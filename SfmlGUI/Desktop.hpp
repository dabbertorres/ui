#ifndef UI_DESKTOP_HPP
#define UI_DESKTOP_HPP

#include "Themeable.hpp"

#include <unordered_map>
#include <vector>
#include <istream>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <SFML/System/Clock.hpp>

#include "Theme.hpp"
#include "Window.hpp"

namespace ui
{
	class Desktop : public EventReceiver, public Themeable, public sf::Drawable
	{
		public:
			Desktop();
			~Desktop();

			void applyTheme(const Theme& thm);

			Window& getWindow(Window::Handle handle) const;
			Window& getFocused() const;

			void update(const sf::Event& event) override;

		private:
			void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

			mutable std::unordered_map<Window::Handle, Window> windows;
			Window* focus;
			Theme theme;

			std::vector<sf::Vertex> vertices;

			sf::Clock clock;
	};
}

#endif
