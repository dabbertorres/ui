#include "Desktop.hpp"

#include <SFML/System/Clock.hpp>

namespace dbr
{
	namespace ui
	{
		Desktop::Desktop()
		:	focus(nullptr),
			timerUpdateThread(timerUpdate, this),
			running(true)
		{
			constructNotice.notify_all();
		}

		Desktop::~Desktop()
		{
			running = false;

			if(timerUpdateThread.joinable())
				timerUpdateThread.join();
		}

		Window& Desktop::getWindow(Window::Handle handle) const
		{
			return windows.at(handle);
		}

		Window& Desktop::getFocused() const
		{
			return *focus;
		}

		void Desktop::applyTheme(const Theme& thm)
		{
			theme = thm;

			// do some updating stuff...
			for(auto& win : windows)
			{
				win.second.applyTheme(theme);
			}
		}

		void Desktop::update(const sf::Event& event)
		{
			switch(event.type)
			{
				case sf::Event::MouseMoved:
					break;

				default:
					break;
			}

			if(focus)
			{
				focus->update(event);
			}
		}

		void Desktop::draw(sf::RenderTarget& target, sf::RenderStates states) const
		{
			target.draw(vertices.data(), vertices.size(), sf::PrimitiveType::Quads, states);

			for(auto& win : windows)
				target.draw(win.second, states);
		}

		void Desktop::timerUpdate(Desktop* desktop)
		{
			std::unique_lock<std::mutex> constructionLock(desktop->constructMutex);
			desktop->constructNotice.wait(constructionLock);

			sf::Clock clock;

			while(desktop->running)
			{

			}
		}
	}
}
