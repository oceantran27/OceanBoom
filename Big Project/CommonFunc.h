#pragma once
#ifndef COMMON_FUNCTION_H
#define COMMON_FUNCTION_H

#include <Windows.h>
#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_image.h>


static SDL_Window* g_window = NULL;
static SDL_Renderer* g_screen = NULL;
static SDL_Event g_event;

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
	int left_;
	int right_;
	int up_;
	int down_;
};

struct Map
{
	int start_x_;
	int start_y_;

	int max_x_;
	int max_y_;

	int tile[MAX_MAP_Y][MAX_MAP_X];
	//char* file_name_;
};


#endif // !COMMON_FUNCTION_H

