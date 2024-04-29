#include "rendering/Renderer.h"

#include "input/InputManager.h"
#include "eventsystem/EventSystem.h"
#include "util/Random.h"
#include "logger/Logger.h"

namespace chroma
{
	Renderer::Renderer() : m_CreationStatus(false)
	{
		m_CreationStatus = true;
	}
}