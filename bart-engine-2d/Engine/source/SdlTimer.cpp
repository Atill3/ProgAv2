#include <SdlTimer.h>
#include <SDL.h>

bool bart::SdlTimer::Initialize()
{
	return true;
}

void bart::SdlTimer::Destroy()
{
}

float bart::SdlTimer::GetTime()
{
	return static_cast<float>(SDL_GetTicks());
}

void bart::SdlTimer::Sleep(const float delay)
{
	if (delay > 0)
	{
		SDL_Delay(static_cast<Uint32>(delay));
	}
}
