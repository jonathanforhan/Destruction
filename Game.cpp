#include "Game.h"

Game::Game()
{
	// Initialize SDL subsytems
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
		Log("SDL init failed. Error: " << SDL_GetError());

	SetBlocks();
}

Game::~Game()
{
}

void Game::Run()
{
	SDL_Event m_Event;

	while (true)
	{
		while (SDL_WaitEvent(&m_Event))
		{
			switch (m_Event.type)
			{
			case SDL_QUIT:
				SDL_Quit();
				break;
			}

			renderWindow.Clear();
			for (auto& n : blocks)
			{
				renderWindow.Render(n);
			}
			renderWindow.Display();
		}
	}
}

void Game::SetBlocks()
{
	int x = 575;
	int y = 250;
	int n = 0;
	for (int j{1}; j <= 6; j++)
	{
		for (int i{}; i < j; i++)
		{
			blocks[n].SetRect(x, y, 50, 50);
			x += 50;
			n++;
		}
		x -= (50 * j + 25); y += 50;
	}
}

