#ifndef UI_CONTROL_HPP
#define UI_CONTROL_HPP

#include "EventReceiver.hpp"
#include "Themeable.hpp"

namespace dbr
{
	namespace ui
	{
		class Control : public EventReceiver, public Themeable
		{
			public:
				Control();
				virtual ~Control();

				bool isVisible() const;

			private:
				bool visible;
		};
	}
}

#endif
