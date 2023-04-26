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
		paused_tick = SDL_GetTicks();
	}
}

void Timer::Resume()
{
	if (is_paused == true)
	{
		is_paused = false;
		start_tick += SDL_GetTicks() - paused_tick;
		paused_tick = 0;
	}
}

int Timer::GetTicks()
{
	if (is_started == true)
	{
		return SDL_GetTicks() - start_tick;
	}
	return 0;
}

bool Timer::isStarted()
{
	return is_started;
}

bool Timer::isPaused()
{
	return is_paused;
}
