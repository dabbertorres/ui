#ifndef UI_WINDOW_HPP
#define UI_WINDOW_HPP

#include "EventReceiver.hpp"
#include <SFML/Graphics/Drawable.hpp>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/Vertex.hpp>

#include <vector>
#include <mutex>

#include "Control.hpp"

namespace ui
{
	class Window : public Control, public sf::Drawable
	{
		public:
			using Handle = unsigned int;
			
			Window();
			~Window();

			void applyTheme(const Theme& thm) override;

			std::mutex& getMutex();

			void update(const sf::Event& event) override;

		private:
			void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

			std::vector<sf::Vertex> vertices;

			std::mutex syncMutex;
	};
}

#endif
