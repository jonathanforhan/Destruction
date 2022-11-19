#include "RenderWindow.h"

RenderWindow::RenderWindow()
	: window(nullptr), renderer(nullptr)
{
	// create window
	window = SDL_CreateWindow("Default", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 400, 400, SDL_WINDOW_SHOWN);
	if (!window)
		throw SDL_GetError();

	// create renderer
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (!renderer)
		throw (SDL_GetError());
}

RenderWindow::RenderWindow(const char* title, int width, int height)
	: window(nullptr), renderer(nullptr)
{
	// create window
	window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
	if (!window)
		throw SDL_GetError();

	// create renderer
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (!renderer)
		throw (SDL_GetError());
}

RenderWindow::~RenderWindow()
{
	// clean up
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
}

void RenderWindow::Clear()
{
	SDL_SetRenderDrawColor(renderer, 70, 70, 70, 1);
	SDL_RenderClear(renderer);
}

void RenderWindow::Render(Entity& entity)
{
	// must do this for L-value reasons
	auto rect = entity.GetRect();
	// main block render
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 1);
	SDL_RenderFillRect(renderer, &rect);
	// Draws black outline for better effect
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 1);
	SDL_RenderDrawRect(renderer, &rect);
}

void RenderWindow::Display()
{
	SDL_RenderPresent(renderer);
}

SDL_Window* RenderWindow::GetWindow()
{
	return window;
}

SDL_Renderer* RenderWindow::GetRenderer()
{
	return renderer;
}

