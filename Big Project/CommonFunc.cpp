#include "CommonFunc.h"

bool SDLCommonFunc::isFocusWithRect(const int& x, const int& y, const SDL_Rect& rect)
{
	if (x >= rect.x && x <= (rect.x + rect.w)
		&& y >= rect.y && y <= (rect.y + rect.h))
	{
		return true;
	}

	return false;
}


int SDLCommonFunc::ShowMenu(SDL_Renderer* des)
{
	BaseObject background_menu;
	background_menu.loadImg("Menu/background.png", des);
	background_menu.setRect(0, 0);

	const int kMenuButton = 4;

	SDL_Rect posButton[kMenuButton];

	posButton[0].x = 720;  //new game
	posButton[0].y = 200;

	posButton[1].x = 720;  //help
	posButton[1].y = 260;

	posButton[2].x = 720;  //hight score
	posButton[2].y = 320;

	posButton[3].x = 720;  //exit
	posButton[3].y = 380;


	std::string button_path[kMenuButton];

	button_path[0] = "Menu/button_new-game.png";
	button_path[1] = "Menu/button_help.png";
	button_path[2] = "Menu/button_high-score.png";
	button_path[3] = "Menu/button_exit.png";

	std::string selected_button_path[kMenuButton];

	selected_button_path[0] = "Menu/button_new-game2.png";
	selected_button_path[1] = "Menu/button_help2.png";
	selected_button_path[2] = "Menu/button_high-score2.png";
	selected_button_path[3] = "Menu/button_exit2.png";

	BaseObject button[kMenuButton];

	for (int i = 0; i < kMenuButton; i++)
	{
		button[i].loadImg(button_path[i], des);
		button[i].setRect(posButton[i].x, posButton[i].y);
	}

	bool is_selected[kMenuButton];

	int xm = 0;
	int ym = 0;
	SDL_Event m_event;
	bool quit = false;
	while (!quit)
	{
		SDL_RenderClear(des);
		background_menu.Render(des);

		for (int i = 0; i < kMenuButton; i++)
		{
			button[i].Render(des);
		}

		while (SDL_PollEvent(&gEvent))
		{
			switch (gEvent.type)
			{
			case SDL_QUIT:
				quit = true;
				break;

			case SDL_MOUSEMOTION:
				xm = gEvent.motion.x;
				ym = gEvent.motion.y;

				for (int i = 0; i < kMenuButton; i++)
				{
					if (isFocusWithRect(xm, ym, button[i].getRect()))
					{
						button[i].loadImg(selected_button_path[i].c_str(), des);
					}
					else
					{
						button[i].loadImg(button_path[i].c_str(), des);
					}
				}
				break;

			case SDL_MOUSEBUTTONDOWN:
				xm = gEvent.button.x;
				ym = gEvent.button.y;

				for (int i = 0; i < kMenuButton; i++)
				{
					if (isFocusWithRect(xm, ym, button[i].getRect()))
					{
						/*button[i].loadImg(selected_button_path[i].c_str(), des);*/
					}

				}
				break;
			}
		}
		SDL_RenderPresent(des);
	}
	return 0;
}