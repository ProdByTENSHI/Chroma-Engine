#pragma once

#include <SDL.h>

namespace chroma
{
	class Renderer
	{
	public:
		Renderer(SDL_Window* window, Uint32 flags);
		~Renderer();

		// Cleans the Screen and Prepares everything before the next Frame is being drawn
		void Prepare();

		// Render a Texture with the given Size and Position
		void Render(SDL_Texture* texture, SDL_Rect srcRect, SDL_Rect dstRect);

		// Converts the given Surface into a Texture before rendering it with the given Size and Position
		void Render(SDL_Surface* surface, SDL_Rect srcRect, SDL_Rect dstRect);

		// Draws the final Frame. Gets called AFTER all the Render Functions
		void Present();

		// -- GETTER
		SDL_Renderer* GetRenderer() { return m_Renderer; }
		bool GetCreationStatus() { return m_CreationStatus; }

	private:
		SDL_Renderer* m_Renderer;

		Uint8 m_R = 0xFF;
		Uint8 m_G = 0xFF;
		Uint8 m_B = 0xFF;

		bool m_CreationStatus;

	};
}