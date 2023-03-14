#include "BaseObject.h"
#include "Game_map.h"
#include "MainObject.h"
#include "ImpTimer.h"

bool Init()
{
	if (SDL_INIT_EVERYTHING < 0) { return false; }
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
	ImpTimer fps_timer;

	if (!Init())
		return -1;

	GameMap game_map;
	game_map.LoadMap("Map/Level 0.txt");
	game_map.LoadTiles(g_screen);
	Map g_map_data = game_map.getMap();

	MainObject p_player;
	p_player.MO_LoadImg("Images/down.png", g_screen);
	p_player.Set_Clip();

	bool quit = false;
	while (!quit)
	{
		fps_timer.start();
		while (SDL_PollEvent (&g_event))
		{
			if (g_event.type == SDL_QUIT)
				quit = true; 
			p_player.HandleInputAction(g_event, g_screen);
		}

		SDL_SetRenderDrawColor(g_screen, 255, 255, 255, 255);
		SDL_RenderClear(g_screen);

		game_map.DrawMap(g_screen);
		p_player.Show(g_screen);
		p_player.HandleMove(g_map_data);

		SDL_RenderPresent(g_screen);
		for (int i = 0; i < p_player.get_bom_list().size(); i++)
		{
			std::vector<Bomb*> bomb_list = p_player.get_bom_list();
			Bomb* p_bomb = bomb_list.at(i);
			p_bomb->Draw(g_screen);
		}

		int real_imp_time = fps_timer.get_ticks();
		int time_one_frame = 1000 / FRAME_PER_SECOND;

		if (real_imp_time < time_one_frame)
		{
			int delay_time = time_one_frame - real_imp_time;
			if(delay_time >= 0)
				SDL_Delay(delay_time);
		}
	}

	Close();
	return 0;
}


