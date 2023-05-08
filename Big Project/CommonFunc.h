#pragma once
#ifndef COMMON_FUNCTION_H
#define COMMON_FUNCTION_H

#include <Windows.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <ctime>
#include <random>
#include <algorithm>
#include <fstream>
#include <sstream>

static SDL_Window* gWindow = NULL;
static SDL_Renderer* gScreen = NULL;
static SDL_Event gEvent;
static TTF_Font* gFont = NULL;

static Mix_Chunk* mix_button = NULL;
static Mix_Chunk* mix_start = NULL;
static Mix_Chunk* mix_win = NULL;
static Mix_Chunk* mix_get_name = NULL;
static Mix_Chunk* mix_lose = NULL;
static Mix_Chunk* mix_round_1 = NULL;
static Mix_Chunk* mix_round_2 = NULL;
static Mix_Chunk* mix_round_3 = NULL;


//Others
#define ERROR_NUM 1
#define NUMBER_OF_LIMIT_CELL 10

//Cells
#define BLANK_CELL 0
#define BOMB_PLANTED -1
#define BLOCK_CELL -2
#define DEAD_CELL -3

//Items
#define BLANK_ITEM -1
#define POWER_UP 14
#define BOMB_UP 15
#define SPEED_UP 16

//Maps
#define CELL_SIZE 52
#define MAX_MAP_X 20
#define MAX_MAP_Y 12

//Screen
const int FRAME_PER_SECOND = 22;
const int SCREEN_WIDTH = CELL_SIZE*MAX_MAP_X;
const int SCREEN_HEIGHT = CELL_SIZE*MAX_MAP_Y;
const int SCREEN_BPP = 64;

//Color
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

struct HighScore 
{
	std::string name;
	int star;
};

namespace SDLCommonFunc
{
	bool isFocusWithRect(const int& x, const int& y, const SDL_Rect& rect);
}

#endif // !COMMON_FUNCTION_H

