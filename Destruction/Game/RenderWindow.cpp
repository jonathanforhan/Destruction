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

	if (entity.GetTexture() != nullptr)
	{
		// rendering for dynamic entities
		SDL_RenderCopyEx(renderer, entity.GetTexture(), NULL, entity.GetRect(), NULL, NULL, SDL_FLIP_NONE);
	}
	else
	{
		// main platform render
		SDL_SetRenderDrawColor(renderer, entity.GetColor()->r, entity.GetColor()->g, entity.GetColor()->b, entity.GetColor()->a);
		SDL_RenderFillRect(renderer, entity.GetRect());
	}

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

