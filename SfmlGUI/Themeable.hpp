#ifndef UI_THEMEABLE_HPP
#define UI_THEMEABLE_HPP

#include <string>

#include "Theme.hpp"

namespace ui
{
	class Themeable
	{
		public:
			Themeable();
			virtual ~Themeable();

			virtual void applyTheme(const Theme& theme) = 0;
	};
}

#endif
