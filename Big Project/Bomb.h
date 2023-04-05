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
	
	SDL_TimerID GetBombTimer() const { return timer_exist_bomb; }
	SDL_TimerID GetExplosionTimer() const { return timer_explode; }

	void Plant( const int& xPos, const int& yPos);

	void DisplayBomb(SDL_Renderer* des);
	void DisplayExplosion(SDL_Renderer* des);
	bool LoadClipImg(std::string path);
	void SetScreen(SDL_Renderer* screen_) { screen = screen_; }
	void SetClip();

	int GetX() const { return x; }
	int GetY() const { return y; }

	void SetRight(const int& right) { max_right = right; }
	void SetLeft(const int& left) { max_left = left; }
	void SetTop(const int& top) { max_top = top; }
	void SetBot(const int& bot) { max_bot = bot; }

	void SetLim(const bool& lim_) { lim = lim_; }
	bool GetLim() const { return lim; }

private:
	void StartTimer();

	//Limit the number of times the bomb explodes
	bool lim;

	int x;
	int y;

	//Maximum length of bomb when colliding with other objects
	int max_right;
	int max_left;
	int max_top;
	int max_bot;

	int frame;
	int width_frame;
	int height_frame;
	SDL_Rect frame_clip[BOMB_FRAMES];

	SDL_TimerID timer_exist_bomb;
	SDL_TimerID timer_explode;
	SDL_Renderer* screen;
};

#endif // !BOMB_H

