#pragma once
#ifndef MAIN_OBJECT_H
#define MAIN_OBJECT_H

#include "BaseObject.h"
#include "CommonFunc.h"
#include "Bomb.h"
#include <vector>

class MainObject : public BaseObject
{
public:
	MainObject();
	~MainObject();

	enum WalkType
	{
		WALK_RIGHT = 1,
		WALK_LEFT = 2,
		WALK_UP = 3,
		WALK_DOWN = 4
	};

	bool MO_LoadImg(std::string path, SDL_Renderer* screen);
	void Show(SDL_Renderer* des);
	void HandleInputAction(SDL_Event &events, SDL_Renderer* screen);
	void Set_Clip();
	void HandleMove(Map& map_data);
	void CheckToMap(Map& map_data);

//	SDL_TimerCallback BombTimerCallBack();
//	void UnlockBombPlacement() { can_place_bomb = true; }
	void set_bomb_list(std::vector<Bomb*> bomb_list)
	{
		p_bomb_list_ = bomb_list;
	}

	std::vector<Bomb*> get_bom_list() const { return p_bomb_list_; }
private:
	/*bool can_place_bomb;*/
	std::vector<Bomb*> p_bomb_list_;

	float x_val_;
	float y_val_;

	float x_pos_;
	float y_pos_;

	int width_frame_;
	int height_frame_;

	SDL_Rect frame_clip_[4];
	Input input_type_;
	int frame_;
	int status_;
};
 
#endif // !MAIN_OBJECT_H
