#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include "BaseObject.h"
#include "CommonFunc.h"
#include "Bomb.h"
#include "Map.h"

#define PLAYER_FRAMES 5
#define LIMIT_LAG 15
#define PROTECT_TIMER 5000

class Bomb;

class Player : public BaseObject
{
public:
	Player();
	~Player();

	enum WalkType
	{
		WALK_NONE = 0,
		WALK_RIGHT = 1,
		WALK_LEFT = 2,
		WALK_UP = 3,
		WALK_DOWN = 4,
		DEAD = 5
	};

	void handleInputAction(SDL_Event &event, SDL_Renderer* screen, Map& main_map_);
	void handleMove(Map& main_map_, Map& item_map_);
	void explodeBomb(SDL_Renderer* des, Bomb* bomb_, Map& main_map_, Map& item_map_);

	void showPlayer(SDL_Renderer* des);
	void showBomb(SDL_Renderer* des, Map& main_map_, Map& item_map_);
	void showLife(SDL_Renderer* des);


	void increaseBombPower() { bomb_power++; }
	void increaseNumBomb() { num_bomb++; }
	void increasePlayerSpeed() { player_speed += 0.75; }
	void increasePoint(const int& point_plus) { mark += point_plus; }
	void decreaseLife();
	void increaseStar(const int& star_plus) { star += star_plus; }

	bool loadClipImg(std::string path, SDL_Renderer* screen);
	void setClip();
	void setSpawn(const float& x_, const float& y_);

	int getStar() const { return star; }
	int getMark() const { return mark; }
	int getLife() const { return life; }
	float getXPos() const { return x_pos; }
	float getYPos() const { return y_pos; }
	float getWidthFrame() const { return width_frame; }
	float getHeightFrame() const { return height_frame; }

	void checkCollideExplosion(const int& angle_1, const int& angle_2, const int& angle_3, const int& angle_4);
	void checkCollideEnemy(const SDL_Rect& rect);
	void checkToMap(Map& main_map_, Map& item_map_);

private:
	int limit_move_sound;

	int star;
	int mark;
	int life;
	int num_bomb;
	int bomb_power;
	float player_speed;

	float x_val;
	float y_val;

	float x_pos;
	float y_pos;
	float real_y_pos;

	int frame_effect;
	int frame;
	int width_frame;
	int height_frame;
	int status;

	bool is_coll_explosion;
	bool is_coll_enemy;
	bool limit_coll;

	Input input_type;
	Uint32 time_protect;
	SDL_Rect frame_clip[PLAYER_FRAMES];
	std::vector<Bomb*> pbomb_list;

	Mix_Chunk* mix_move;
	Mix_Chunk* mix_plant;
	Mix_Chunk* mix_damage;
	Mix_Chunk* mix_die;
	Mix_Chunk* mix_item;
	Mix_Chunk* mix_explosion;
};
 
#endif // !PLAYER_H
