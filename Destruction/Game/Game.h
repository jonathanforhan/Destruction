#pragma once

#include<iostream>
#include<vector>

#include"RenderWindow.h"
#include"EventHandler.h"
#include"../Engine/Engine.h"
#include"Entity.h"
#include"Platform.h"
#include"Block.h"
#include"Ball.h"

class Game
{
public:
	Game();
	~Game();

	void Run();
private:
	// Game's RenderWindow
	RenderWindow renderWindow = RenderWindow("Destruction", WIN_WIDTH, WIN_HEIGHT);

	// Game Objects
	std::vector<Block> blocks{21};
	Platform platform;
	Ball ball;
	// Game Object Ptrs
	std::vector<Block>* blocksPtr = &blocks;
	Platform* platformPtr = &platform;
	Ball* ballPtr = &ball;

	// menu obj
	Entity menu;

	// Block Functions
	void SetBlocks();
	// Ball functions
	void ResetBall();

	bool Menu();
};

