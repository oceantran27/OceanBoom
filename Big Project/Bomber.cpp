#include "Bomber.h"

#define PLAYER_SPEED 6


Bomber::Bomber()
{
	frame = 0;

	x_pos = 52;
	y_pos = 52;

	x_val = 0;
	y_val = 0;

	width_frame = 0;
	height_frame = 0;

	status = -1;
	input_type.left = 0;
	input_type.right = 0;
	input_type.up = 0;
	input_type.down = 0;

}

Bomber::~Bomber()
{

}

bool Bomber::LoadClipImg(std::string path, SDL_Renderer* screen)
{
	bool ret = BaseObject::LoadImg(path, screen);
	if (ret == false)
	{
		return false;
	}

	width_frame = rect.w / 3;
	height_frame = rect.h;

	return true;
}

void Bomber::SetClip()
{
	if (width_frame > 0 && height_frame > 0)
	{
		for (int i = 0; i < 3; i++)
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
	if (status == WALK_LEFT)
	{
		LoadClipImg("Images/left.png", des);
	}
	else if (status == WALK_RIGHT)
	{
		LoadClipImg("Images/right.png", des);
	}
	else if (status == WALK_UP)
	{
		LoadClipImg("Images/up.png", des);
	}
	else if (status == WALK_DOWN)
	{
		LoadClipImg("Images/down.png", des);
	}

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

	if (frame >= 3)
		frame = 0;

	rect.x = x_pos;
	rect.y = y_pos;

	SDL_Rect* current_clip = &frame_clip[frame];
	SDL_Rect renderQuad = { rect.x, rect.y, width_frame, height_frame };
	SDL_RenderCopy(des, pObject, current_clip, &renderQuad);
}

void Bomber::HandleInputAction(SDL_Event &event, SDL_Renderer* screen, Map& map_data)
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

		case SDLK_SPACE:
		{
			int x_num_tile = ((x_pos + ERROR_NUM) / TILE_SIZE);
			int y_num_tile = ((y_pos + 0.5*height_frame + ERROR_NUM) / TILE_SIZE);
			if (map_data.tile_map[y_num_tile][x_num_tile] == BLANK_TILE)
			{
				Bomb* pbomb = new Bomb();
				pbomb->SetScreen(screen);
				pbomb->SetMap(map_data);
				pbomb->Plant(x_num_tile, y_num_tile);
				pbomb_list.push_back(pbomb);
				map_data.tile_map[y_num_tile][x_num_tile] = BOMB_PLANTED;	
			}
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
		}
	}
}

void Bomber::HandleMove(Map& map_data)
{
	x_val = 0;
	y_val = 0;
	if (input_type.left == 1)
	{
		x_val -= PLAYER_SPEED;
	}
	else if (input_type.right == 1)
	{
		x_val += PLAYER_SPEED;
	}
	else if (input_type.up == 1)
	{
		y_val -= PLAYER_SPEED;
	}
	else if (input_type.down == 1)
	{
		y_val += PLAYER_SPEED;
	}
	CheckToMap(map_data);
}

void Bomber::CheckToMap(Map& map_data)
{
	int old_x_pos = x_pos;
	int old_y_pos = y_pos;

	x_pos += x_val;
	y_pos += y_val;

	int x1, x2;
	int y1, y2;

	x1 = (x_pos + ERROR_NUM) / TILE_SIZE;
	x2 = (x_pos + width_frame - ERROR_NUM) / TILE_SIZE;

	y1 = (y_pos + ERROR_NUM) / TILE_SIZE;
	y2 = (y_pos + height_frame - ERROR_NUM) / TILE_SIZE;

	int top_right = map_data.tile_map[y1][x2];
	int bot_right = map_data.tile_map[y2][x2];
	int top_left = map_data.tile_map[y1][x1];
	int bot_left = map_data.tile_map[y2][x1];
	
	bool check_top_right = top_right != BLANK_TILE && top_right != BOMB_PLANTED;
	bool check_top_left = top_left != BLANK_TILE && top_left != BOMB_PLANTED;
	bool check_bot_right = bot_right != BLANK_TILE && bot_right != BOMB_PLANTED;
	bool check_bot_left = bot_left != BLANK_TILE && bot_left != BOMB_PLANTED ;

	if (x_val > 0)
	{
		if (check_top_right || check_bot_right)
		{
			x_pos = old_x_pos;
			x_val = 0;
		}
	}
	else if (x_val < 0)
	{
		if (check_top_left || check_bot_left)
		{
			x_pos = old_x_pos;
			x_val = 0;
		}
	}

	if (y_val > 0)
	{
		if (check_bot_right || check_bot_left)
		{
			y_pos = old_y_pos;
			y_val = 0;
		}
	}
	else if (y_val < 0)
	{
		if (check_top_right || check_top_left)
		{
			y_pos = old_y_pos;
			y_val = 0;
		}
	}

	if (pbomb_list.size() != 0)
	{
		int bomb_x_pos = pbomb_list.back()->GetXNumTile();
		int bomb_y_pos = pbomb_list.back()->GetYNumTile();

		if ((x1 != bomb_x_pos || x2 != bomb_x_pos || y1 != bomb_y_pos || y2 != bomb_y_pos) 
			&& (x_val != 0 || y_val != 0))
		{
			map_data.tile_map[bomb_y_pos][bomb_x_pos] = BLOCK_TILE;
		}
	}
}

void Bomber::BombShow(SDL_Renderer* des, Map& map_data)
{
	for (int i = 0; i < pbomb_list.size(); i++)
	{
		if (!pbomb_list[i]->IsActive())
		{
			map_data.tile_map[pbomb_list[i]->GetYNumTile()][pbomb_list[i]->GetXNumTile()] = BLANK_TILE;
			delete pbomb_list[i];
			pbomb_list[i] = NULL;
			pbomb_list.erase(pbomb_list.begin() + i);
		}
		else
		{
			pbomb_list[i]->Show(des);
		}
	}
}



