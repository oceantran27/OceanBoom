#include "Bomb.h"

#define EXPLOSION_TIME 2500


Bomb::Bomb()
{
	m_timer_id = 0;
	frame = 0;
}

Bomb::~Bomb()
{
 //
}

void Bomb::Plant(const float& x_num_tile_, const float& y_num_tile_) {
    if (!IsActive()) {
        StartTimer();
		LoadClipImg("Images/bomb.png");
		SetClip();
		x_pos = x_num_tile_ * TILE_SIZE + 1.5 * ERROR_NUM;
		y_pos = y_num_tile_ * TILE_SIZE;
		x_num_tile = x_num_tile_;
		y_num_tile = y_num_tile_;
    }
}

void Bomb::Explode() {
	for (int i = -bomb_power; i <= bomb_power; i++) {
		int x1 = x_num_tile + i;
		int y1 = y_num_tile + i;

		//if (map_data.tile_map[y1][x_num_tile] != BLANK_TILE &&
		//	map_data.tile_map[y1][x_num_tile] != LIMIT_TILE &&
		//	map_data.tile_map[y1][x_num_tile] != BLOCK_TILE &&
		//	map_data.tile_map[y1][x_num_tile] != BOMB_PLANTED)
		//{
		//	map_data.tile_map[y1][x_num_tile] = BLANK_TILE;
		//	//std::cout << x_num_tile << " " << y1 << std::endl;
		//}

		//if (map_data.tile_map[y_num_tile][x1] != BLANK_TILE &&
		//	map_data.tile_map[y_num_tile][x1] != LIMIT_TILE &&
		//	map_data.tile_map[y_num_tile][x1] != BLOCK_TILE &&
		//	map_data.tile_map[y_num_tile][x1] != BOMB_PLANTED)
		//{
		//	map_data.tile_map[y_num_tile][x1] = BLANK_TILE;
		//	//std::cout << x1 << " " << y_num_tile << std::endl;
		//}
	}
	StopTimer();
}

Uint32 Bomb::TimerCallback(Uint32 interval, void* param) {
    Bomb* bomb_ = static_cast<Bomb*>(param);
    bomb_->Explode();
    return 0;
}

void Bomb::StartTimer() {
    m_timer_id = SDL_AddTimer(EXPLOSION_TIME, TimerCallback, this);
}

void Bomb::StopTimer() {
    SDL_RemoveTimer(m_timer_id);
    m_timer_id = 0;
}

bool Bomb::LoadClipImg(std::string path)
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





