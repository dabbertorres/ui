#include "ParseException.hpp"

namespace ui
{
	ParseException::ParseException(const std::string& arg)
	:	std::runtime_error(arg)
	{}

	ParseException::ParseException(const char* arg)
	:	std::runtime_error(arg)
	{}
}