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
#include <ctime>
#include <random>

static SDL_Window* gWindow = NULL;
static SDL_Renderer* gScreen = NULL;
static SDL_Event gEvent;

#define LIMIT_LAG 15
#define ERROR_NUM 1
#define BLANK_TILE 0
#define BLANK_ITEM -1
#define POWER_UP 5
#define BOMB_UP 6
#define SPEED_UP 7
#define BLOCK_TILE -2
#define LIMIT_TILE 1
#define BOMB_PLANTED -1
#define TILE_SIZE 52
#define MAX_MAP_X 20
#define MAX_MAP_Y 13

const int FRAME_PER_SECOND = 24;
const int SCREEN_WIDTH = TILE_SIZE*MAX_MAP_X;
const int SCREEN_HEIGHT = TILE_SIZE*MAX_MAP_Y;
const int SCREEN_BPP = 64;

const int COLOR_KEY_R = 90;
const int COLOR_KEY_G = 182;
const int COLOR_KEY_B = 0;


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

