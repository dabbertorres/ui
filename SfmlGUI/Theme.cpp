#include "Theme.hpp"

#include <cctype>
#include <array>
#include <sstream>

#include "ParseException.hpp"

namespace
{
	enum class ParseState
	{
		ElementSelector,
		ReadingElement,
		PropertyDefinitions,
		ReadingPropertyName,
		ReadingPropertyValue,
	};
}

namespace ui
{
	Theme::Theme()
	{
		// need to fill in default property values and stuff
	}

	Theme::~Theme()
	{}

	void Theme::load(std::istream& istream)
	{
		using Property = std::pair<std::string, std::string>;

		// read whole file
		istream.seekg(0, std::ios::end);
		std::streamoff length = istream.tellg();
		istream.seekg(0, std::ios::beg);
		
		std::vector<char> buffer(static_cast<std::size_t>(length));
		istream.read(buffer.data(), length);

		std::list<std::string> selectedElements;

		std::list<Property> selectedProperties;
		std::string currentProperty;

		// parsing state tracking
		ParseState parseState = ParseState::ElementSelector;

		// parse!
		auto begin = buffer.begin();
		auto end = buffer.end();

		// track line endings for error reporting
		std::size_t lineNum = 1;	// start at 1 for human friendliness

		for(auto it = begin; it != end; ++it)
		{
			auto val = *it;

			// if ... else if ... else ... to avoid making >= 255 cases in the switch statement
			if(std::isspace(val))
			{
				// check we aren't in a state that allows spaces in the middle...
				if(parseState != ParseState::ElementSelector && parseState != ParseState::PropertyDefinitions)
				{
					// if we are...

					auto tempIt = it;

					// find next non-space character
					while(std::isspace(*++tempIt))
					{
						if(*tempIt == '\n')
							++lineNum;
					}

					// if it's alnum, then that's bad
					if(std::isalnum(*tempIt))
					{
						std::ostringstream oss;
						oss << "Unexpected whitespace (id: " << static_cast<int>(val) << ") at line " << lineNum;

						throw ParseException(oss.str());
					}
				}

				// fine otherwise

				if(val == '\n')
					++lineNum;
			}
			else if(std::isalnum(val))
			{
				if(parseState == ParseState::ElementSelector)
				{
					// if in the element selector, then we found the start of a new element
					parseState = ParseState::ReadingElement;
					begin = it;
				}
				else if(parseState == ParseState::PropertyDefinitions)
				{
					// if in the property definitions, then we found the start of a new property
					parseState = ParseState::ReadingPropertyName;
					begin = it;
				}
			}
			else
			{
				switch(val)
				{
					// separator in element selector
					case ',':
						// end of an element
						if(parseState == ParseState::ReadingElement)
						{
							selectedElements.emplace_back(begin, it);

							parseState = ParseState::ElementSelector;
						}
						else
						{
							std::ostringstream oss;
							oss << "Unexpected \',\' at line " << lineNum;

							throw ParseException(oss.str());
						}
						break;

						// begin property definitions
					case '{':
						if(parseState == ParseState::ElementSelector)
						{
							parseState = ParseState::PropertyDefinitions;
						}
						else if(parseState == ParseState::ReadingElement)
						{
							std::string elem(begin, it);

							// whitespace trim
							auto left = std::find_if_not(elem.begin(), elem.end(), std::isspace);
							auto right = std::find_if_not(elem.rbegin(), elem.rend(), std::isspace).base();

							selectedElements.emplace_back(left, right);

							parseState = ParseState::PropertyDefinitions;
						}
						else
						{
							std::ostringstream oss;
							oss << "Unexpected \'{\' at line " << lineNum;

							throw ParseException(oss.str());
						}
						break;

						// end property definitions
					case '}':
						if(parseState == ParseState::PropertyDefinitions)
						{
							// apply gathered properties to selected elements
							for(auto& e : selectedElements)
							{
								for(auto& p : selectedProperties)
								{
									properties[e][p.first] = p.second;
								}
							}

							// clear for next
							selectedElements.clear();
							selectedProperties.clear();

							parseState = ParseState::ElementSelector;
						}
						else
						{
							std::ostringstream oss;
							oss << "Unexpected \'}\' at line " << lineNum;

							throw ParseException(oss.str());
						}
						break;

						// property name and value separator
					case ':':
						if(parseState == ParseState::ReadingPropertyName)
						{
							std::string name(begin, it);

							// whitespace trim
							auto left = std::find_if_not(name.begin(), name.end(), std::isspace);
							auto right = std::find_if_not(name.rbegin(), name.rend(), std::isspace).base();

							currentProperty.assign(left, right);

							parseState = ParseState::ReadingPropertyValue;

							// skip over next space
							while(std::isspace(*++it))
							{
								if(*it == '\n')
									++lineNum;
							}

							// found our starting point
							begin = it;

							// decrement so for loop increment isn't screwed up
							--it;
						}
						else
						{
							std::ostringstream oss;
							oss << "Unexpected \':\' at line " << lineNum;

							throw ParseException(oss.str());
						}
						break;

						// end property
					case ';':
						if(parseState == ParseState::ReadingPropertyValue)
						{
							std::string value(begin, it);

							// whitespace trim
							auto left = std::find_if_not(value.begin(), value.end(), std::isspace);
							auto right = std::find_if_not(value.rbegin(), value.rend(), std::isspace).base();

							selectedProperties.emplace_back(currentProperty, std::string{left, right});

							parseState = ParseState::PropertyDefinitions;
						}
						else
						{
							std::ostringstream oss;
							oss << "Unexpected \';\' at line " << lineNum;

							throw ParseException(oss.str());
						}
						break;

						// comment
					case '#':
						while(*++it != '\n');	// move to next newline character
						++lineNum;
						break;

					default:
					{
						// we got some character we don't handle
						std::ostringstream oss;
						oss << "Unexpected \'" << val << "\' (id: " << static_cast<int>(val) << ") at line " << lineNum;

						throw ParseException(oss.str());
					}
					break;
				}
			}
		}
	}

	void Theme::add(const std::string& elem, const std::string& prop, const std::string& val)
	{
		properties.at(elem).at(prop) = val;
	}

	const Theme::Properties& Theme::get(const std::string& elem) const
	{
		return properties.at(elem);
	}

	const std::string& Theme::get(const std::string& elem, const std::string& prop) const
	{
		return properties.at(elem).at(prop);
	}

	Theme::Elements::const_iterator Theme::begin() const
	{
		return properties.begin();
	}

	Theme::Elements::const_iterator Theme::end() const
	{
		return properties.end();
	}
}
