#include "CommonFunc.h"
#include "BaseObject.h"
#include "Map.h"
#include "Bomb.h"
#include "Bomber.h"
#include "Timer.h"

bool Init()
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

void Close()
{

	SDL_DestroyRenderer(gScreen);
	gScreen = NULL;

	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	IMG_Quit();
	SDL_Quit();
}

int main(int argc, char* argv[])
{
	Timer fps_time;

	if (!Init())
		return -1;

	GameMap gGameMap;
	std::string name_main_map = "Map/Game_";
	std::string name_item_map = "Map/Item_";
	char number_game = 1 + '0';
	name_main_map += number_game;
	name_item_map += number_game;
	name_item_map += ".txt";
	name_main_map += ".txt";
	gGameMap.LoadMap(name_main_map.c_str(), name_item_map.c_str());
	gGameMap.LoadTiles(gScreen);
	Map gMainMap = gGameMap.GetMainMap();
	Map gItemMap = gGameMap.GetItemMap();

	Bomber pPlayer;
	pPlayer.LoadClipImg("Images/down.png", gScreen);
	pPlayer.SetClip();

	bool quit = false;
	int count = 2;
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


