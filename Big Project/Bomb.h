#pragma once
#ifndef BOMB_H
#define BOMB_H

#include "CommonFunc.h"
#include "BaseObject.h"
#include "Bomber.h"

#define TIME_BOMB_EXPLODE 2000

class Bomb : public BaseObject
{
public:
	Bomb();
	~Bomb();
	
	void plant();
	void explode();
	bool is_active() const { return m_timer_id != 0; }

private:
	static Uint32 timer_callback(Uint32 interval, void* param);
	void start_timer();
	void stop_timer();

	SDL_TimerID m_timer_id;
};

#endif // !BOMB_H

