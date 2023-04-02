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
	Timer fpsTime;

	if (!Init())
		return -1;

	GameMap gameMap;
	std::string name_game = "Map/Game_";
	char number_game = 1 + '0';
	name_game += number_game;
	name_game += ".txt";
	gameMap.LoadMap(name_game.c_str());
	gameMap.LoadTiles(gScreen);
	Map gMap = gameMap.GetMap();

	Bomber pPlayer;
	pPlayer.LoadClipImg("Images/down.png", gScreen);
	pPlayer.SetClip();

	bool quit = false;
	while (!quit)
	{
		fpsTime.Start();
		while (SDL_PollEvent (&gEvent))
		{
			if (gEvent.type == SDL_QUIT)
				quit = true; 
			pPlayer.HandleInputAction(gEvent, gScreen, gMap);
		}

		SDL_SetRenderDrawColor(gScreen, COLOR_KEY_R, COLOR_KEY_G, COLOR_KEY_B, 255);
		SDL_RenderClear(gScreen);

		gameMap.DrawMap(gScreen);
		gameMap.UpdateMap(gMap);
		pPlayer.HandleMove(gMap);
		pPlayer.BombShow(gScreen, gMap);
		pPlayer.BomberShow(gScreen);

		SDL_RenderPresent(gScreen);

		int currentTime = fpsTime.GetTicks();
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


