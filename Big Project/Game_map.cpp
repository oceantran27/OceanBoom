#include "Game_map.h"

void GameMap::LoadMap(const char* name)
{
	FILE *fp = NULL;
	fopen_s(&fp, name, "rb");

	if (fp == NULL)
	{	
		return;
	}

	game_map_.max_x_ = 0; 
	game_map_.max_y_ = 0;

	for (int i = 0; i < MAX_MAP_Y; i++)
	{
		for (int j = 0; j < MAX_MAP_X; j++)
		{
			fscanf_s(fp, "%d", &game_map_.tile[i][j]);

			game_map_.max_x_ = (j > game_map_.max_x_) ? j : game_map_.max_x_;
			game_map_.max_y_ = (i > game_map_.max_y_) ? i : game_map_.max_y_;
		}
	}
	game_map_.max_x_ = (game_map_.max_x_ + 1) * TILE_SIZE;
	game_map_.max_y_ = (game_map_.max_y_ + 1) * TILE_SIZE;

	game_map_.start_x_ = 0; 
	game_map_.start_y_ = 0;

	/*game_map_.file_name_ = name;*/

	fclose(fp);
}

void GameMap::LoadTiles(SDL_Renderer* screen)
{
	std::string file_img;
	FILE* fp = NULL;
	for (int i = 0; i < MAX_TILES; i++)
	{
		char num_img = i + '0';
		file_img = "Images/background_";
		file_img = file_img + num_img;
		file_img = file_img + ".png";
		fopen_s(&fp, file_img.c_str(), "rb");

		if (fp == NULL)
			continue;

		fclose(fp);

		tile_mat[i].LoadImg(file_img, screen);
	}
}

void GameMap::DrawMap(SDL_Renderer* screen)
{
	int x1 = 0;
	int x2 = x1 + SCREEN_WIDTH;

	int y1 = 0;
	int y2 = y1 + SCREEN_HEIGHT;

	int map_x = game_map_.start_x_/TILE_SIZE;
	int map_y = game_map_.start_y_ / TILE_SIZE;

	for (int i = y1; i < y2; i += TILE_SIZE)
	{
		map_x = game_map_.start_x_ / TILE_SIZE;
		for (int j = x1; j < x2; j += TILE_SIZE)
		{
			int val = game_map_.tile[map_y][map_x];
			tile_mat[val].SetRect(j, i);
			tile_mat[val].Render(screen);
			map_x++;
		}
		map_y++;
	}
}