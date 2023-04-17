	#include "BaseObject.h"

BaseObject::BaseObject()
{
	pObject = NULL;
	rect.x = 0;
	rect.y = 0;
	rect.w = 0;
	rect.h = 0;
}

BaseObject::~BaseObject()
{
}

bool BaseObject::loadImg(std::string path, SDL_Renderer* screen)
{
	SDL_Texture* new_texture = NULL;
	SDL_Surface* load_surface = IMG_Load(path.c_str());
	if (load_surface == NULL)
		return false;

	SDL_SetColorKey(load_surface, SDL_TRUE, SDL_MapRGB(load_surface->format, COLOR_KEY_R, COLOR_KEY_G, COLOR_KEY_B));

	new_texture = SDL_CreateTextureFromSurface(screen, load_surface);
	if (new_texture == NULL) 
		return false;

	rect.w = load_surface->w;
	rect.h = load_surface->h;

	SDL_FreeSurface(load_surface);

	pObject = new_texture;
	if (pObject == NULL) 
		return false;

	return true;
}

void BaseObject::Render(SDL_Renderer* des, const SDL_Rect* clip)
{
	SDL_Rect renderquad = { rect.x, rect.y, rect.w, rect.h };

	SDL_RenderCopy(des, pObject, clip, &renderquad);
}

void BaseObject::Free()
{
	if (pObject != NULL)
	{
		SDL_DestroyTexture(pObject);
		pObject = NULL;
		rect.w = 0;
		rect.h = 0;

	}
}