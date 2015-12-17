#ifndef UI_EVENT_RECEIVER_HPP
#define UI_EVENT_RECEIVER_HPP

#include <SFML/Window/Event.hpp>

namespace dbr
{
	namespace ui
	{
		class EventReceiver
		{
			public:
				EventReceiver();
				virtual ~EventReceiver();

				virtual void update(const sf::Event& event) = 0;
		};
	}
}

#endif
