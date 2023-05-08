#include "CommonFunc.h"



bool SDLCommonFunc::isFocusWithRect(const int& x, const int& y, const SDL_Rect& rect)
{
	if (x >= rect.x && x <= (rect.x + rect.w)
		&& y >= rect.y && y <= (rect.y + rect.h))
	{
		return true;
	}

	return false;
}