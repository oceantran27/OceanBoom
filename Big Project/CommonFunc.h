#pragma once
#ifndef COMMON_FUNCTION_H
#define COMMON_FUNCTION_H

#include <Windows.h>
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <string>
#include <vector>

static SDL_Window* gWindow = NULL;
static SDL_Renderer* gScreen = NULL;
static SDL_Event gEvent;

#define ERROR_NUM 1
#define BLANK_TILE 0
#define BLOCK_TILE -2
#define LIMIT_TILE 1
#define BOMB_PLANTED -1
#define TILE_SIZE 52
#define MAX_MAP_X 15
#define MAX_MAP_Y 13

const int FRAME_PER_SECOND = 22;
const int SCREEN_WIDTH = TILE_SIZE*MAX_MAP_X;
const int SCREEN_HEIGHT = TILE_SIZE*MAX_MAP_Y;
const int SCREEN_BPP = 64;

const int COLOR_KEY_R = 35;
const int COLOR_KEY_G = 31;
const int COLOR_KEY_B = 31;


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

