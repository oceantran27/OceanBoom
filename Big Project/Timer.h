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
	int start_tick;
	int paused_tick;

	bool is_started;
	bool is_paused;
};


#endif // !TIMER_H
