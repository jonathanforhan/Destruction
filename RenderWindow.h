#pragma once

#include<SDL.h>

#include"Entity.h"

#define WIN_WIDTH 1200
#define WIN_HEIGHT 800

class RenderWindow
{
public:
	RenderWindow();
	RenderWindow(const char* title, int width, int height);
	~RenderWindow();

	// Render Loop
	void Clear();
	void Render(Entity& entity);
	void Display();

	// Getters
	SDL_Window* GetWindow();
	SDL_Renderer* GetRenderer();

private:

	SDL_Window* window;
	SDL_Renderer* renderer;
};

