#include "Bomb.h"

#define BOMB_EXIST_TIME 2500
#define EXPLOSION_TIME 800


Bomb::Bomb()
{
	lim = true;
	timer_exist_bomb = 0;
	frame = 0;
	max_right = 0;
	max_left = 0;
	max_top = 0;
	max_bot = 0;
}

Bomb::~Bomb()
{
 //
}

void Bomb::Plant(const int& x_, const int& y_) {
    if (timer_exist_bomb == 0) {
        StartTimer();
		LoadClipImg("Images/bomb.png");
		SetClip();
		x = x_;
		y = y_;
    }
}

void Bomb::StartTimer() {
	timer_exist_bomb = SDL_GetTicks() + BOMB_EXIST_TIME;
	timer_explode = timer_exist_bomb + EXPLOSION_TIME;
}

bool Bomb::LoadClipImg(std::string path)
{
	bool ret = BaseObject::LoadImg(path, screen);
	if (ret == false)
	{
		return false;
	}

	width_frame = rect.w / BOMB_FRAMES;
	height_frame = rect.h;

	return true;
}

void Bomb::SetClip()
{
	if (width_frame > 0 && height_frame > 0)
	{
		for (int i = 0; i < BOMB_FRAMES; i++)
		{
			frame_clip[i].x = i * width_frame;
			frame_clip[i].y = 0;
			frame_clip[i].w = width_frame;
			frame_clip[i].h = height_frame;
		}
	}
}

void Bomb::DisplayBomb(SDL_Renderer* des)
{
	if (frame >= BOMB_FRAMES)
	{
		frame = 0;
	}
	SDL_Rect* current_clip = &frame_clip[frame];
	SDL_Rect renderQuad = { x*TILE_SIZE, y*TILE_SIZE, width_frame, height_frame };
	SDL_RenderCopy(des, pObject, current_clip, &renderQuad);
	frame++;
}

void Bomb::DisplayExplosion(SDL_Renderer* des)
{
	SetRect(x * TILE_SIZE, y * TILE_SIZE);
	LoadImg("Images/explode.png", screen);
	Render(des);

	for (int i = max_left; i <= max_right; i++)
	{
		if (i == 0)
		{
			continue;
		}
		SetRect((x + i)*TILE_SIZE, y * TILE_SIZE);
		LoadImg("Images/explode_x.png", screen);
		Render(des);
	}

	for (int i = max_top; i <= max_bot; i++)
	{
		if (i == 0)
		{
			continue;
		}
		SetRect(x * TILE_SIZE, (y + i) * TILE_SIZE);
		LoadImg("Images/explode_y.png", screen);
		Render(des);
	}
}





