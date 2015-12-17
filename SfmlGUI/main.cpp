#include <iostream>
#include <fstream>

#include "Theme.hpp"
#include "ParseException.hpp"

#include "Desktop.hpp"

using namespace dbr;

int main(int argc, char** argv)
{
	ui::Theme theme;
	ui::Desktop desktop;

	{
		std::ifstream fin("test.thm");

		try
		{
			if(fin)
				theme.load(fin);
			else
				std::cout << "Couldn't open test.thm\n";
		}
		catch(const ui::ParseException& pe)
		{
			std::cout << "ParseException: " << pe.what() << '\n';
		}
	}

	for(auto& elem : theme)
	{
		std::cout << elem.first << ":\n";
		for(auto& prop : elem.second)
		{
			std::cout << '\t' << prop.first << ": " << static_cast<std::string>(prop.second) << '\n';
		}
	}
	std::cout << std::endl;

	desktop.applyTheme(theme);

	return 0;
}