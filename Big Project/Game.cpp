#include "CommonFunc.h"
#include "BaseObject.h"
#include "Map.h"
#include "Bomb.h"
#include "Player.h"
#include "Timer.h"
#include "Enemy.h"
#include "Text.h"

enum GameState {MENU, PLAYING, /*HIGH_SCORE,*/ HELP, EXIT, GAME_OVER};
GameState gameState = MENU;

const UINT32 TIMER_BREAK = 2000;
const UINT32 TIMER_RESULT = 10000;

bool InitWindow()
{
	if (SDL_INIT_VIDEO < 0 || TTF_Init() < 0) { return false; }
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

	gWindow = SDL_CreateWindow("Boom Ocean",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		SCREEN_WIDTH, SCREEN_HEIGHT,
		SDL_WINDOW_SHOWN);
	if (gWindow == NULL)
		return false;

	gScreen = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
	if (gScreen == NULL)
		return false;

	SDL_Surface* iconSurface = IMG_Load("Images/icon.png");
	SDL_SetWindowIcon(gWindow, iconSurface);

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

void InitPlayer(Player& player_, const int& type)
{

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
}

void Close()
{
	SDL_DestroyRenderer(gScreen);
	gScreen = NULL;

	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	TTF_CloseFont(gFont);
	gFont = NULL;

	TTF_Quit();
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


void renderMenu()
{
	BaseObject background_menu;
	background_menu.loadImg("Menu/background.png", gScreen);
	background_menu.setRect(0, 0);

	const int kMenuButton = 3;

	SDL_Rect posButton[kMenuButton];

	posButton[0].x = 720;  //new game
	posButton[0].y = 210;

	posButton[1].x = 720;  //help
	posButton[1].y = 290;

	posButton[2].x = 720;  //exit
	posButton[2].y = 370;

	std::string button_path[kMenuButton];

	button_path[0] = "Menu/button_new-game.png";
	button_path[1] = "Menu/button_help.png";
	button_path[2] = "Menu/button_exit.png";

	std::string selected_button_path[kMenuButton];

	selected_button_path[0] = "Menu/button_new-game2.png";
	selected_button_path[1] = "Menu/button_help2.png";
	selected_button_path[2] = "Menu/button_exit2.png";

	BaseObject button[kMenuButton];

	for (int i = 0; i < kMenuButton; i++)
	{
		button[i].loadImg(button_path[i], gScreen);
		button[i].setRect(posButton[i].x, posButton[i].y);
	}

	int xm = 0;
	int ym = 0;
	SDL_Event m_event;
	bool quit = false;
	while (!quit)
	{
		SDL_RenderClear(gScreen);
		background_menu.Render(gScreen);

		for (int i = 0; i < kMenuButton; i++)
		{
			button[i].Render(gScreen);
		}

		while (SDL_PollEvent(&gEvent))
		{
			switch (gEvent.type)
			{
			case SDL_QUIT:
				quit = true;
				gameState = EXIT;
				break;

			case SDL_MOUSEMOTION:
				xm = gEvent.motion.x;
				ym = gEvent.motion.y;

				for (int i = 0; i < kMenuButton; i++)
				{
					if (SDLCommonFunc::isFocusWithRect(xm, ym, button[i].getRect()))
					{
						button[i].loadImg(selected_button_path[i].c_str(), gScreen);
					}
					else
					{
						button[i].loadImg(button_path[i].c_str(), gScreen);
					}
				}
				break;

			case SDL_MOUSEBUTTONDOWN:
				xm = gEvent.button.x;
				ym = gEvent.button.y;

				for (int i = 0; i < kMenuButton; i++)
				{
					if (SDLCommonFunc::isFocusWithRect(xm, ym, button[i].getRect()))
					{
						gameState = static_cast<GameState>(i + 1);
						quit = true;
					}
				}
				break;
			}
			
		}
		SDL_RenderPresent(gScreen);
	}

}

void renderHelp()
{
	BaseObject background_help;
	background_help.loadImg("Menu/background_help.png", gScreen);
	background_help.setRect(0, 0);

	SDL_Rect posButton;

	posButton.x = 836;  //back
	posButton.y = 516;

	std::string selected_button_path = "Menu/back2.png";
	std::string button_path = "Menu/back.png";


	BaseObject button;
	button.loadImg(button_path, gScreen);
	button.setRect(posButton.x, posButton.y);

	int xm = 0;
	int ym = 0;
	SDL_Event m_event;
	bool quit = false;
	while (!quit)
	{
		SDL_RenderClear(gScreen);
		background_help.Render(gScreen);
		button.Render(gScreen);
		while (SDL_PollEvent(&gEvent))
		{
			switch (gEvent.type)
			{
			case SDL_QUIT:
				quit = true;
				gameState = EXIT;
				break;

			case SDL_MOUSEMOTION:
				xm = gEvent.motion.x;
				ym = gEvent.motion.y;

					if (SDLCommonFunc::isFocusWithRect(xm, ym, button.getRect()))
					{
						button.loadImg(selected_button_path.c_str(), gScreen);
					}
					else
					{
						button.loadImg(button_path.c_str(), gScreen);
					}
				break;

			case SDL_MOUSEBUTTONDOWN:
				xm = gEvent.button.x;
				ym = gEvent.button.y;

					if (SDLCommonFunc::isFocusWithRect(xm, ym, button.getRect()))
					{
						gameState = MENU;
						quit = true;
					}
				break;
			}

		}
		SDL_RenderPresent(gScreen);
	}

}

bool pause()
{
	const int kMenuButton = 2;

	SDL_Rect posButton[kMenuButton];

	posButton[0].x = 6 * CELL_SIZE;  //Menu
	posButton[0].y = 350;

	posButton[1].x = 12 * CELL_SIZE;  //Resume
	posButton[1].y = 350;

	std::string button_path[kMenuButton];

	button_path[0] = "Menu/button_menu.png";
	button_path[1] = "Menu/button_resume.png";

	std::string selected_button_path[kMenuButton];

	selected_button_path[0] = "Menu/button_menu2.png";
	selected_button_path[1] = "Menu/button_resume2.png";

	BaseObject button[kMenuButton];

	for (int i = 0; i < kMenuButton; i++)
	{
		button[i].loadImg(button_path[i], gScreen);
		button[i].setRect(posButton[i].x, posButton[i].y);
	}

	gFont = TTF_OpenFont("Font/ariblk.ttf", 20);
	Text warning;
	warning.setColor(Text::RED_TEXT);
	warning.setText("WARNING: The game will not be saved if you press \"Menu\".");
	warning.loadFromRenderText(gFont, gScreen);
	Text ques;
	ques.setColor(Text::RED_TEXT);
	ques.setText("Do you want to continue?");
	ques.loadFromRenderText(gFont, gScreen);

	int xm = 0;
	int ym = 0;
	bool quit = false;
	while (!quit)
	{
		SDL_RenderClear(gScreen);
		warning.renderText(gScreen, 4.75 * CELL_SIZE, 3 * CELL_SIZE);
		ques.renderText(gScreen, 7.5 * CELL_SIZE, 4 * CELL_SIZE);

		SDL_SetRenderDrawColor(gScreen, COLOR_KEY_R, COLOR_KEY_G, 255, 255);


		for (int i = 0; i < kMenuButton; i++)
		{
			button[i].Render(gScreen);
		}

		while (SDL_PollEvent(&gEvent))
		{
			switch (gEvent.type)
			{
			case SDL_QUIT:
				quit = true;
				gameState = EXIT;
				return false;
				break;

			case SDL_MOUSEMOTION:
				xm = gEvent.motion.x;
				ym = gEvent.motion.y;

				for (int i = 0; i < kMenuButton; i++)
				{
					if (SDLCommonFunc::isFocusWithRect(xm, ym, button[i].getRect()))
					{
						button[i].loadImg(selected_button_path[i].c_str(), gScreen);
					}
					else
					{
						button[i].loadImg(button_path[i].c_str(), gScreen);
					}
				}
				break;

			case SDL_MOUSEBUTTONDOWN:
				xm = gEvent.button.x;
				ym = gEvent.button.y;

				for (int i = 0; i < kMenuButton; i++)
				{
					if (SDLCommonFunc::isFocusWithRect(xm, ym, button[i].getRect()))
					{
						switch (i)
						{
						case 0:
							gameState = MENU;
							break;
						}
						quit = true;
						return false;
					}
				}
				break;
			}
		}
		SDL_RenderPresent(gScreen);
	}
}

void renderResult(const Uint32& time_play)
{
	Timer render_result_time;
	render_result_time.Start();
	BaseObject result_table;

	std::string str_time = "Time: ";
	//std::string str_mark = "Mark: ";

	std::string str_val;
	int min = time_play / 60;
	str_val = std::to_string(min);
	str_time += str_val + "\' ";
	int sec = time_play % 60;
	str_val = std::to_string(sec);
	str_time += str_val + "\'\'";

	gFont = TTF_OpenFont("Font/ariblk.ttf", 30);
	Text result_time;
	result_time.setColor(Text::RED_TEXT);
	result_time.setText(str_time);
	result_time.loadFromRenderText(gFont, gScreen);

	if (time_play > 120)
	{
		result_table.loadImg("Menu/1_star.png", gScreen);
	}
	else if (time_play > 60)
	{
		result_table.loadImg("Menu/2_star.png", gScreen);
	}
	else
	{
		result_table.loadImg("Menu/3_star.png", gScreen);
	}
	result_table.setRect(0, 0);

	while (render_result_time.GetTicks() <= TIMER_RESULT)
	{
		while (SDL_PollEvent(&gEvent))
		{
			switch (gEvent.type)
			{
			case SDL_QUIT:
				gameState = EXIT;
				return;
				break;
			}
		}
		SDL_RenderClear(gScreen);
		SDL_SetRenderDrawColor(gScreen, COLOR_KEY_R, COLOR_KEY_G, 255, 255);
		result_table.Render(gScreen);

		result_time.renderText(gScreen, 8 * CELL_SIZE, 5.5 * CELL_SIZE);
		SDL_RenderPresent(gScreen);
	}
}

void loopGame()
{
	bool game_over = false;
	int round = 3;
	Player pPlayer;
	while (round <= 3 && !game_over)
	{
		Timer fps_time;
		Timer playing_time;
		Timer break_time;

		GameMap gGameMap = InitGameMap(round);
		Map gMainMap = gGameMap.getMainMap();
		Map gItemMap = gGameMap.getItemMap();
		InitPlayer(pPlayer, round);
		std::vector<Enemy*> ListEnemy = InitEnemy(round);

		BaseObject pause_button;
		pause_button.loadImg("Menu/pause.png", gScreen);
		pause_button.setRect(18.5 * CELL_SIZE, 0.15 * CELL_SIZE);

		TTF_Font* gFont = NULL;
		gFont = TTF_OpenFont("Font/ariblk.ttf", 20);
		Text time_game;
		time_game.setColor(Text::YELLOW_TEXT);
		Text mark_game;
		mark_game.setColor(Text::YELLOW_TEXT);

		playing_time.Start();
		bool is_pause = false;
		bool quit = false;
		int xm = 0;
		int ym = 0;
		while (!quit)
		{
			fps_time.Start();

			while (SDL_PollEvent(&gEvent))
			{
				switch (gEvent.type)
				{
				case SDL_QUIT:
					quit = true;
					gameState = EXIT;
					return;
					break;

				case SDL_MOUSEMOTION:
					xm = gEvent.motion.x;
					ym = gEvent.motion.y;

					if (SDLCommonFunc::isFocusWithRect(xm, ym, pause_button.getRect()))
					{
						pause_button.loadImg("Menu/pause2.png", gScreen);
					}
					else
					{
						pause_button.loadImg("Menu/pause.png", gScreen);
					}
					break;

				case SDL_MOUSEBUTTONDOWN:
					xm = gEvent.button.x;
					ym = gEvent.button.y;


					if (SDLCommonFunc::isFocusWithRect(xm, ym, pause_button.getRect()))
					{
						is_pause = true;
						playing_time.Paused();
					}
					break;
				}
				if (!game_over)
				{
					pPlayer.handleInputAction(gEvent, gScreen, gMainMap);
				}
			}

			while (is_pause)
			{
				is_pause = pause();
			}
			playing_time.Resume();
			if (gameState != PLAYING)
			{
				break;
			}

			SDL_SetRenderDrawColor(gScreen, COLOR_KEY_R, COLOR_KEY_G, COLOR_KEY_B, 255);
			SDL_RenderClear(gScreen);

			int remain_time = 180 - (playing_time.GetTicks() / 1000);
			Uint32 mark_val = pPlayer.getPoint();

			gGameMap.drawMap(gScreen);
			gGameMap.updateItemMap(gItemMap);
			gGameMap.updateMainMap(gMainMap);

			pause_button.Render(gScreen);

			pPlayer.showBomb(gScreen, gMainMap, gItemMap);
			pPlayer.showLife(gScreen);
			pPlayer.handleMove(gMainMap, gItemMap);

			for (int i = 0; i < ListEnemy.size(); i++)
			{
				Uint32 current_time = SDL_GetTicks();
				if (ListEnemy[i]->isDead() && current_time >= ListEnemy[i]->getTimeDead())
				{
					int plus_point = ListEnemy[i]->getTypeEnemy() * 100;
					pPlayer.increasePoint(plus_point);
					ListEnemy[i]->Free();
					ListEnemy[i] = NULL;
					delete(ListEnemy[i]);
					ListEnemy.erase(ListEnemy.begin() + i);
				}
				else
				{
					if (remain_time == 30)
					{
						ListEnemy[i]->increaseEnemySpeed();
					}
					ListEnemy[i]->handleMove(pPlayer, gMainMap);
					ListEnemy[i]->showEnemy(gScreen);
					if (!ListEnemy[i]->isFreeze())
					{
						pPlayer.checkCollideEnemy(ListEnemy[i]->getRect());
					}
				}
			}

			pPlayer.showPlayer(gScreen);

			std::string str_mark = "MARK: ";
			std::string str_val = std::to_string(mark_val);
			str_mark += str_val;

			mark_game.setText(str_mark);
			mark_game.loadFromRenderText(gFont, gScreen);
			mark_game.renderText(gScreen, 8.5 * CELL_SIZE, 0.25 * CELL_SIZE);

			std::string str_time = "TIME: ";

			if (remain_time > 0)
			{
				std::string str_val = std::to_string(remain_time);
				str_time += str_val;

				time_game.setText(str_time);
				time_game.loadFromRenderText(gFont, gScreen);
				time_game.renderText(gScreen, 15 * CELL_SIZE, 0.25 * CELL_SIZE);
			}

			SDL_RenderPresent(gScreen);

			int currentTime = fps_time.GetTicks();
			int oneFrameTime = 1000 / FRAME_PER_SECOND;
			if (currentTime < oneFrameTime)
			{
				int delayTime = oneFrameTime - currentTime;
				if (delayTime >= 0)
					SDL_Delay(delayTime);
			}

			if (remain_time <= 0 || pPlayer.getLife() <= 0)
			{
				if (!game_over)
				{
					ListEnemy.clear();
					game_over = true;
					break_time.Start();
					
				}
				else if (break_time.GetTicks() >= TIMER_BREAK )
				{
					quit = true;
					gameState = EXIT;
					return;
					break;
				}
			}

			if (ListEnemy.empty() && !game_over) {
				quit = true;
			}

			//if (round == 1) { ListEnemy.clear(); }
		}
		renderResult(playing_time.GetTicks()/1000);
		round++;
	}
}


int main(int argc, char* argv[])
{

	if (!InitWindow())
	{
		return -1;
	}

	bool is_quit = false;
	while (!is_quit)
	{
		switch (gameState)
		{
		case MENU:
			renderMenu();
			break;
		case PLAYING:
			loopGame();
			break;
		case HELP:
			renderHelp();
			break;
		case EXIT:
			is_quit = true;
			break;
		}
	}

	Close();

	return 0;
}


