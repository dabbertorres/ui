#include "Control.hpp"

namespace dbr
{
	namespace ui
	{
		Control::Control()
		:	visible(true)
		{}

		Control::~Control()
		{}

		bool Control::isVisible() const
		{
			return visible;
		}
	}
}
