#include "core/Time.h"

#include "core/Application.h"
#include "eventsystem/EventSystem.h"

namespace chroma
{
	static Time* instance;

	Time* Time::GetInstance()
	{
		if (instance == nullptr)
			instance = new Time();

		return instance;
	}

	// Todo: Implement
	float Time::GetTimeInScene()
	{
		return 0;
	}

	// Todo: Implement
	double Time::GetDeltaTime()
	{
		return 0;
	}
}