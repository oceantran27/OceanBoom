#pragma once
#ifndef COMMON_FUNCTION_H
#define COMMON_FUNCTION_H

#include <Windows.h>
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <string>


static SDL_Window* gWindow = NULL;
static SDL_Renderer* gScreen = NULL;
static SDL_Event gEvent;

const int FRAME_PER_SECOND = 24;
const int SCREEN_WIDTH = 52*15;
const int SCREEN_HEIGHT = 52*13;
const int SCREEN_BPP = 32;

const int COLOR_KEY_R = 140;
const int COLOR_KEY_G = 198;
const int COLOR_KEY_B = 255;

#define TILE_SIZE 52
#define MAX_MAP_X 15
#define MAX_MAP_Y 13

struct Input
{
	int mLeft;
	int mRight;
	int mUp;
	int mDown;
};

struct Map
{
	int mStart_x;
	int mStart_y;

	int mMax_x;
	int mMax_y;

	int mTileMap[MAX_MAP_Y][MAX_MAP_X];
};

#endif // !COMMON_FUNCTION_H

