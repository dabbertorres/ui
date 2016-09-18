#ifndef UI_PARSE_EXCEPTION_HPP
#define UI_PARSE_EXCEPTION_HPP

#include <stdexcept>

namespace dbr
{
	namespace ui
	{
		class ParseException : public std::runtime_error
		{
			public:
				ParseException() = delete;
				explicit ParseException(const std::string& arg);
				explicit ParseException(const char* arg);

				ParseException(const ParseException& other) = default;
				ParseException(ParseException&& other) = default;

				ParseException& operator=(const ParseException& other) = default;
				ParseException& operator=(ParseException&& other) = default;

				~ParseException() = default;
		};
	}
}

#endif
