#include "Text.h"

Text::Text()
{
	text_color.r = 255;
	text_color.b = 255;
	text_color.g = 255;
	texture = NULL;
}

Text::~Text()
{
	//
}

bool Text::loadFromRenderText(TTF_Font* font, SDL_Renderer* screen)
{
	SDL_Surface* text_surface = TTF_RenderText_Solid(font, str_val.c_str(), text_color);
	if (text_surface)
	{
		texture = SDL_CreateTextureFromSurface(screen, text_surface);
		width = text_surface->w;
		height = text_surface->h;
		
		SDL_FreeSurface(text_surface);
	}

	return texture != NULL;
}

void Text::Free()
{
	if (texture != NULL)
	{
		SDL_DestroyTexture(texture);
		texture = NULL;
	}  
}

void Text::setColor(int type)
{
	if (type == YELLOW_TEXT)
	{
		SDL_Color color = { 220, 150, 0 };
		text_color = color;
	}
	else if (type == RED_TEXT)
	{
		SDL_Color color = { 237, 28, 36 };
		text_color = color;
	}
}

void Text::renderText(SDL_Renderer* screen,
	int x_pos, int y_pos,
	SDL_Rect* clip /*= NULL*/,
	double angle /*= 0.0*/,
	SDL_Point* center/* = NULL*/,
	SDL_RendererFlip flip /*= SDL_FLIP_NONE*/)
{
	SDL_Rect renderQuad = { x_pos, y_pos, width, height };
	if (clip != NULL)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	SDL_RenderCopyEx(screen, texture, clip, &renderQuad, angle, center, flip);
}