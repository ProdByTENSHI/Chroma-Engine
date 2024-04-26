#pragma once

#include <SDL.h>

namespace chroma
{
	class Time
	{
	public:
		static Time* GetInstance();

		//! Returns the Time in the current Scene
		float GetTimeInScene();

		//! Returns Time since the last Frame
		double GetDeltaTime();

	private:
		Time();
		Time(const Time& other);

		float m_LastFrameTime;

	};
}