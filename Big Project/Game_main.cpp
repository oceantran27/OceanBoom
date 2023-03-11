#include "BaseObject.h"
#include "Game_map.h"
#include "MainObject.h"

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

void Close()
{

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

	GameMap game_map;
	game_map.LoadMap("Map/Level 1.txt");
	game_map.LoadTiles(g_screen);

	MainObject p_player;
	p_player.MO_LoadImg("Images/down.png", g_screen);
	p_player.Set_Clip();

	Map g_map_data = game_map.getMap();

	bool quit = false;
	while (!quit)
	{
		while (SDL_PollEvent (&g_event))
		{
			if (g_event.type == SDL_QUIT)
				quit = true; 
			p_player.HandleInputAction(g_event);
		}

		SDL_SetRenderDrawColor(g_screen, 255, 255, 255, 255);
		SDL_RenderClear(g_screen);

		game_map.DrawMap(g_screen);
		p_player.Show(g_screen);
		p_player.HandleMove(g_map_data);

		SDL_RenderPresent(g_screen);
	}

	return 0;
}


