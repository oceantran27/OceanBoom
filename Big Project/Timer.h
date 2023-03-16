#pragma once
#ifndef TIMER_H
#define TIMER_H

#include "CommonFunc.h"

class Timer
{
public:
	Timer();
	~Timer();

	void Start();
	void Stop();
	void Paused();
	void Resume();

	int GetTicks();
	bool IsPaused();
	bool IsStarted();

private:
	int mStartTick;
	int mPausedTick;

	bool mIsStarted;
	bool mIsPaused;
};


#endif // !TIMER_H
