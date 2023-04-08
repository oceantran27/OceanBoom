#include "Enemy.h"

Enemy::Enemy()
{
	//enemy_speed;

	x_val = 0;
	y_val = 0;

	x_pos = 0;
	y_pos = 0;

	width_frame = 0;
	height_frame = 0;

	//frame = 0;
	type = -1;

	status = 0;
	timer_keep_direction = 0;
}

Enemy::~Enemy()
{
	//
}

//bool Enemy::LoadClipImg(std::string path, SDL_Renderer* screen)
//{
//	bool ret = BaseObject::LoadImg(path, screen);
//	if (ret == false)
//	{
//		return false;
//	}
//
//	width_frame = rect.w / ENEMY_FRAMES;
//	height_frame = rect.h;
//
//	return true;
//}
//
//void Enemy::SetClip()
//{
//	if (width_frame > 0 && height_frame > 0)
//	{
//		for (int i = 0; i < ENEMY_FRAMES; i++)
//		{
//			frame_clip[i].x = i * width_frame;
//			frame_clip[i].y = 0;
//			frame_clip[i].w = width_frame;
//			frame_clip[i].h = height_frame;
//		}
//	}
//}
	
void Enemy::EnemyShow(SDL_Renderer* des)
{
	switch (type)
	{
	case 1:
		if (status == WALK_NONE)
		{
			LoadImg("Enemy/1_Down.png", des);
		}
		else if (status == WALK_LEFT)
		{
			LoadImg("Enemy/1_Left.png", des);
		}
		else if (status == WALK_RIGHT)
		{
			LoadImg("Enemy/1_Right.png", des);
		}
		else if (status == WALK_UP)
		{
			LoadImg("Enemy/1_Up.png", des);
		}
		else if (status == WALK_DOWN)
		{
			LoadImg("Enemy/1_Down.png", des);
		}
		break;

	case 2:
		if (status == WALK_NONE)
		{
			LoadImg("Enemy/2_Down.png", des);
		}
		else if (status == WALK_LEFT)
		{
			LoadImg("Enemy/2_Left.png", des);
		}
		else if (status == WALK_RIGHT)
		{
			LoadImg("Enemy/2_Right.png", des);
		}
		else if (status == WALK_UP)
		{
			LoadImg("Enemy/2_Up.png", des);
		}
		else if (status == WALK_DOWN)
		{
			LoadImg("Enemy/2_Down.png", des);
		}
		break;

	case 3:
		if (status == WALK_NONE)
		{
			LoadImg("Enemy/3_Down.png", des);
		}
		else if (status == WALK_LEFT)
		{
			LoadImg("Enemy/3_Left.png", des);
		}
		else if (status == WALK_RIGHT)
		{
			LoadImg("Enemy/3_Right.png", des);
		}
		else if (status == WALK_UP)
		{
			LoadImg("Enemy/3_Up.png", des);
		}
		else if (status == WALK_DOWN)
		{
			LoadImg("Enemy/3_Down.png", des);
		}
		break;
	}

	width_frame = rect.w;
	height_frame = rect.h;
	rect.x = x_pos;
	rect.y = y_pos;

	SDL_Rect renderQuad = { rect.x, rect.y, width_frame, height_frame };
	SDL_RenderCopy(des, pObject, NULL, &renderQuad);
}

void Enemy::CheckToMap(Map& main_map_)
{
	int old_x_pos = x_pos;
	int old_y_pos = y_pos;

	x_pos += x_val;
	y_pos += y_val;

	int x1, x2;
	int y1, y2;

	//Check for collision of player and obstacles

	x1 = (x_pos + ERROR_NUM) / TILE_SIZE;
	x2 = (x_pos + width_frame - ERROR_NUM) / TILE_SIZE;

	y1 = (y_pos + ERROR_NUM) / TILE_SIZE;
	y2 = (y_pos + height_frame - ERROR_NUM) / TILE_SIZE;

	int main_top_right = main_map_.tile_map[y1][x2];
	int main_bot_right = main_map_.tile_map[y2][x2];
	int main_top_left = main_map_.tile_map[y1][x1];
	int main_bot_left = main_map_.tile_map[y2][x1];

	bool check_main_top_right = main_top_right != BLANK_TILE;
	bool check_main_top_left = main_top_left != BLANK_TILE;
	bool check_main_bot_right = main_bot_right != BLANK_TILE;
	bool check_main_bot_left = main_bot_left != BLANK_TILE;

	//move right
	if (x_val > 0)
	{
		if (check_main_top_right || check_main_bot_right)
		{
				x_pos = old_x_pos;
				x_val = 0;
				status = WALK_LEFT;
		}
	}
	//move left
	else if (x_val < 0)
	{
		if (check_main_top_left || check_main_bot_left)
		{
				x_pos = old_x_pos;
				x_val = 0;
				status = WALK_RIGHT;
		}
	}
	//move up
	else if (y_val > 0)
	{
		if (check_main_bot_right || check_main_bot_left)
		{
				y_pos = old_y_pos;
				y_val = 0;
				status = WALK_DOWN;
		}
	}
	//move down
	else if (y_val < 0)
	{
		if (check_main_top_right || check_main_top_left)
		{
				y_pos = old_y_pos;
				y_val = 0;
				status = WALK_UP;
		}
	}
}

void Enemy::HandleMove(Map& main_map_)
{
	timer_keep_direction++;
	x_val = 0;
	y_val = 0;

	srand(SDL_GetTicks());
	int random_number = 20 + rand() % 50;
	if (timer_keep_direction > random_number)
	{
		status = rand() % 4 + 1;
		timer_keep_direction = 0;
	}
		if (status == WALK_LEFT)
		{
			x_val -= enemy_speed[type];
		}
		else if (status == WALK_RIGHT)
		{
			x_val += enemy_speed[type];
		}
		else if (status == WALK_UP)
		{
			y_val -= enemy_speed[type];
		}
		else if (status == WALK_DOWN)
		{
			y_val += enemy_speed[type];
		}

		CheckToMap(main_map_);
}