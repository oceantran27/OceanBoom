#pragma once
#ifndef BOMBER_H
#define BOMBER_H

#include "BaseObject.h"
#include "CommonFunc.h"
#include "Bomb.h"
#include <vector>

class Bomber : public BaseObject
{
public:
	Bomber();
	~Bomber();

	enum WalkType
	{
		WALK_RIGHT = 1,
		WALK_LEFT = 2,
		WALK_UP = 3,
		WALK_DOWN = 4
	};

	bool LoadClipImg(std::string path, SDL_Renderer* screen);
	void BomberShow(SDL_Renderer* des);
	void HandleInputAction(SDL_Event &event, SDL_Renderer* screen);
	void SetClip();
	void HandleMove(Map& mapData);
	void CheckToMap(Map& mapData);
	void BombShow(SDL_Renderer* des);
	void SetBombList(std::vector<Bomb*> bombList)
	{
		pBombList = bombList;
	}

	std::vector<Bomb*> GetBombList() const { return pBombList; }

private:
	std::vector<Bomb*> pBombList;

	float mVal_x;
	float mVal_y;

	float m_xPos;
	float m_yPos;

	int mWidthFrame;
	int mHeightFrame;

	SDL_Rect mFrameClip[4];
	Input mInputType;
	int mFrame;
	int mStatus;
};
 
#endif // !MAIN_OBJECT_H
