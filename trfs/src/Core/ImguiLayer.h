#pragma once

#include <SDL.h>

namespace Core
{
	class ImguiLayer
	{
	public:
		ImguiLayer(SDL_Window* window, SDL_GLContext context);
		~ImguiLayer() = default;

		void OnNewFrame() const;
		void OnEvent(SDL_Event& event) const;
		void Render() const;
		void OnEndFrame() const;
		void Shutdown() const;
	};
} // namespace Core
