#pragma once
#ifndef BOMB_H
#define BOMB_H

#include "CommonFunc.h"
#include "BaseObject.h"

#define TIME_BOMB_EXPLODE 2000
#define WIDTH_BOMB 48
#define HEIGHT_BOMB 48

class Bomb : public BaseObject
{
public:
	Bomb();
	~Bomb();
	
	void Update(float deltaTime);
	bool PlaceBomb(SDL_Renderer* screen);
	void Explode();
	bool isWaitingToExplode() const;
	/*void SetWidthHeight(const int& width, const int& height) { rect_.w = width; rect_.h = height; }*/
	void Draw(SDL_Renderer* screen);

private:
	float mTimer;
	bool mWaitingToExplode;
	int m_xPos;
	int m_yPos;
};

#endif // !BOMB_H

