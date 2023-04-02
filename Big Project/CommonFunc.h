#pragma once
#ifndef COMMON_FUNCTION_H
#define COMMON_FUNCTION_H

#include <Windows.h>
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>

static SDL_Window* gWindow = NULL;
static SDL_Renderer* gScreen = NULL;
static SDL_Event gEvent;

#define ERROR_NUM 1
#define BLANK_TILE 0
#define BLOCK_TILE -2
#define LIMIT_TILE 1
#define BOMB_PLANTED -1
#define TILE_SIZE 52
#define MAX_MAP_X 25
#define MAX_MAP_Y 15

const int FRAME_PER_SECOND = 30;
const int SCREEN_WIDTH = TILE_SIZE*MAX_MAP_X;
const int SCREEN_HEIGHT = TILE_SIZE*MAX_MAP_Y;
const int SCREEN_BPP = 64;

const int COLOR_KEY_R = 5;
const int COLOR_KEY_G = 140;
const int COLOR_KEY_B = 60;


struct Input
{
	int left;
	int right;
	int up;
	int down;
};

struct Map
{
	int start_x;
	int start_y;

	int max_x;
	int max_y;

	int tile_map[MAX_MAP_Y][MAX_MAP_X];
};

#endif // !COMMON_FUNCTION_H

