#include "Bomb.h"

#define EXPLOSION_TIME 2000

Bomb::Bomb()
{
	mTimer = -1;
	mWaitingToExplode = false;
}

Bomb::~Bomb()
{
	//
}

void Bomb::Update(float deltaTime)
{
	//if (mWaitingToExplode)
	//{
		mTimer += deltaTime;

		if (mTimer > EXPLOSION_TIME)
		{
			Explode();
		}
	//}
}

void Bomb::Explode()
{
	//
	mWaitingToExplode = false;
}

bool Bomb::PlaceBomb()
{
	if (mWaitingToExplode) {
		return false;
	}

	mWaitingToExplode = true;
	mTimer = 0.0f;
	return true;
}

