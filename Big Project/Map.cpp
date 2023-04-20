#include "Map.h"

void GameMap::loadMap(const char* name_game_map, const char* name_item_map)
{
	FILE* fp1 = NULL;
	FILE* fp2 = NULL;
	fopen_s(&fp1, name_game_map, "rb");
	fopen_s(&fp2, name_item_map, "rb");

	for (int i = 0; i < MAX_MAP_Y; i++)
	{
		for (int j = 0; j < MAX_MAP_X; j++)
		{
			fscanf_s(fp1, "%2d", &main_map_.tile_map[i][j]);
			fscanf_s(fp2, "%2d", &item_map_.tile_map[i][j]);
		}
	}

	main_map_.start_x = 0; 
	main_map_.start_y = 0;

	fclose(fp1);
	fclose(fp2);

	fp1 = NULL;
	fp2 = NULL;

	delete(fp1);
	delete(fp2);
}

void GameMap::loadTiles(SDL_Renderer* screen)
{
	std::string fileImg;
	FILE* fp1 = NULL;
	for (int i = 0; i < MAX_TILES; i++)
	{
		std::string numImg = std::to_string(i);
		fileImg = "Images/";
		fileImg = fileImg + numImg;
		fileImg = fileImg + ".png";
		fopen_s(&fp1, fileImg.c_str(), "rb");

		if (fp1 == NULL)
			continue;

		tiles[i].loadImg(fileImg, screen);
		fclose(fp1);
		fp1 = NULL;
		delete(fp1);
	}
}

void GameMap::drawMap(SDL_Renderer* screen)
{
	int x1 = 0;
	int x2 = x1 + SCREEN_WIDTH;

	int y1 = 0;
	int y2 = y1 + SCREEN_HEIGHT;

	int main_map_x = main_map_.start_x/CELL_SIZE;
	int main_map_y = main_map_.start_y/CELL_SIZE;

	for (int i = y1; i < y2; i += CELL_SIZE)
	{
		main_map_x = main_map_.start_x / CELL_SIZE;
		for (int j = x1; j < x2; j += CELL_SIZE)
		{
			int main_val = main_map_.tile_map[main_map_y][main_map_x];
			int item_val = item_map_.tile_map[main_map_y][main_map_x];

			if (main_val == BLANK_CELL)
			{
				tiles[main_val].setRect(j, i);
				tiles[main_val].Render(screen);

				if (item_val != BLANK_ITEM)
				{
					tiles[item_val].setRect(j, i);
					tiles[item_val].Render(screen);
				}
			}
			else
			{
				if (item_val != BLANK_ITEM)
				{
					tiles[item_val].setRect(j, i);
					tiles[item_val].Render(screen);
				}

				if (main_val < BLANK_CELL)
				{
					main_val = BLANK_CELL;
				}
				tiles[main_val].setRect(j, i);
				tiles[main_val].Render(screen);
			}
			main_map_x++;
		}
		main_map_y++;
	}
}