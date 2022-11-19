#pragma once

#include<iostream>
#include<vector>

#include"RenderWindow.h"
#include"Entity.h"
#include"Block.h"
#include"Ball.h"

// easy logging
#define Log(x) std::cout << x << '\n';

class Game
{
public:
	Game();
	~Game();

	void Run();
private:
	// Game's RenderWindow
	RenderWindow renderWindow = RenderWindow("Destruction", WIN_WIDTH, WIN_HEIGHT);

	std::vector<Block> blocks{21};

	// Block Functions
	void SetBlocks();


};

