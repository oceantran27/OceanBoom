#pragma once
#ifndef mapH
#define mapH

#include "CommonFunc.h"
#include "BaseObject.h"

#define MAX_TILES 20
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
	void UpdateMap(Map& map__) { map_ = map__; }
private:
	Map map_;
	TileMat tiles[MAX_TILES];
};

#endif // !mapH
