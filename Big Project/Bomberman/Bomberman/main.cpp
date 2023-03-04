#include "main.h"

int main(int argc, char* argv[]) 
{
	if (!init())
	{		
		printf("Failed to initialize!\n");
	}
	else
	{
		if (!loadMedia())
		{
			printf("Failed to load media!\n");
		}
		else
		{
			//SDL_BlitSurface(gHelloWorld, NULL, gScreenSurface, NULL);
			//SDL_UpdateWindowSurface(gWindow);
			SDL_Event e; 
			bool quit = false; 
			while (quit == false) 
			{ 
				while (SDL_PollEvent(&e)) 
				{ 
					if (e.type == SDL_QUIT) quit = true; 
				}
				SDL_BlitSurface(gXOut, NULL, gScreenSurface, NULL);
				SDL_UpdateWindowSurface(gWindow);
			}
		}
	}
	close();
	return 0;
}

bool init()
{

	if (SDL_Init(SDL_INIT_VIDEO < 0))
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		return false;
	}
	else
	{
		gWindow = SDL_CreateWindow("Bomberman",
			SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			SCREEN_WIDTH, SCREEN_HEIGHT,
			SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			return false;
		}
		else
		{
			gScreenSurface = SDL_GetWindowSurface(gWindow);
		}
	}
	return true;
}

bool loadMedia()
{
	gXOut = SDL_LoadBMP("x.bmp");
	if (gXOut == NULL)
	{
		printf("Unable to load image %s! SDL Error: %s\n", "x.bmp", SDL_GetError());
		return false;
	}
	return true;
}

void close()
{
	SDL_FreeSurface(gXOut);
	gXOut = NULL;
	
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	SDL_Quit();
}

SDL_Surface* loadSurface(std::string path)
{
	SDL_Surface* loadedSurface = SDL_LoadBMP(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
	}
	return loadedSurface;
}