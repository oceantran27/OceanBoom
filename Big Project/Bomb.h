#pragma once
#ifndef BOMB_H
#define BOMB_H

#include "CommonFunc.h"
#include "BaseObject.h"
#include "Player.h"
#include "Map.h"

#define BOMB_FRAMES 8
#define BOMB_EXIST_TIME 2500
#define EXPLOSION_TIME 800

class Bomb : public BaseObject
{
public:
	Bomb();
	~Bomb();
	
	SDL_TimerID getBombTimer() const { return timer_exist_bomb; }
	SDL_TimerID getExplosionTimer() const { return timer_explode; }

	void plantBomb( const int& xPos, const int& yPos);

	void displayBomb(SDL_Renderer* des);
	void displayExplosion(SDL_Renderer* des);
	bool loadClipImg(std::string path);
	void setScreen(SDL_Renderer* screen_) { screen = screen_; }
	void setClip();

	int getX() const { return x; }
	int getY() const { return y; }

	void setRight(const int& right) { max_right = right; }
	void setLeft(const int& left) { max_left = left; }
	void setTop(const int& top) { max_top = top; }
	void setBot(const int& bot) { max_bot = bot; }

	void setLim(const bool& lim_) { limit_explode = lim_; }
	bool getLim() const { return limit_explode; }
	void clearBomb(Map& main_map_, Map& item_map_);

private:
	void StartTimer();

	int count;

	//Limit the number of times the bomb explodes
	bool limit_explode;

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

