#pragma once
#ifndef BOMB_H
#define BOMB_H

#include "CommonFunc.h"
#include "BaseObject.h"

#define TIME_BOMB_EXPLODE 2000

class Bomb : public BaseObject
{
public:
	Bomb();
	~Bomb();
	
	void Update(float deltaTime);
	bool PlaceBomb();
	void Explode();
	bool IsWaitingToExplode() const;

private:
	float mTimer;
	bool mWaitingToExplode;
};

#endif // !BOMB_H

