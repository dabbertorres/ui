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
		PropertyDefinitions,
		PropertyName,
		PropertyValue,
	};

	// parsing state tracking
	constexpr std::array<ParseState, 4> states = {ParseState::ElementSelector, ParseState::PropertyDefinitions, ParseState::PropertyName, ParseState::PropertyValue};
	auto currState = 0;
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
		// read whole file
		istream.seekg(std::ios::end);
		auto length = istream.tellg();
		istream.seekg(std::ios::beg);

		std::vector<char> buffer(length);
		istream.read(buffer.data(), length);

		std::list<std::string> selectedElements;

		// parse!
		auto begin = buffer.begin();
		auto end = buffer.end();
		for(auto it = begin; it != end; ++it)
		{
			auto val = *it;

			// skip whitespace
			if(std::isspace(val))
				continue;

			switch(val)
			{
				// separator in element selector
				case ',':
					if(states[currState] == ParseState::ElementSelector)
					{
						selectedElements.emplace_back(begin, it);
						++(begin = it);
					}
					else
					{
						std::ostringstream oss("Unexpected \',\' at position ");
						oss << it - buffer.begin();

						throw ParseException(oss.str());
					}
					break;

					// begin property definitions
				case '{':
					if(states[currState] == ParseState::ElementSelector)
					{
						++currState;
					}
					else
					{
						std::ostringstream oss("Unexpected \'{\' at position ");
						oss << it - buffer.begin();

						throw ParseException(oss.str());
					}
					break;

					// end property definitions
				case '}':
					break;

					// property name and value separator
				case ':':
					break;

					// end property
				case ';':
					break;

					// comment
				case '#':
					while(*++it != '\n');	// semicolon intentional: "move to next char until we find a newline character"
					break;

				default:
					break;
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
}
