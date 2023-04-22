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
	loadImg("Bomb/mid.png", des);
	Render(des);

	setRect((x + max_left) * CELL_SIZE, y * CELL_SIZE);
	loadImg("Bomb/left_2.png", des);
	Render(des);

	setRect((x + max_right) * CELL_SIZE, y * CELL_SIZE);
	loadImg("Bomb/right_2.png", des);
	Render(des);

	setRect(x * CELL_SIZE, (y + max_top) * CELL_SIZE);
	loadImg("Bomb/top_2.png", des);
	Render(des);

	setRect(x * CELL_SIZE, (y + max_bot) * CELL_SIZE);
	loadImg("Bomb/bot_2.png", des);
	Render(des);

	if (max_left < -1)
	{
		for (int i = -1; i > max_left; i--)
		{
			setRect((x + i) * CELL_SIZE, y * CELL_SIZE);
			loadImg("Bomb/left_1.png", des);
			Render(des);
		}
	}

	if (max_right > 1)
	{
		for (int i = 1; i < max_right; i++)
		{
			setRect((x + i) * CELL_SIZE, y * CELL_SIZE);
			loadImg("Bomb/right_1.png", des);
			Render(des);
		}
	}

	if (max_top < -1)
	{
		for (int i = -1; i > max_top; i--)
		{
			setRect(x * CELL_SIZE, (y + i) * CELL_SIZE);
			loadImg("Bomb/top_1.png", des);
			Render(des);
		}
	}
	if (max_bot > 1)
	{
		for (int i = 1; i < max_bot; i++)
		{
			setRect(x * CELL_SIZE, (y + i) * CELL_SIZE);
			loadImg("Bomb/bot_1.png", des);
			Render(des);
		}
	}
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





