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

	void loadMap(const char* name_game_map, const char* name_item_map);
	void loadTiles(SDL_Renderer* screen);
	void drawMap(SDL_Renderer* screen);

	Map getMainMap() const { return main_map_; }
	Map getItemMap() const { return item_map_; }

	void updateMainMap(Map& main_map__) { main_map_ = main_map__; }
	void updateItemMap(Map& item_map__) { item_map_ = item_map__; }

private:
	Map main_map_;
	Map item_map_;
	TileMat tiles[MAX_TILES];
};

#endif // !mapH
