#include "CommonFunc.h"
#include "BaseObject.h"
#include "Map.h"
#include "Bomber.h"
#include "Timer.h"
#include "Bomb.h"

bool Init()
{
	if (SDL_INIT_EVERYTHING < 0) { return false; }
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
	gameMap.LoadMap("Map/Level 0.txt");
	gameMap.LoadTiles(gScreen);
	Map gTileMap = gameMap.GetMap();

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
			pPlayer.HandleInputAction(gEvent, gScreen);
		}

		SDL_SetRenderDrawColor(gScreen, 255, 255, 255, 255);
		SDL_RenderClear(gScreen);

		gameMap.DrawMap(gScreen);
		pPlayer.BombShow(gScreen);
		pPlayer.BomberShow(gScreen);
		pPlayer.HandleMove(gTileMap);


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


