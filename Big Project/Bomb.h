#pragma once
#ifndef BOMB_H
#define BOMB_H

#include "CommonFunc.h"
#include "BaseObject.h"
#include "Bomber.h"
#include "Map.h"

class Bomber;

class Bomb : public BaseObject
{
public:
	Bomb();
	~Bomb();
	
	void Plant( const float& xPos, const float& yPos);
	void Explode();
	bool IsActive() const { return m_timer_id != 0; }
	void SetClip();
	bool LoadClipImg(std::string path);
	void Show(SDL_Renderer* des);
	int GetXNumTile() const { return x_num_tile; }
	int GetYNumTile() const { return y_num_tile; }
	void SetScreen(SDL_Renderer* screen_) { screen = screen_; }
	void SetMap(Map& map_) { map_data = map_; }

private:
	int bomb_power = 2;

	Map map_data;
	SDL_Renderer* screen;

	int x_num_tile;
	int y_num_tile;

	float x_pos;
	float y_pos;

	int frame;
	int width_frame;
	int height_frame;
	SDL_Rect frame_clip[4];

	static Uint32 TimerCallback(Uint32 interval, void* param);
	void StartTimer();
	void StopTimer();

	SDL_TimerID m_timer_id;
};

#endif // !BOMB_H

