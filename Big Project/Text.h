#pragma once

#ifndef TEXT_H_
#define TEXT_H_

#include "CommonFunc.h"

class Text
{
public:
	Text();
	~Text();

	enum TextColor
	{
		YELLOW_TEXT,
		RED_TEXT,
		BLACK_TEXT,
		WHITE_TEXT
	};

	bool loadFromFile(std::string path);
	bool loadFromRenderText(TTF_Font* font, SDL_Renderer* screen);
	void Free();

	void setColor(Uint8 red, Uint8 green, Uint8 blue);
	void setColor(int type);

	void renderText(SDL_Renderer* screen,
		int x_pos, int y_pos,
		SDL_Rect* clip = NULL,
		double angle = 0.0,
		SDL_Point* center = NULL,
		SDL_RendererFlip flip = SDL_FLIP_NONE);

	int getWidth() const { return width; }
	int getHeight() const { return height; }
	
	void setText(const std::string& text) { str_val = text; }
	std::string getText() const { return str_val; }

private:
	std::string str_val;
	SDL_Color text_color;
	SDL_Texture* texture;
	int width;
	int height;
};


#endif // !TEXT_H_
