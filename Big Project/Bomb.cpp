#include "Bomb.h"

Bomb::Bomb()
{
	limit_explode = true;
	timer_exist_bomb = 0;
	frame = 0;
	max_right = 0;
	max_left = 0;
	max_top = 0;
	max_bot = 0;
	count = 0;
}

Bomb::~Bomb()
{
	SDL_RemoveTimer(timer_exist_bomb);
	SDL_RemoveTimer(timer_explode);
}

void Bomb::StartTimer() {
	timer_exist_bomb = SDL_GetTicks() + BOMB_EXIST_TIME;
	timer_explode = timer_exist_bomb + EXPLOSION_TIME;
}

bool Bomb::loadClipImg(std::string path)
{
	bool ret = BaseObject::loadImg(path, screen);
	if (ret == false)
	{
		return false;
	}

	width_frame = rect.w / BOMB_FRAMES;
	height_frame = rect.h;

	return true;
}

void Bomb::setClip()
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

void Bomb::displayBomb(SDL_Renderer* des)
{
	if (frame >= BOMB_FRAMES)
	{
		frame = 0;
	}
	SDL_Rect* current_clip = &frame_clip[frame];
	SDL_Rect renderQuad = { x*CELL_SIZE, y*CELL_SIZE, width_frame, height_frame };
	SDL_RenderCopy(des, pObject, current_clip, &renderQuad);
	if (count % 2 == 0)
	{
		frame++;
	}
	count++;

	current_clip = NULL;
	delete(current_clip);
}

void Bomb::displayExplosion(SDL_Renderer* des)
{
	setRect(x * CELL_SIZE, y * CELL_SIZE);
	loadImg("Bomb/explode_.png", des);
	Render(des);

	for (int i = max_left; i <= max_right; i++)
	{
		if (i == 0)
		{
			continue;
		}
		setRect((x + i) * CELL_SIZE, y * CELL_SIZE);
		loadImg("Bomb/explode_x_.png", des);
		Render(des);
	}

	for (int i = max_top; i <= max_bot; i++)
	{
		if (i == 0)
		{
			continue;
		}
		setRect(x * CELL_SIZE, (y + i) * CELL_SIZE);
		loadImg("Bomb/explode_y_.png", des);
		Render(des);
	}

	//std::cout << "max_left = " << max_left << std::endl;
	//std::cout << "max_right = " << max_right << std::endl;
	//std::cout << "max_top = " << max_top << std::endl;
	//std::cout << "max_bot = " << max_bot << std::endl;
	//std::cout << "--------------------------------------------\n";
}

void Bomb::clearBomb(Map& main_map_, Map& item_map_)
{
	for (int i = max_left; i <= max_right; i++)
	{
		main_map_.tile_map[y][x + i] = BLANK_CELL;
		
	}
	for (int i = max_top; i <= max_bot; i++)
	{
		main_map_.tile_map[y + i][x] = BLANK_CELL;
	}
}

void Bomb::plantBomb(const int& x_, const int& y_) {
	if (timer_exist_bomb == 0) {
		StartTimer();
		loadClipImg("Bomb/bomb.png");
		setClip();
		x = x_;
		y = y_;
	}
}





