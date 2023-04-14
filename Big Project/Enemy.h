#pragma once
#ifndef ENEMY_H
#define ENEMY_H

#include "BaseObject.h"
#include "CommonFunc.h"
#include "Map.h"

#define FREEZE_TIMER 15000

class Enemy : public BaseObject
{
public:
	Enemy();
	~Enemy();

	enum WalkType
	{
		FREEZE = 0,
		WALK_RIGHT = 1,
		WALK_LEFT = 2,
		WALK_UP = 3,
		WALK_DOWN = 4,
		DEAD = 5
	};

	void SetXVal(const float& x_val_) { x_val = x_val_; }
	void SetYVal(const float& y_val_) { y_val = y_val_; }

	void SetXPos(const float& x_pos_) { x_pos = x_pos_; }
	void SetYPos(const float& y_pos_) { y_val = y_pos_; }

	float GetXPos() const { return x_pos; }
	float GetYPos() const { return y_pos; }

	void EnemyShow(SDL_Renderer* des);
	void HandleMove(const float& player_x_pos, const float& player_y_pos, Map& main_map_);
	bool CheckToMap(Map& main_map_);
	void SetSpawn(const int& type_, const float& x_, const float& y_) { type = type_; x_pos = x_ * TILE_SIZE; y_pos = y_ * TILE_SIZE; }

	bool checkCellCollision(Map& main_map_);
	bool checkBombCollision(Map& main_map_);

private:
	//Type of enemy
	int type;

	float enemy_speed[4] = {0, 3, 3.5};

	float x_val;
	float y_val;

	float x_pos;
	float y_pos;

	int width_frame;
	int height_frame;

	int status;

	bool is_freeze;
	bool is_dead;

	SDL_TimerID timer_id;
};

#endif // !ENEMY_H
