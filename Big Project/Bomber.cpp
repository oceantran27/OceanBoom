#include "Bomber.h"

#define BLANK_TILE 0
#define PLAYER_SPEED 4
#define ERROR_NUM 4


Bomber::Bomber()
{
	mFrame = 0;
	m_xPos = 52;
	m_yPos = 52;
	mVal_x = 0;
	mVal_y = 0;
	mWidthFrame = 0;
	mHeightFrame = 0;
	mStatus = -1;
	mInputType.mLeft = 0;
	mInputType.mRight = 0;
	mInputType.mUp = 0;
	mInputType.mDown = 0;
}

Bomber::~Bomber()
{

}

bool Bomber::LoadClipImg(std::string path, SDL_Renderer* screen)
{
	bool ret = BaseObject::LoadImg(path, screen);
	if (ret == false)
	{
		return false;
	}

	mWidthFrame = mRect.w / 3;
	mHeightFrame = mRect.h;

	return true;
}

void Bomber::SetClip()
{
	if (mWidthFrame > 0 && mHeightFrame > 0)
	{
		for (int i = 0; i < 3; i++)
		{
			mFrameClip[i].x = i*mWidthFrame;
			mFrameClip[i].y = 0;
			mFrameClip[i].w = mWidthFrame;
			mFrameClip[i].h = mHeightFrame;
		}
	}
}

void Bomber::BomberShow(SDL_Renderer* des)
{
	if (mStatus == WALK_LEFT)
	{
		LoadClipImg("Images/left.png", des);
	}
	else if (mStatus == WALK_RIGHT)
	{
		LoadClipImg("Images/right.png", des);
	}
	else if (mStatus == WALK_UP)
	{
		LoadClipImg("Images/up.png", des);
	}
	else if (mStatus == WALK_DOWN)
	{
		LoadClipImg("Images/down.png", des);
	}

	if (mInputType.mLeft == 1 ||
		mInputType.mRight == 1 ||
		mInputType.mUp == 1 ||
		mInputType.mDown == 1)
	{
		mFrame++;
	}
	else
	{
		mFrame = 0;
	}

	if (mFrame >= 3)
		mFrame = 0;

	mRect.x = m_xPos;
	mRect.y = m_yPos;

	SDL_Rect* current_clip = &mFrameClip[mFrame];
	SDL_Rect renderQuad = { mRect.x, mRect.y, mWidthFrame, mHeightFrame };
	SDL_RenderCopy(des, pObject, current_clip, &renderQuad);
}

void Bomber::HandleInputAction(SDL_Event &event, SDL_Renderer* screen)
{
	if (event.type == SDL_KEYDOWN)
	{
		switch (event.key.keysym.sym)
		{
		case SDLK_LEFT:
		{
			mStatus = WALK_LEFT;
			mInputType.mLeft = 1;
			mInputType.mRight = 0;
			mInputType.mUp = 0;
			mInputType.mDown = 0;
		}
		break;

		case SDLK_RIGHT:
		{
			mStatus = WALK_RIGHT;
			mInputType.mLeft = 0;
			mInputType.mRight = 1;
			mInputType.mUp = 0;
			mInputType.mDown = 0;
		}
		break;

		case SDLK_UP:
		{
			mStatus = WALK_UP;
			mInputType.mLeft = 0;
			mInputType.mRight = 0;
			mInputType.mUp = 1;
			mInputType.mDown = 0;
		}
		break;

		case SDLK_DOWN:
		{
			mStatus = WALK_DOWN;
			mInputType.mLeft = 0;
			mInputType.mRight = 0;
			mInputType.mUp = 0;
			mInputType.mDown = 1;

		}
		break;

		case SDLK_SPACE:
		{
			Bomb* mBomb = new Bomb();
			mBomb->LoadImg("Images/bomb.png", screen);
			int tmp_x = (int)(m_xPos + ERROR_NUM) / TILE_SIZE;
			int tmp_y = (int)(m_yPos + ERROR_NUM) / TILE_SIZE;
			mBomb->SetRect(tmp_x*TILE_SIZE, tmp_y*TILE_SIZE);
			pBombList.push_back(mBomb);
		}
		break;
		}
	}

	if (event.type == SDL_KEYUP)
	{
		switch (event.key.keysym.sym)
		{
		case SDLK_LEFT:
		{
			mInputType.mLeft = 0;
		}
		break;

		case SDLK_RIGHT:
		{
			mInputType.mRight = 0;
		}
		break;

		case SDLK_UP:
		{
			mInputType.mUp = 0;
		}
		break;

		case SDLK_DOWN:
		{
			mInputType.mDown = 0;
		}
		break;
		}
	}

}

void Bomber::HandleMove(Map& mapData)
{
	mVal_x = 0;
	mVal_y = 0;
	if (mInputType.mLeft == 1)
	{
		mVal_x -= PLAYER_SPEED;
	}
	else if (mInputType.mRight == 1)
	{
		mVal_x += PLAYER_SPEED;
	}
	else if (mInputType.mUp == 1)
	{
		mVal_y -= PLAYER_SPEED;
	}
	else if (mInputType.mDown == 1)
	{
		mVal_y += PLAYER_SPEED;
	}
	CheckToMap(mapData);
}

void Bomber::CheckToMap(Map& mapData)
{
	m_xPos += mVal_x;
	m_yPos += mVal_y;

	int x1, x2;
	int y1, y2;

	x1 = (m_xPos + ERROR_NUM) / TILE_SIZE;
	x2 = (m_xPos + mWidthFrame - ERROR_NUM) / TILE_SIZE;

	y1 = (m_yPos + ERROR_NUM) / TILE_SIZE;
	y2 = (m_yPos + mHeightFrame - ERROR_NUM) / TILE_SIZE;


	if (m_xPos < TILE_SIZE || m_xPos + mWidthFrame + TILE_SIZE > mapData.mMax_x)
	{
		m_xPos -= mVal_x;
	}
	if (m_yPos < TILE_SIZE || m_yPos + mHeightFrame + TILE_SIZE > mapData.mMax_y)
	{
		m_yPos -= mVal_y;
	}

	if (mVal_x > 0)
	{
		if (mapData.mTileMap[y1][x2] != BLANK_TILE || mapData.mTileMap[y2][x2] != BLANK_TILE)
		{
			m_xPos = x2 * TILE_SIZE - mWidthFrame - ERROR_NUM;
			mVal_x = 0;
		}
	}
	else if (mVal_x < 0)
	{
		if (mapData.mTileMap[y1][x1] != BLANK_TILE || mapData.mTileMap[y2][x1] != BLANK_TILE)
		{
			m_xPos = (x1 + 1) * TILE_SIZE;
			mVal_x = 0;
		}
	}

	if (mVal_y > 0)
	{
		if (mapData.mTileMap[y2][x1] != BLANK_TILE || mapData.mTileMap[y2][x2] != BLANK_TILE)
		{
			m_yPos = y2 * TILE_SIZE - mHeightFrame - ERROR_NUM;
			mVal_y = 0;
		}
	}
	else if (mVal_y < 0)
	{
		if (mapData.mTileMap[y1][x1] != BLANK_TILE || mapData.mTileMap[y1][x2] != BLANK_TILE)
		{
			m_yPos = (y1 + 1) * TILE_SIZE;
			mVal_y = 0;
		}
	}
}

void Bomber::BombShow(SDL_Renderer* des)
{
	for (auto mBomb : pBombList)
	{
		mBomb->Render(des);
	}
}