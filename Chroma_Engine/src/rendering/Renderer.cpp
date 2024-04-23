#include "rendering/Renderer.h"

#include "input/InputManager.h"
#include "eventsystem/EventSystem.h"
#include "util/Random.h"
#include "logger/Logger.h"

namespace chroma
{
	Renderer::Renderer(SDL_Window* window, Uint32 flags) : m_CreationStatus(false)
	{
		m_Renderer = SDL_CreateRenderer(window, -1, flags);
		if (m_Renderer == nullptr)
		{
			Logger::GetInstance()->Log("Could not create Renderer!");
			m_CreationStatus = false;
		}

		m_CreationStatus = true;

		EventHandler<SDL_Keycode> _randomDrawColor([this](SDL_Keycode key)
			{
				if (key != SDLK_SPACE)
					return;

				m_R = Random::GetInt(0, 255);
				m_G = Random::GetInt(0, 255);
				m_B = Random::GetInt(0, 255);
			});

		InputManager::GetInstance()->OnKeyDown.Subscribe(_randomDrawColor);
	}

	Renderer::~Renderer()
	{
		SDL_DestroyRenderer(m_Renderer);
	}

	void Renderer::Prepare()
	{
		SDL_SetRenderDrawColor(m_Renderer, m_R, m_G, m_B, 0xFF);
		SDL_RenderClear(m_Renderer);
	}

	void Renderer::Render(SDL_Texture* texture, SDL_Rect srcRect, SDL_Rect dstRect)
	{
		SDL_RenderCopy(m_Renderer, texture, &srcRect, &dstRect);
	}

	void Renderer::Render(SDL_Surface* surface, SDL_Rect srcRect, SDL_Rect dstRect)
	{
		SDL_Texture* _texture = SDL_CreateTextureFromSurface(m_Renderer, surface);
		SDL_RenderCopy(m_Renderer, _texture, &srcRect, &dstRect);
	}

	void Renderer::Present()
	{
		SDL_RenderPresent(m_Renderer);
	}
}