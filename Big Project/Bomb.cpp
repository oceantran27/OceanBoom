#include "Bomb.h"
#include "MainObject.h"

#define EXPLOSION_TIME 2000

Bomb::Bomb()
{
	mTimer = -1;
	mWaitingToExplode = false;
	m_xPos = 0;
	m_yPos = 0;
}

Bomb::~Bomb()
{
	//
}

void Bomb::Update(float deltaTime)
{
	if (mWaitingToExplode)
	{
		mTimer += deltaTime;

		if (mTimer > EXPLOSION_TIME)
		{
			Explode();
		}
	}
}

void Bomb::Explode()
{
	//
	mWaitingToExplode = false;
}

bool Bomb::PlaceBomb(SDL_Renderer* screen)
{
	if (mWaitingToExplode) {
		return false;
	}

	mWaitingToExplode = true;
	mTimer = 0.0f;
	/*Draw(screen);*/
	return true;
}

void Bomb::Draw(SDL_Renderer* screen)
{
	Render(screen);
}
