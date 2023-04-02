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
	void HandleInputAction(SDL_Event &event, SDL_Renderer* screen, Map& map_data);
	void SetClip();
	void HandleMove(Map& map_data);
	void CheckToMap(Map& map_data);
	void GetBombList(std::vector<Bomb*> bomb_list);
	void BombShow(SDL_Renderer* des, Map& map_data);
	void BombExplode(Bomb* bomb_, Map& map_data);
	void IncreaseBombPower() { bomb_power++; }

private:
	int bomb_power;

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
