#ifndef UI_DESKTOP_HPP
#define UI_DESKTOP_HPP

#include "EventReceiver.hpp"
#include "Themeable.hpp"
#include <SFML/Graphics/Drawable.hpp>

#include <unordered_map>
#include <vector>

#include <thread>
#include <atomic>
#include <condition_variable>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/Vertex.hpp>

#include "Theme.hpp"
#include "Window.hpp"

namespace ui
{
	class Desktop : public EventReceiver, public Themeable, public sf::Drawable
	{
		public:
			Desktop();

			Desktop(const Desktop& other) = delete;
			Desktop(Desktop&& other) = default;

			~Desktop();

			void applyTheme(const Theme& thm) override;

			Window& getWindow(Window::Handle handle) const;
			Window& getFocused() const;

			void update(const sf::Event& event) override;

		private:
			void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

			static void timerUpdate(Desktop* desktop);

			// used to block timerUpdateThread until construction of Desktop is finished
			// also, unfortunately, the order here matters. (constructNotice and constructMutex before timerUpdateThread)
			// otherwise, timerUpdate() on timerUpdateThread may try to use these before they have finished being constructed.
			std::condition_variable constructNotice;
			std::mutex constructMutex;

			std::thread timerUpdateThread;
			std::atomic<bool> running;

			mutable std::unordered_map<Window::Handle, Window> windows;
			Window* focus;
			Theme theme;

			std::vector<sf::Vertex> vertices;
	};
}

#endif
