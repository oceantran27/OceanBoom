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

#define ERROR_NUM 1
#define NUMBER_OF_LIMIT_CELL 10
#define BLANK_CELL 0
#define BOMB_PLANTED -1
#define BLOCK_CELL -2
#define DEAD_CELL -3
#define BLANK_ITEM -1
#define POWER_UP 14
#define BOMB_UP 15
#define SPEED_UP 16
#define CELL_SIZE 52
#define MAX_MAP_X 20
#define MAX_MAP_Y 13

const int FRAME_PER_SECOND = 22;
const int SCREEN_WIDTH = CELL_SIZE*MAX_MAP_X;
const int SCREEN_HEIGHT = CELL_SIZE*MAX_MAP_Y;
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

