#pragma once
#ifndef BOMB_H
#define BOMB_H

#include "CommonFunc.h"
#include "BaseObject.h"
#include "Bomber.h"

#define TIME_BOMB_EXPLODE 3000

class Bomber;

class Bomb : public BaseObject
{
public:
	Bomb();
	~Bomb();
	
	void plant( const float& xPos, const float& yPos, SDL_Renderer* screen);
	void explode();
	bool is_active() const { return m_timer_id != 0; }
	void SetClip();
	bool LoadClipImg(std::string path, SDL_Renderer* screen);
	void Show(SDL_Renderer* des);
	int GetXNumTile() const { return x_num_tile; }
	int GetYNumTile() const { return y_num_tile; }


private:
	int x_num_tile;
	int y_num_tile;

	float x_pos;
	float y_pos;

	int frame;
	int width_frame;
	int height_frame;
	SDL_Rect frame_clip[4];

	static Uint32 timer_callback(Uint32 interval, void* param);
	void start_timer();
	void stop_timer();

	SDL_TimerID m_timer_id;
};

#endif // !BOMB_H

