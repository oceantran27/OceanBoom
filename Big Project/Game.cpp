#include "CommonFunc.h"
#include "BaseObject.h"
#include "Map.h"
#include "Bomb.h"
#include "Bomber.h"
#include "Timer.h"
#include "Enemy.h"

bool InitWindow()
{
	if (SDL_INIT_VIDEO < 0) { return false; }
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

	gWindow = SDL_CreateWindow("Bomberman", 
								SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
								SCREEN_WIDTH, SCREEN_HEIGHT, 
								SDL_WINDOW_SHOWN);
	if (gWindow == NULL) 
		return false;

	gScreen = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
	if (gScreen == NULL)
		return false;

	SDL_SetRenderDrawColor(gScreen, 255, 255, 255, 255);

	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags)) 
		return false;

	return true;
}
GameMap InitGameMap(const int& type)
{
	GameMap game_map_;
	char number_game = type + '0';

	std::string name_main_map = "Map/Game_";
	name_main_map += number_game;
	name_main_map += ".txt";

	std::string name_item_map = "Map/Item_";
	name_item_map += number_game;
	name_item_map += ".txt";

	game_map_.LoadMap(name_main_map.c_str(), name_item_map.c_str());
	game_map_.LoadTiles(gScreen);

	return game_map_;
}
Bomber InitBomber(const int& type)
{
	Bomber player_;

	std::string name_bomber = "Bomber/Game_";
	char number_game = type + '0';
	name_bomber += number_game;
	name_bomber += ".txt";

	float x, y;
	FILE* fp = NULL;
	fopen_s(&fp, name_bomber.c_str(), "rb");
	fscanf_s(fp, "%f%f", &x, &y);
	fclose(fp);

	player_.SetSpawn(x, y);
	player_.LoadClipImg("Bomber/down.png", gScreen);
	player_.SetClip();

	return player_;
}

void Close()
{
	SDL_DestroyRenderer(gScreen);
	gScreen = NULL;

	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	IMG_Quit();
	SDL_Quit();
}

std::vector<Enemy*> InitEnemy(const int& type)
{
	std::vector<Enemy*> list_enemies;
	char number_game = type + '0';

	std::string name_enemy = "Enemy/Game_";
	name_enemy += number_game;
	name_enemy += ".txt";

	int number_enemy;
	FILE* fp = NULL;
	fopen_s(&fp, name_enemy.c_str(), "rb");
	fscanf_s(fp, "%d", &number_enemy);

	int type_enemy;
	int x, y;
	for (int i = 0; i < number_enemy; i++) 
	{
		Enemy* enemy_ = new Enemy();
		fscanf_s(fp, "%d%d%d", &type_enemy, &x, &y);
		enemy_->SetSpawn(type_enemy, x, y);
		list_enemies.push_back(enemy_);
	}
	fclose(fp);

	return list_enemies;
}

int main(int argc, char* argv[])
{
	Timer fps_time;

	if (!InitWindow())
	{
		return -1;
	}

	GameMap gGameMap = InitGameMap(1);
	Map gMainMap = gGameMap.GetMainMap();
	Map gItemMap = gGameMap.GetItemMap();

	Bomber pPlayer = InitBomber(1);

	std::vector<Enemy*> ListEnemy = InitEnemy(1);

	bool quit = false;
	while (!quit)
	{
		fps_time.Start();
		while (SDL_PollEvent (&gEvent))
		{
			if (gEvent.type == SDL_QUIT)
				quit = true; 
			pPlayer.HandleInputAction(gEvent, gScreen, gMainMap);
		}

		SDL_SetRenderDrawColor(gScreen, COLOR_KEY_R, COLOR_KEY_G, COLOR_KEY_B, 255);
		SDL_RenderClear(gScreen);

		gGameMap.DrawMap(gScreen);
		gGameMap.UpdateItemMap(gItemMap);
		gGameMap.UpdateMainMap(gMainMap);

		for (auto enemy_ : ListEnemy)
		{
			enemy_->HandleMove(pPlayer.GetXPos(), pPlayer.GetYPos(), gMainMap);
			enemy_->EnemyShow(gScreen);
		}

		pPlayer.HandleMove(gMainMap,gItemMap);
		pPlayer.BombShow(gScreen, gMainMap, gItemMap);
		pPlayer.BomberShow(gScreen);



		SDL_RenderPresent(gScreen);

		int currentTime = fps_time.GetTicks();
		int oneFrameTime = 1000 / FRAME_PER_SECOND;

		if (currentTime < oneFrameTime)
		{
			int delayTime = oneFrameTime - currentTime;
			if(delayTime >= 0)
				SDL_Delay(delayTime);
		}
	}

	Close();
	return 0;
}


