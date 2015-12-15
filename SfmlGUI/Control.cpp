#include "Control.hpp"

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
