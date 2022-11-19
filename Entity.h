#pragma once

#include<SDL.h>

class Entity
{
public:
	Entity();
	~Entity();

	// Getters
	SDL_Rect GetRect();
	SDL_Color GetColor();

	// Setters
	void SetRect(uint32_t x, uint32_t y, uint32_t w, uint32_t h);
	void SetColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a);

private:
	// rect default to 50x50 at 0, 0
	SDL_Rect self = { 0, 0, 50, 50 };
	// color default to white
	SDL_Color color = { 255, 255, 255, 1 };
};

