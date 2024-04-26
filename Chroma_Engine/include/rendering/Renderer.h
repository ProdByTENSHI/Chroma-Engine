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
		void RenderTexture(SDL_Texture* texture, const SDL_Rect* srcRect, const SDL_Rect* dstRect);

		// Converts the given Surface into a Texture before rendering it with the given Size and Position
		void RenderSurface(SDL_Surface* surface, SDL_Rect srcRect, SDL_Rect dstRect);

		// Draws the final Frame. Gets called AFTER all the Render Functions
		void Present();

		// -- GETTER
		SDL_Renderer* GetRenderer() { return m_Renderer; }
		bool GetCreationStatus() { return m_CreationStatus; }

	private:
		SDL_Renderer* m_Renderer;

		bool m_CreationStatus;

	};
}