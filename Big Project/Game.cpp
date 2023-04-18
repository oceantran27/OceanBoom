#include "CommonFunc.h"
#include "BaseObject.h"
#include "Map.h"
#include "Bomb.h"
#include "Player.h"
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

	game_map_.loadMap(name_main_map.c_str(), name_item_map.c_str());
	game_map_.loadTiles(gScreen);

	return game_map_;
}

Player InitPlayer(const int& type)
{
	Player player_;

	std::string name_player = "Player/Game_";
	char number_game = type + '0';
	name_player += number_game;
	name_player += ".txt";

	float x, y;
	FILE* fp = NULL;
	fopen_s(&fp, name_player.c_str(), "rb");
	fscanf_s(fp, "%f%f", &x, &y);
	fclose(fp);

	player_.setSpawn(x, y);
	//player_.loadClipImg("Player/down.png", gScreen);
	//player_.setClip();

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
		enemy_->setSpawn(type_enemy, x, y);
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
	Map gMainMap = gGameMap.getMainMap();
	Map gItemMap = gGameMap.getItemMap();

	Player pPlayer = InitPlayer(1);

	std::vector<Enemy*> ListEnemy = InitEnemy(1);

	bool quit = false;
	while (!quit)
	{

		fps_time.Start();
		while (SDL_PollEvent (&gEvent))
		{
			if (gEvent.type == SDL_QUIT)
				quit = true; 
			pPlayer.handleInputAction(gEvent, gScreen, gMainMap);
		}

		SDL_SetRenderDrawColor(gScreen, COLOR_KEY_R, COLOR_KEY_G, COLOR_KEY_B, 255);
		SDL_RenderClear(gScreen);

		gGameMap.drawMap(gScreen);
		gGameMap.updateItemMap(gItemMap);
		gGameMap.updateMainMap(gMainMap);

		pPlayer.showBomb(gScreen, gMainMap, gItemMap);
		pPlayer.handleMove(gMainMap, gItemMap);
		pPlayer.showPlayer(gScreen);

		for (int i = 0; i < ListEnemy.size(); i++)
		{
			SDL_TimerID current_time = SDL_GetTicks();
			if (ListEnemy[i]->isDead() && current_time >= ListEnemy[i]->getTimeDead())
			{
				ListEnemy[i]->Free();
				ListEnemy[i] = NULL;
				delete(ListEnemy[i]);
				ListEnemy.erase(ListEnemy.begin() + i);
			}
			else
			{
				ListEnemy[i]->handleMove(pPlayer, gMainMap);
				ListEnemy[i]->showEnemy(gScreen);
				if (!ListEnemy[i]->isFreeze())
				{
					pPlayer.checkCollideEnemy(ListEnemy[i]->getRect());
				}
			}
			SDL_RemoveTimer(current_time);
		}

		SDL_RenderPresent(gScreen);

		int currentTime = fps_time.GetTicks();
		int oneFrameTime = 1000 / FRAME_PER_SECOND;
		if (currentTime < oneFrameTime)
		{
			int delayTime = oneFrameTime - currentTime;
			if(delayTime >= 0)
				SDL_Delay(delayTime);
		}

		if (pPlayer.getLifesRemain() <= 0) {
			SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Game Over", "Ngu !", gWindow);
			Close();
			break;
		}
	}

	Close();

	return 0;
}


