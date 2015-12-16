#include <iostream>
#include <fstream>

#include "Theme.hpp"
#include "ParseException.hpp"

#include "Desktop.hpp"

int main(int argc, char** argv)
{
	ui::Theme theme;

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
			std::cout << '\t' << prop.first << ": " << prop.second << '\n';
		}
	}
	std::cout << std::endl;

	ui::Desktop desktop;
	desktop.applyTheme(theme);

	return 0;
}