#include "BaseObject.h"
#include "Game_map.h"

//BaseObject g_background;

bool Init()
{
	if (SDL_INIT_VIDEO < 0) { return false; }
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

	g_window = SDL_CreateWindow("Bomberman", 
								SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
								SCREEN_WIDTH, SCREEN_HEIGHT, 
								SDL_WINDOW_SHOWN);
	if (g_window == NULL) 
		return false;

	g_screen = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
	if (g_screen == NULL)
		return false;

	SDL_SetRenderDrawColor(g_screen, 255, 255, 255, 255);

	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags)) 
		return false;

	return true;
}

//bool LoadBackGround()
//{
//	bool load_bckground = g_background.LoadImg("background_Play.png", g_screen);
//	if (load_bckground == NULL) 
//		return false;
//
//	return true;
//}

void Close()
{
	/*g_background.Free();*/

	SDL_DestroyRenderer(g_screen);
	g_screen = NULL;

	SDL_DestroyWindow(g_window);
	g_window = NULL;

	IMG_Quit();
	SDL_Quit();
}

int main(int argc, char* argv[])
{
	if (!Init())
		return -1;

	//if (!LoadBackGround())
	//	return -1;

	GameMap game_map;
	game_map.LoadMap("Images/map.txt");
	game_map.LoadTiles(g_screen);

	bool quit = false;
	while (!quit)
	{
		while (SDL_PollEvent (&g_event))
		{
			if (g_event.type == SDL_QUIT)
				quit = true; 
		}
		SDL_SetRenderDrawColor(g_screen, 255, 255, 255, 255);
		SDL_RenderClear(g_screen);

		game_map.DrawMap(g_screen);
		//g_background.Render(g_screen, NULL);
		SDL_RenderPresent(g_screen);
	}

	return 0;
}


