#include "Window.hpp"

namespace ui
{
	Window::Window()
	{}

	Window::~Window()
	{}

	void Window::applyTheme(const Theme& thm)
	{
		
	}

	std::mutex& Window::getMutex()
	{
		return syncMutex;
	}

	void Window::update(const sf::Event& event)
	{

	}

	void Window::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(vertices.data(), vertices.size(), sf::PrimitiveType::Quads, states);
	}
}
