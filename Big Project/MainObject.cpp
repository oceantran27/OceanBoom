#include "MainObject.h"

#define BLANK_TILE 0
#define PLAYER_SPEED 0.3


MainObject::MainObject()
{
	frame_ = 0;
	x_pos_ = 52;
	y_pos_ = 52;
	x_val_ = 0;
	y_val_ = 0;
	width_frame_ = 0;
	height_frame_ = 0;
	status_ = -1;
	input_type_.left_ = 0;
	input_type_.right_ = 0;
	input_type_.up_ = 0;
	input_type_.down_ = 0;
}

MainObject::~MainObject()
{

}

bool MainObject::MO_LoadImg(std::string path, SDL_Renderer* screen)
{
	bool ret = BaseObject::LoadImg(path, screen);
	if (ret == false)
	{
		return false;
	}

	width_frame_ = rect_.w / 4;
	height_frame_ = rect_.h;
}

void MainObject::Set_Clip()
{
	if (width_frame_ > 0 && height_frame_ > 0)
	{
		for (int i = 0; i < 4; i++)
		{
			frame_clip_[i].x = i*width_frame_;
			frame_clip_[i].y = 0;
			frame_clip_[i].w = width_frame_;
			frame_clip_[i].h = height_frame_;
		}
	}
}

void MainObject::Show(SDL_Renderer* des)
{
	if (status_ == WALK_LEFT)
	{
		LoadImg("Images/left.png", des);
	}
	else if (status_ == WALK_RIGHT)
	{
		LoadImg("Images/right.png", des);
	}
	else if (status_ == WALK_UP)
	{
		LoadImg("Images/up.png", des);
	}
	else if (status_ == WALK_DOWN)
	{
		LoadImg("Images/down.png", des);
	}

	if (input_type_.left_ == 1 ||
		input_type_.right_ == 1 ||
		input_type_.up_ == 1 ||
		input_type_.down_ == 1)
	{
		frame_++;
	}
	else
	{
		frame_ = 0;
	}

	if (frame_ >= 4)
		frame_ = 0;

	rect_.x = x_pos_;
	rect_.y = y_pos_;

	SDL_Rect* current_clip = &frame_clip_[frame_];
	SDL_Rect renderQuad = { rect_.x, rect_.y, width_frame_, height_frame_ };
	SDL_RenderCopy(des, p_object_, current_clip, &renderQuad);
}

void MainObject::HandleInputAction(SDL_Event &event)
{
	if (event.type == SDL_KEYDOWN)
	{
		switch (event.key.keysym.sym)
		{
		case SDLK_LEFT:
		{
			status_ = WALK_LEFT;
			input_type_.left_ = 1;
			input_type_.right_ = 0;
			input_type_.up_ = 0;
			input_type_.down_ = 0;
		}
		break;

		case SDLK_RIGHT:
		{
			status_ = WALK_RIGHT;
			input_type_.left_ = 0;
			input_type_.right_ = 1;
			input_type_.up_ = 0;
			input_type_.down_ = 0;
		}
		break;

		case SDLK_UP:
		{
			status_ = WALK_UP;
			input_type_.left_ = 0;
			input_type_.right_ = 0;
			input_type_.up_ = 1;
			input_type_.down_ = 0;
		}
		break;

		case SDLK_DOWN:
		{
			status_ = WALK_DOWN;
			input_type_.left_ = 0;
			input_type_.right_ = 0;
			input_type_.up_ = 0;
			input_type_.down_ = 1;
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
			input_type_.left_ = 0;
		}
		break;

		case SDLK_RIGHT:
		{
			input_type_.right_ = 0;
		}
		break;

		case SDLK_UP:
		{
			input_type_.up_ = 0;
		}
		break;

		case SDLK_DOWN:
		{
			input_type_.down_ = 0;
		}
		break;
		}
	}

}

void MainObject::HandleMove(Map& map_data)
{
	x_val_ = 0;
	y_val_ = 0;
	if (input_type_.left_ == 1)
	{
		x_val_ -= PLAYER_SPEED;
	}
	else if (input_type_.right_ == 1)
	{
		x_val_ += PLAYER_SPEED;
	}
	else if (input_type_.up_ == 1)
	{
		y_val_ -= PLAYER_SPEED;
	}
	else if (input_type_.down_ == 1)
	{
		y_val_ += PLAYER_SPEED;
	}
	CheckToMap(map_data);
}

void MainObject::CheckToMap(Map& map_data)
{
	x_pos_ += x_val_;
	y_pos_ += y_val_;

	int x1, x2;
	int y1, y2;

	x1 = x_pos_ / TILE_SIZE;
	x2 = (x_pos_ + width_frame_ - 1) / TILE_SIZE;

	y1 = y_pos_ / TILE_SIZE;
	y2 = (y_pos_ + height_frame_ - 1) / TILE_SIZE;


	if (x_pos_ < TILE_SIZE || x_pos_ + width_frame_ + TILE_SIZE > map_data.max_x_)
	{
		x_pos_ -= x_val_;
	}
	if (y_pos_ < TILE_SIZE || y_pos_ + height_frame_ + TILE_SIZE > map_data.max_y_)
	{
		y_pos_ -= y_val_;
	}

	if (x_val_ > 0)
	{
		if (map_data.tile[y1][x2] != BLANK_TILE || map_data.tile[y2][x2] != BLANK_TILE)
		{
			x_pos_ = x2 * TILE_SIZE - width_frame_ - 1;
			x_val_ = 0;
		}
	}
	else if (x_val_ < 0)
	{
		if (map_data.tile[y1][x1] != BLANK_TILE || map_data.tile[y2][x1] != BLANK_TILE)
		{
			x_pos_ = (x1 + 1) * TILE_SIZE;
			x_val_ = 0;
		}
	}

	if (y_val_ > 0)
	{
		if (map_data.tile[y2][x1] != BLANK_TILE || map_data.tile[y2][x2] != BLANK_TILE)
		{
			y_pos_ = y2 * TILE_SIZE - height_frame_ - 1;
			y_val_ = 0;
		}
	}
	else if (y_val_ < 0)
	{
		if (map_data.tile[y1][x1] != BLANK_TILE || map_data.tile[y1][x2] != BLANK_TILE)
		{
			y_pos_ = (y1 + 1) * TILE_SIZE;
			y_val_ = 0;
		}
	}
}
