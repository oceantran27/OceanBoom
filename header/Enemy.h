#pragma once
#ifndef ENEMY_H
#define ENEMY_H

#include "BaseObject.h"
#include "CommonFunc.h"
#include "Player.h"
#include "Map.h"

#define FREEZE_TIMER 15000
#define DEAD_TIMER 700

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
		WALK_DOWN = 4,
		FREEZE = 5,
		DEAD = 6
	};

	void setSpawn(const int& type_, const float& x_, const float& y_) { type = type_; x_pos = x_ * CELL_SIZE; y_pos = y_ * CELL_SIZE; }
	void setXVal(const float& x_val_) { x_val = x_val_; }
	void setYVal(const float& y_val_) { y_val = y_val_; }
	void setXPos(const float& x_pos_) { x_pos = x_pos_; }
	void setYPos(const float& y_pos_) { y_val = y_pos_; }

	float getXPos() const { return x_pos; }
	float getYPos() const { return y_pos; }
	int getTypeEnemy() const { return type;}
	Uint32 getTimeDead() const { return dead_time; }

	void showEnemy(SDL_Renderer* des);
	void handleMove(Player& pPLayer, Map& main_map_);
	void increaseEnemySpeed();

	bool isCollideCell(Map& main_map_);
	bool isCollideExplosion(Map& main_map_);
	bool checkToMap(Player& pPlayer, Map& main_map_);
	void checkDead(Player& pPLayer);
	bool isDead() const { return is_dead; }
	bool isFreeze() const { return is_freeze; }


private:
	//Type of enemy
	int type;

	bool is_speed_up;
	float enemy_speed[4] = { 0, 3, 3.5, 2 };
	int enemy_life[4] = { 0, 1, 1, 200 };

	float x_val;
	float y_val;

	float x_pos;
	float y_pos;
	float real_y_pos;

	int width_frame;
	int height_frame;

	int status;

	bool is_freeze;
	bool is_dead;
	bool is_coll;

	Uint32 dead_time;
	Uint32 freeze_time;

	Mix_Chunk* mix_die;
	Mix_Chunk* mix_freeze;
};

#endif // !ENEMY_H
