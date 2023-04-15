#include "Bomber.h"

#define LIMIT_LAG 15

Bomber::Bomber()
{
	frame = 0;

	bomb_limit = 1;
	bomb_power = 1;
	player_speed = 4;

	x_val = 0;
	y_val = 0;

	width_frame = 0;
	height_frame = 0;

	status = WALK_NONE;
	input_type.left = 0;
	input_type.right = 0;
	input_type.up = 0;
	input_type.down = 0;

	x_pos = 0;
	y_pos = 0;
}

Bomber::~Bomber()
{
	pbomb_list.clear();
}

bool Bomber::LoadClipImg(std::string path, SDL_Renderer* screen)
{
	bool ret = BaseObject::LoadImg(path, screen);
	if (ret == false)
	{
		return false;
	}

	width_frame = rect.w / BOMBER_FRAMES;
	height_frame = rect.h;

	return true;
}

void Bomber::SetClip()
{
	if (width_frame > 0 && height_frame > 0)
	{
		for (int i = 0; i < BOMBER_FRAMES; i++)
		{
			frame_clip[i].x = i*width_frame;
			frame_clip[i].y = 0;
			frame_clip[i].w = width_frame;
			frame_clip[i].h = height_frame;
		}
	}
}

void Bomber::BomberShow(SDL_Renderer* des)
{
	if (status == WALK_NONE)
	{
		LoadClipImg("Bomber/down.png", des);
	}
	else if (status == WALK_LEFT)
	{
		LoadClipImg("Bomber/left.png", des);
	}
	else if (status == WALK_RIGHT)
	{
		LoadClipImg("Bomber/right.png", des);
	}
	else if (status == WALK_UP)
	{
		LoadClipImg("Bomber/up.png", des);
	}
	else if (status == WALK_DOWN)
	{
		LoadClipImg("Bomber/down.png", des);
	}

	SetClip();

	if (input_type.left == 1 ||
		input_type.right == 1 ||
		input_type.up == 1 ||
		input_type.down == 1)
	{
		frame++;
	}
	else
	{
		frame = 0;
	}

	if (frame >= BOMBER_FRAMES)
		frame = 0;

	rect.x = x_pos;
	rect.y = y_pos;

	SDL_Rect* current_clip = &frame_clip[frame];
	SDL_Rect renderQuad = { rect.x, rect.y, width_frame, height_frame };
	SDL_RenderCopy(des, pObject, current_clip, &renderQuad);
}

void Bomber::HandleInputAction(SDL_Event &event, SDL_Renderer* screen, Map& main_map_)
{
	if (event.type == SDL_KEYDOWN)
	{
		switch (event.key.keysym.sym)
		{
		case SDLK_LEFT:
		{
			status = WALK_LEFT;
			input_type.left = 1;
			input_type.right = 0;
			input_type.up = 0;
			input_type.down = 0;
		}
		break;

		case SDLK_RIGHT:
		{
			status = WALK_RIGHT;
			input_type.left = 0;
			input_type.right = 1;
			input_type.up = 0;
			input_type.down = 0;
		}
		break;

		case SDLK_UP:
		{
			status = WALK_UP;
			input_type.left = 0;
			input_type.right = 0;
			input_type.up = 1;
			input_type.down = 0;
		}
		break;

		case SDLK_DOWN:
		{
			status = WALK_DOWN;
			input_type.left = 0;
			input_type.right = 0;
			input_type.up = 0;
			input_type.down = 1;

		}
		break;
		}
	}

	if (event.type == SDL_KEYUP)
	{
		switch (event.key.keysym.sym)
		{
		case SDLK_LEFT:
		{
			input_type.left = 0;
		}
		break;

		case SDLK_RIGHT:
		{
			input_type.right = 0;
		}
		break;

		case SDLK_UP:
		{
			input_type.up = 0;
		}
		break;

		case SDLK_DOWN:
		{
			input_type.down = 0;
		}
		break;

		case SDLK_SPACE:
		{
			if (pbomb_list.size() < bomb_limit)
			{
				int x, y;
				if (status == WALK_LEFT)
				{
					x = ((x_pos + width_frame - ERROR_NUM) / TILE_SIZE);
				}
				else
				{
					x = ((x_pos + ERROR_NUM) / TILE_SIZE);
				}
				y = ((y_pos + 0.7 * height_frame - ERROR_NUM) / TILE_SIZE);

				if (main_map_.tile_map[y][x] == BLANK_TILE)
				{
					Bomb* pbomb = new Bomb();
					pbomb->SetScreen(screen);
					pbomb->Plant(x, y);
					pbomb_list.push_back(pbomb);
					main_map_.tile_map[y][x] = BOMB_PLANTED;
				}
			}
		}
		break;
		}
	}
}

void Bomber::HandleMove(Map& main_map_, Map& item_map_)
{
	x_val = 0;
	y_val = 0;
	if (input_type.left == 1)
	{
		x_val -= player_speed;
	}
	else if (input_type.right == 1)
	{
		x_val += player_speed;
	}
	else if (input_type.up == 1)
	{
		y_val -= player_speed;
	}
	else if (input_type.down == 1)
	{
		y_val += player_speed;
	}
	CheckToMap(main_map_, item_map_);
}

void Bomber::CheckToMap(Map& main_map_, Map& item_map_)
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
	
	bool check_main_top_right = main_top_right != BLANK_TILE && main_top_right != BOMB_PLANTED;
	bool check_main_top_left = main_top_left != BLANK_TILE && main_top_left != BOMB_PLANTED;
	bool check_main_bot_right = main_bot_right != BLANK_TILE && main_bot_right != BOMB_PLANTED;
	bool check_main_bot_left = main_bot_left != BLANK_TILE && main_bot_left != BOMB_PLANTED;

	//move right
	if (x_val > 0)
	{
		if (check_main_top_right || check_main_bot_right)
		{
			int foot_lag_part = y_pos + height_frame - (y1 + 1) * TILE_SIZE;
			int head_lag_part = (y1 + 1) * TILE_SIZE - y_pos;
			if (foot_lag_part <= LIMIT_LAG && foot_lag_part >= 0
				&& check_main_bot_right && main_map_.tile_map[y2 - 1][x1 + 1] == BLANK_TILE)
			{
				y_pos -= foot_lag_part + ERROR_NUM;
				int y3 = y_pos / TILE_SIZE;
			}
			else if (head_lag_part <= LIMIT_LAG && head_lag_part > 0
				&& check_main_top_right && main_map_.tile_map[y1 + 1][x1 + 1] == BLANK_TILE)
			{
				y_pos += head_lag_part + ERROR_NUM;
			}
			else
			{
				x_pos = old_x_pos;
				x_val = 0;
			}
		}

	}
	//move left
	else if (x_val < 0)
	{
		if (check_main_top_left || check_main_bot_left)
		{
			int foot_lag_part = y_pos + height_frame - (y1 + 1) * TILE_SIZE;
			int head_lag_part = (y1 + 1) * TILE_SIZE - y_pos;
			if (foot_lag_part <= LIMIT_LAG && foot_lag_part >= 0
				&& check_main_bot_left && main_map_.tile_map[y2 - 1][x2 - 1] == BLANK_TILE)
			{
				y_pos -= foot_lag_part + ERROR_NUM;
			}
			else if (head_lag_part <= LIMIT_LAG && head_lag_part > 0
				&& check_main_top_left && main_map_.tile_map[y1 + 1][x2 - 1] == BLANK_TILE)
			{
				y_pos += head_lag_part + ERROR_NUM;
			}
			else
			{
				x_pos = old_x_pos;
				x_val = 0;
			}
		}
	}
	//move up
	if (y_val > 0)
	{
		if (check_main_bot_right || check_main_bot_left)
		{
			int foot_right_lag_part = x_pos + width_frame - (x1 + 1) * TILE_SIZE;
			int foot_left_lag_part = (x1 + 1) * TILE_SIZE - x_pos;
			if (foot_left_lag_part <= LIMIT_LAG && foot_left_lag_part >= 0
				&& check_main_bot_left && main_map_.tile_map[y1 + 1][x2] == BLANK_TILE)
			{
				x_pos += foot_left_lag_part + ERROR_NUM;
			}
			else if (foot_right_lag_part <= LIMIT_LAG && foot_right_lag_part > 0
				&& check_main_bot_right && main_map_.tile_map[y1 + 1][x1] == BLANK_TILE)
			{
				x_pos -= foot_right_lag_part + ERROR_NUM;
			}
			else
			{
				y_pos = old_y_pos;
				y_val = 0;
			}
		}
	}
	//move down
	else if (y_val < 0)
	{
		if (check_main_top_right || check_main_top_left)
		{
			int head_right_lag_part = x_pos + width_frame - (x1 + 1) * TILE_SIZE;
			int head_left_lag_part = (x1 + 1) * TILE_SIZE - x_pos;
			if (head_left_lag_part <= LIMIT_LAG && head_left_lag_part >= 0
				&& check_main_top_left && main_map_.tile_map[y2 - 1][x2] == BLANK_TILE)
			{
				x_pos += head_left_lag_part + ERROR_NUM;
			}
			else if (head_right_lag_part <= LIMIT_LAG && head_right_lag_part > 0
				&& check_main_top_right && main_map_.tile_map[y2 - 1][x1] == BLANK_TILE)
			{
				x_pos -= head_right_lag_part + ERROR_NUM;
			}
			else
			{
				y_pos = old_y_pos;
				y_val = 0;
			}
		}
	}


	//Check for collision of player and items
	x1 = (x_pos + 3*ERROR_NUM) / TILE_SIZE;
	x2 = (x_pos + width_frame - 3*ERROR_NUM) / TILE_SIZE;

	y1 = (y_pos + 3*ERROR_NUM) / TILE_SIZE;
	y2 = (y_pos + height_frame - 3*ERROR_NUM) / TILE_SIZE;

	int item_top_right = item_map_.tile_map[y1][x2];
	int item_bot_right = item_map_.tile_map[y2][x2];
	int item_top_left = item_map_.tile_map[y1][x1];
	int item_bot_left = item_map_.tile_map[y2][x1];

	if (item_top_left == BOMB_UP || item_bot_left == BOMB_UP || item_top_right == BOMB_UP || item_bot_right == BOMB_UP)
	{
		IncreaseBombLimit();
	}
	if (item_top_left == POWER_UP || item_bot_left == POWER_UP || item_top_right == POWER_UP || item_bot_right == POWER_UP)
	{
		IncreaseBombPower();
	}
	if (item_top_left == SPEED_UP || item_bot_left == SPEED_UP || item_top_right == SPEED_UP || item_bot_right == SPEED_UP)
	{
		IncreasePlayerSpeed();
	}

	if (item_top_left != BLANK_ITEM)
	{
		item_map_.tile_map[y1][x1] = BLANK_ITEM;
	}
	if (item_bot_left != BLANK_ITEM)
	{
		item_map_.tile_map[y2][x1] = BLANK_ITEM;
	}
	if (item_top_right != BLANK_ITEM)
	{
		item_map_.tile_map[y1][x2] = BLANK_ITEM;
	}
	if (item_bot_right != BLANK_ITEM)
	{
		item_map_.tile_map[y2][x2] = BLANK_ITEM;
	}

	//Check for collision of player and bombs 
	if (pbomb_list.size() != 0)
	{
		for (auto bomb : pbomb_list)
		{
			int bomb_x = bomb->GetX();
			int bomb_y = bomb->GetY();
			int bomb_x_pos = bomb_x * TILE_SIZE;
			int bomb_y_pos = bomb_y * TILE_SIZE;

			if ((y_pos + height_frame < bomb_y_pos) ||
				(y_pos > bomb_y_pos + TILE_SIZE) ||
				(x_pos + width_frame < bomb_x_pos) ||
				(x_pos > bomb_x_pos + TILE_SIZE))
			{
				main_map_.tile_map[bomb_y][bomb_x] = BLOCK_TILE;
			}
		}
	}
}

void Bomber::BombExplode(SDL_Renderer* des, Bomb* bomb_,
						 Map& main_map_, Map& item_map_)
{
	int x = bomb_->GetX();
	int y = bomb_->GetY(); 

	if (bomb_->GetLim())
	{
		for (int i = -1; i >= -bomb_power; i--)
		{
			int x1 = x + i;

			if (main_map_.tile_map[y][x1] <= 10 && main_map_.tile_map[y][x1] > 0)
			{
				break;
			}

			bomb_->SetLeft(i);

			if (/*main_map_.tile_map[y][x1] != BLOCK_TILE &&*/
				main_map_.tile_map[y][x1] != BOMB_PLANTED)
			{
				main_map_.tile_map[y][x1] = DEAD_TILE;
				break;
			}

			if (item_map_.tile_map[y][x1] != BLANK_ITEM)
			{
				item_map_.tile_map[y][x1] = BLANK_ITEM;
			}
		}

		for (int i = 1; i <= bomb_power; i++)
		{
			int x1 = x + i;

			if (main_map_.tile_map[y][x1] <= NUMBER_OF_LIMIT_TILE && main_map_.tile_map[y][x1] > 0)
			{
				break;
			}

			bomb_->SetRight(i);

			if (/*main_map_.tile_map[y][x1] != BLOCK_TILE &&*/
				main_map_.tile_map[y][x1] != BOMB_PLANTED)
			{
				main_map_.tile_map[y][x1] = DEAD_TILE;
				break;
			}

			if (item_map_.tile_map[y][x1] != BLANK_ITEM)
			{
				item_map_.tile_map[y][x1] = BLANK_ITEM;
			}
		}

		for (int i = -1; i >= -bomb_power; i--)
		{
			int y1 = y + i;

			if (main_map_.tile_map[y1][x] <= 10 && main_map_.tile_map[y1][x] > 0)
			{
				break;
			}

			bomb_->SetTop(i);

			if (/*main_map_.tile_map[y1][x] != BLOCK_TILE &&*/
				main_map_.tile_map[y1][x] != BOMB_PLANTED)
			{
				main_map_.tile_map[y1][x] = DEAD_TILE;
				break;
			}

			if (item_map_.tile_map[y1][x] != BLANK_ITEM)
			{
				item_map_.tile_map[y1][x] = BLANK_ITEM;
			}
		}

		for (int i = 1; i <= bomb_power; i++)
		{
			int y1 = y + i;

			if (main_map_.tile_map[y1][x] <= 10 && main_map_.tile_map[y1][x] > 0)
			{
				break;
			}

			bomb_->SetBot(i);

			if (/*main_map_.tile_map[y1][x] != BLOCK_TILE &&*/
				main_map_.tile_map[y1][x] != BOMB_PLANTED)
			{
				main_map_.tile_map[y1][x] = DEAD_TILE;
				break;
			}

			if (item_map_.tile_map[y1][x] != BLANK_ITEM)
			{
				item_map_.tile_map[y1][x] = BLANK_ITEM;
			}
		}

		main_map_.tile_map[y][x] = DEAD_TILE;
		bomb_->SetLim(false);
	}
	bomb_->DisplayExplosion(des);
}

void Bomber::BombShow(SDL_Renderer* des, Map& main_map_, Map& item_map_)
{
	for (int i = 0; i < pbomb_list.size(); i++)
	{
		SDL_TimerID current_timer_id = SDL_GetTicks();
		int bomb_x = pbomb_list[i]->GetX();
		int bomb_y = pbomb_list[i]->GetY();
		if (current_timer_id >= pbomb_list[i]->GetExplosionTimer())
		{
			//main_map_.tile_map[bomb_y][bomb_x] = DEAD_TILE;
			pbomb_list[i]->ClearBomb(main_map_);
			pbomb_list[i]->Free();
			pbomb_list[i] = NULL;
			delete pbomb_list[i];
			pbomb_list.erase(pbomb_list.begin() + i);
		}
		else if (current_timer_id >= pbomb_list[i]->GetBombTimer())
		{
			main_map_.tile_map[bomb_y][bomb_x] = DEAD_TILE;
			BombExplode(des, pbomb_list[i], main_map_, item_map_);
		}
		else
		{
			pbomb_list[i]->DisplayBomb(des);
		}
		SDL_RemoveTimer(current_timer_id);
	}
}