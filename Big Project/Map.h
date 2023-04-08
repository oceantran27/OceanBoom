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

	void LoadMap(const char* name_game_map, const char* name_item_map);
	void LoadTiles(SDL_Renderer* screen);
	void DrawMap(SDL_Renderer* screen);
	Map GetMainMap() const { return main_map_; }
	Map GetItemMap() const { return item_map_; }
	void UpdateMainMap(Map& main_map__) { main_map_ = main_map__; }
	void UpdateItemMap(Map& item_map__) { item_map_ = item_map__; }

private:
	Map main_map_;
	Map item_map_;
	TileMat tiles[MAX_TILES];
};

#endif // !mapH
