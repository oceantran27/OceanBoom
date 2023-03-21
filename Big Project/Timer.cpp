#include "Timer.h";

Timer::Timer()
{
	start_tick = 0;
	paused_tick = 0;
	is_paused = false;
	is_started = false;
}

Timer::~Timer()
{
	//
}

void Timer::Start()
{
	is_started = true;
	is_paused = false;
	start_tick = SDL_GetTicks();
}

void Timer::Stop()
{
	is_paused = false;
	is_started = false;
}

void Timer::Paused()
{
	if (is_started == true && is_paused == false)
	{
		is_paused = true;
		paused_tick = SDL_GetTicks() - start_tick;
		paused_tick = 0;
	}
}

int Timer::GetTicks()
{
	if (is_started == true)
	{
		if (is_paused == true)
		{
			return paused_tick;
		}
		else
		{
			return SDL_GetTicks() - start_tick;
		}
	}
	return 0;
}

bool Timer::IsStarted()
{
	return is_started;
}

bool Timer::IsPaused()
{
	return is_paused;
}
