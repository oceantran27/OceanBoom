#include "Bomb.h"

#define EXPLOSION_TIME 2500


Bomb::Bomb()
{
	timer_id = 0;
	frame = 0;
}

Bomb::~Bomb()
{
 //
}

void Bomb::Plant(const int& x_, const int& y_) {
    if (timer_id == 0) {
        StartTimer();
		LoadClipImg("Images/bomb.png");
		SetClip();
		x_pos = x_ * TILE_SIZE;
		y_pos = y_ * TILE_SIZE;
    }
}

void Bomb::StartTimer() {
	timer_id = SDL_GetTicks() + EXPLOSION_TIME;
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

void Bomb::Show(SDL_Renderer* des)
{
	if (frame >= BOMB_FRAMES)
	{
		frame = 0;
	}
	SDL_Rect* current_clip = &frame_clip[frame];
	SDL_Rect renderQuad = { x_pos, y_pos, width_frame, height_frame };
	SDL_RenderCopy(des, pObject, current_clip, &renderQuad);
	frame++;
}





