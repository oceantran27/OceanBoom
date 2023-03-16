#pragma once
#ifndef BASE_OBJECT_H
#define BASE_OBJECT_H

#include "CommonFunc.h"

class BaseObject
{
public:
	BaseObject();
	~BaseObject();
	void SetRect(const int& x, const int& y) { mRect.x = x; mRect.y = y; }
	SDL_Rect GetRect() const { return mRect; }
	SDL_Texture* GetObject() const{ return pObject; }

	bool LoadImg(std::string path, SDL_Renderer* screen);
	void Render(SDL_Renderer* des, const SDL_Rect* clip = NULL);
	void Free();

protected:
	SDL_Texture* pObject;
	SDL_Rect mRect;
};

#endif // !BASE_OBJECT_H

