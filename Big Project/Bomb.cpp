#include "Bomb.h"

#define EXPLOSION_TIME 2000


Bomb::Bomb()
{
	m_timer_id = 0;
	frame = 0;
}

Bomb::~Bomb()
{
	//
}


void Bomb::plant(const float& x_num_tile_, const float& y_num_tile_, SDL_Renderer* screen) {
    if (!is_active()) {
        start_timer();
		LoadClipImg("Images/bomb.png", screen);
		SetClip();
		x_pos = x_num_tile_ * TILE_SIZE + 1.5 * ERROR_NUM;
		y_pos = y_num_tile_ * TILE_SIZE;
		x_num_tile = x_num_tile_;
		y_num_tile = y_num_tile_;
    }
}

void Bomb::explode() {
    stop_timer();
    printf("Bom exploded!\n");
}

Uint32 Bomb::timer_callback(Uint32 interval, void* param) {
    Bomb* bom = static_cast<Bomb*>(param);
    bom->explode();
    return 0;
}

void Bomb::start_timer() {
    m_timer_id = SDL_AddTimer(2000, timer_callback, this);
}

void Bomb::stop_timer() {
    SDL_RemoveTimer(m_timer_id);
    m_timer_id = 0;
}

bool Bomb::LoadClipImg(std::string path, SDL_Renderer* screen)
{
	bool ret = BaseObject::LoadImg(path, screen);
	if (ret == false)
	{
		return false;
	}

	width_frame = rect.w / 4;
	height_frame = rect.h;

	return true;
}

void Bomb::SetClip()
{
	if (width_frame > 0 && height_frame > 0)
	{
		for (int i = 0; i < 4; i++)
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
	if (frame >= 4)
	{
		frame = 0;
	}
	SDL_Rect* current_clip = &frame_clip[frame];
	SDL_Rect renderQuad = { x_pos, y_pos, width_frame, height_frame };
	SDL_RenderCopy(des, pObject, current_clip, &renderQuad);
	frame++;
}





