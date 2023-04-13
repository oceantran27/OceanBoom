#pragma once
#ifndef BOMBER_H
#define BOMBER_H

#include "BaseObject.h"
#include "CommonFunc.h"
#include "Bomb.h"
#include "Map.h"

#define BOMBER_FRAMES 3

class Bomb;

class Bomber : public BaseObject
{
public:
	Bomber();
	~Bomber();

	enum WalkType
	{
		WALK_NONE = 0,
		WALK_RIGHT = 1,
		WALK_LEFT = 2,
		WALK_UP = 3,
		WALK_DOWN = 4
	};

	bool LoadClipImg(std::string path, SDL_Renderer* screen);
	void BomberShow(SDL_Renderer* des);
	void HandleInputAction(SDL_Event &event, SDL_Renderer* screen, Map& main_map_);
	void SetClip();
	void HandleMove(Map& main_map_, Map& item_map_);
	void CheckToMap(Map& main_map_, Map& item_map_);
	void BombShow(SDL_Renderer* des, Map& main_map_, Map& item_map_);
	void BombExplode(SDL_Renderer* des, Bomb* bomb_, Map& main_map_, Map& item_map_);
	void IncreaseBombPower() { bomb_power++; }
	void IncreaseBombLimit() { bomb_limit++; }
	void IncreasePlayerSpeed() { player_speed ++; }
	void SetSpawn(const float& x_, const float& y_) { x_pos = x_*TILE_SIZE; y_pos = y_*TILE_SIZE; }
	float GetXPos() const { return x_pos; }
	float GetYPos() const { return y_pos; }

private:

	int bomb_limit;
	int bomb_power;
	float player_speed;
	std::vector<Bomb*> pbomb_list;

	float x_val;
	float y_val;

	float x_pos;
	float y_pos;

	int frame;
	int width_frame;
	int height_frame;

	SDL_Rect frame_clip[BOMBER_FRAMES];
	Input input_type;
	int status;
};
 
#endif // !MAIN_OBJECT_H
