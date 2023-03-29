#include "Map.h"



void GameMap::LoadMap(const char* name)
{
	FILE *fp = NULL;
	fopen_s(&fp, name, "rb");

	if (fp == NULL)
	{	
		return;
	}

	map_.max_x = 0; 
	map_.max_y = 0;

	for (int i = 0; i < MAX_MAP_Y; i++)
	{
		for (int j = 0; j < MAX_MAP_X; j++)
		{
			fscanf_s(fp, "%d", &map_.tile_map[i][j]);

			map_.max_x = (j > map_.max_x) ? j : map_.max_x;
			map_.max_y = (i > map_.max_y) ? i : map_.max_y;
		}
	}
	map_.max_x = (map_.max_x + 1) * TILE_SIZE;
	map_.max_y = (map_.max_y + 1) * TILE_SIZE;

	map_.start_x = 0; 
	map_.start_y = 0;

	fclose(fp);
}

void GameMap::LoadTiles(SDL_Renderer* screen)
{
	std::string fileImg;
	FILE* fp = NULL;
	for (int i = 0; i < MAX_TILES; i++)
	{
		char numImg = i + '0';
		fileImg = "Images/background ";
		fileImg = fileImg + numImg;
		fileImg = fileImg + ".png";
		fopen_s(&fp, fileImg.c_str(), "rb");

		if (fp == NULL)
			continue;

		fclose(fp);

		tiles[i].LoadImg(fileImg, screen);
	}
}

void GameMap::DrawMap(SDL_Renderer* screen)
{
	int x1 = 0;
	int x2 = x1 + SCREEN_WIDTH;

	int y1 = 0;
	int y2 = y1 + SCREEN_HEIGHT;

	int map_x = map_.start_x/TILE_SIZE;
	int map_y = map_.start_y / TILE_SIZE;

	for (int i = y1; i < y2; i += TILE_SIZE)
	{
		map_x = map_.start_x / TILE_SIZE;
		for (int j = x1; j < x2; j += TILE_SIZE)
		{
			int val = map_.tile_map[map_y][map_x];
			if (val < BLANK_TILE)
			{
				val = BLANK_TILE;
			}
			tiles[val].SetRect(j, i);
			tiles[val].Render(screen);
			map_x++;
		}
		map_y++;
	}
}