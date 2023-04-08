#pragma once
#ifndef ENEMY_H
#define ENEMY_H

#include "BaseObject.h"
#include "CommonFunc.h"
#include "Map.h"

#define ENEMY_FRAMES 6

class Enemy : public BaseObject
{
public:
	Enemy();
	~Enemy();

	enum WalkType
	{
		WALK_NONE = 0,
		WALK_RIGHT = 1,
		WALK_LEFT = 2,
		WALK_UP = 3,
		WALK_DOWN = 4
	};

	void SetXVal(const float& x_val_) { x_val = x_val_; }
	void SetYVal(const float& y_val_) { y_val = y_val_; }

	void SetXPos(const float& x_pos_) { x_pos = x_pos_; }
	void SetYPos(const float& y_pos_) { y_val = y_pos_; }

	float GetXPos() const { return x_pos; }
	float GetYPos() const { return y_pos; }

	//bool LoadClipImg(std::string path, SDL_Renderer* screen);
	//void SetClip();
	void EnemyShow(SDL_Renderer* des);
	void HandleMove(Map& main_map_);
	void CheckToMap(Map& main_map_);

	int GetWidthFrame() const { return width_frame; }
	int GetHeightFrame() const { return height_frame; }
	void SetSpawn(const int& type_, const float& x_, const float& y_) { type = type_; x_pos = x_ * TILE_SIZE; y_pos = y_ * TILE_SIZE; }

private:
	//
	int timer_keep_direction;

	int type;

	float enemy_speed[10] = {0, 3, 4};

	float x_val;
	float y_val;

	float x_pos;
	float y_pos;

	int width_frame;
	int height_frame;

	//int frame;

	//SDL_Rect frame_clip[ENEMY_FRAMES];
	int status;
};

#endif // !ENEMY_H
