#include "Map.h"

void GameMap::LoadMap(const char* name)
{
	FILE *fp = NULL;
	fopen_s(&fp, name, "rb");

	if (fp == NULL)
	{	
		return;
	}

	mMap.mMax_x = 0; 
	mMap.mMax_y = 0;

	for (int i = 0; i < MAX_MAP_Y; i++)
	{
		for (int j = 0; j < MAX_MAP_X; j++)
		{
			fscanf_s(fp, "%d", &mMap.mTileMap[i][j]);

			mMap.mMax_x = (j > mMap.mMax_x) ? j : mMap.mMax_x;
			mMap.mMax_y = (i > mMap.mMax_y) ? i : mMap.mMax_y;
		}
	}
	mMap.mMax_x = (mMap.mMax_x + 1) * TILE_SIZE;
	mMap.mMax_y = (mMap.mMax_y + 1) * TILE_SIZE;

	mMap.mStart_x = 0; 
	mMap.mStart_y = 0;

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

		mTiles[i].LoadImg(fileImg, screen);
	}
}

void GameMap::DrawMap(SDL_Renderer* screen)
{
	int x1 = 0;
	int x2 = x1 + SCREEN_WIDTH;

	int y1 = 0;
	int y2 = y1 + SCREEN_HEIGHT;

	int map_x = mMap.mStart_x/TILE_SIZE;
	int map_y = mMap.mStart_y / TILE_SIZE;

	for (int i = y1; i < y2; i += TILE_SIZE)
	{
		map_x = mMap.mStart_x / TILE_SIZE;
		for (int j = x1; j < x2; j += TILE_SIZE)
		{
			int val = mMap.mTileMap[map_y][map_x];
			mTiles[val].SetRect(j, i);
			mTiles[val].Render(screen);
			map_x++;
		}
		map_y++;
	}
}