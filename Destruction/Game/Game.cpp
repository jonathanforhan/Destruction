#include "Game.h"

Game::Game()
{
	// Initialize SDL subsytems
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
		throw SDL_GetError();

	ball.SetTexture(renderWindow.GetRenderer(), "Textures/Ball.png");
	for (auto& block : blocks)
	{
		block.SetTexture(renderWindow.GetRenderer(), "Textures/Block.png");
	}
	menu.SetTexture(renderWindow.GetRenderer(), "Textures/Destruction.png");
	SetBlocks();
	ResetBall();
}

Game::~Game()
{
}

void Game::Run()
{
	// data handlers
	Engine physicsEngine(&ball, &blocks, &platform);
	EventHandler eventHandler(&ball);
	SDL_Event m_Event;

	bool drag{};
	int x{};
	int y{};

	bool ballLaunch{};

	while (true)
	{
		if (SDL_PollEvent(&m_Event))
		{
			// inputs to be shipped off to event handler
			switch (m_Event.type)
			{
			case SDL_QUIT:
				SDL_Quit();
				return;
			case SDL_MOUSEBUTTONDOWN:
				SDL_GetMouseState(&x, &y);
				if (eventHandler.MouseDown(x, y))
					drag = true;
				break;
			case SDL_MOUSEBUTTONUP:
				drag = false;
				ballLaunch = true;
				break;
			case SDL_KEYDOWN:
				ballLaunch = false;
 				ResetBall();
				break;
			}

			if (drag)
			{
				SDL_GetMouseState(&x, &y);
				eventHandler.Drag(x, y);
			}
		}

		physicsEngine.GetDeltaTime(); // for system continuity
		physicsEngine.UpdateEntities(ballLaunch);

		SDL_Delay(1);

		// main render loop
		renderWindow.Clear();
		renderWindow.Render(platform);
		renderWindow.Render(ball);
		for (auto& block : blocks)
		{
			renderWindow.Render(block);
		}
		renderWindow.Display();

		if (Menu()) // menu check for end of game
			ballLaunch = false;
	}
}

void Game::SetBlocks()
{
	int x = 400;
	int y = 250;
	int n = 0;
	for (int j{1}; j <= 6; j++)
	{
		for (int i{}; i < j; i++)
		{
			blocks[n].Move((float)x, (float)y);
			SDL_SetTextureColorMod(blocks[n].GetTexture(), 255, 255, 255);
			// must reset data so they dont spaz when you reset lol
			blocks[n].SetAngleX(0);
			blocks[n].SetAngleY(0);
			blocks[n].SetSpeed(0);
			blocks[n].ResetGFactor();
			x += 51;
			n++;
		}
		x -= (50 * j + 25); y += 50;
	}
}

void Game::ResetBall()
{
	ball.Move(1000, 400);
	ball.SetAngleX(0);
	ball.SetAngleY(0);
	ball.SetSpeed(0);
	ball.ResetGFactor();

	// random color generator for ball
	srand(static_cast<unsigned int>(SDL_GetTicks64()));
	uint8_t r = rand() % 256;
	uint8_t g = rand() % 256;
	uint8_t b = rand() % 256;
	ball.SetColor(r, g, b, 255);
	SDL_SetTextureColorMod(ball.GetTexture(), r, g, b);
}

bool Game::Menu()
{
	int n = 0;
	for (auto& block : blocks)
	{
		if (block.GetY() > 1200)
			n++;
	}
	if (n == blocks.size())
	{
		SDL_Event menu_event;
		menu.SetRect(300, 0, 800, 800);
		while(true)
		{
			// random color generator for ball
			srand(static_cast<unsigned int>(SDL_GetTicks64()));
			uint8_t r = rand() % 256;
			uint8_t g = rand() % 256;
			uint8_t b = rand() % 256;
			ball.SetColor(r, g, b, 255);
			// essential renderWindow.clear() but with fancy colors
			SDL_SetRenderDrawColor(renderWindow.GetRenderer(), r, g, b, 255);
			SDL_RenderClear(renderWindow.GetRenderer());
			SDL_Delay(500);

			SDL_RenderCopyEx(renderWindow.GetRenderer(), menu.GetTexture(), NULL, menu.GetRect(), NULL, NULL, SDL_FLIP_NONE);

			renderWindow.Display();

			if (SDL_PollEvent(&menu_event))
			{
				// inputs to be shipped off to event handler
				switch (menu_event.type)
				{
				case SDL_QUIT:
					SDL_Quit();
					break;
				case SDL_KEYDOWN:
					ResetBall();
					SetBlocks();
					return true;
				}
			}
		}
	}
	return false;
}