#include "Desktop.hpp"

namespace ui
{
	Desktop::Desktop()
	:	focus(nullptr)
	{}

	Desktop::~Desktop()
	{}

	Window& Desktop::getWindow(Window::Handle handle) const
	{
		return windows.at(handle);
	}

	Window& Desktop::getFocused() const
	{
		return *focus;
	}

	void Desktop::applyTheme(Theme&& thm)
	{
		theme = thm;

		// do some updating stuff...
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
}
