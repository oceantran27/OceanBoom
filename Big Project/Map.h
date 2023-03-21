#pragma once
#ifndef MAP_H
#define MAP_H

#include "CommonFunc.h"
#include "BaseObject.h"

#define MAX_TILES 5

class TileMat : public BaseObject
{
public:
	TileMat() { ; }
	~TileMat() { ; }
};

class GameMap
{
public:
	GameMap() { ; }
	~GameMap() { ; }

	void LoadMap(const char* name);
	void LoadTiles(SDL_Renderer* screen);
	void DrawMap(SDL_Renderer* screen);
	Map GetMap() const { return map_; }

private:
	Map map_;
	TileMat tiles[MAX_TILES];
};

#endif // !MAP_H
