#pragma once
#ifndef BOMB_H
#define BOMB_H

#include "CommonFunc.h"
#include "BaseObject.h"
#include "Bomber.h"
#include "Map.h"

#define BOMB_FRAMES 4

class Bomb : public BaseObject
{
public:
	Bomb();
	~Bomb();
	
	void Plant( const int& xPos, const int& yPos);
	SDL_TimerID GetTimer() const { return timer_id; }
	void SetClip();
	bool LoadClipImg(std::string path);
	void Show(SDL_Renderer* des);
	int GetX() const { return x_pos / TILE_SIZE; }
	int GetY() const { return y_pos / TILE_SIZE; }
	void SetScreen(SDL_Renderer* screen_) { screen = screen_; }

private:
	float x_pos;
	float y_pos;

	int frame;
	int width_frame;
	int height_frame;
	SDL_Rect frame_clip[BOMB_FRAMES];

	void StartTimer();

	SDL_TimerID timer_id;
	SDL_Renderer* screen;

};

#endif // !BOMB_H

