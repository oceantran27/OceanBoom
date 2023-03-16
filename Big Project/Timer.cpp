#include "Timer.h";

Timer::Timer()
{
	mStartTick = 0;
	mPausedTick = 0;
	mIsPaused = false;
	mIsStarted = false;
}

Timer::~Timer()
{
	//
}

void Timer::Start()
{
	mIsStarted = true;
	mIsPaused = false;
	mStartTick = SDL_GetTicks();
}

void Timer::Stop()
{
	mIsPaused = false;
	mIsStarted = false;
}

void Timer::Paused()
{
	if (mIsStarted == true && mIsPaused == false)
	{
		mIsPaused = true;
		mPausedTick = SDL_GetTicks() - mStartTick;
		mPausedTick = 0;
	}
}

int Timer::GetTicks()
{
	if (mIsStarted == true)
	{
		if (mIsPaused == true)
		{
			return mPausedTick;
		}
		else
		{
			return SDL_GetTicks() - mStartTick;
		}
	}
	return 0;
}

bool Timer::IsStarted()
{
	return mIsStarted;
}

bool Timer::IsPaused()
{
	return mIsPaused;
}
