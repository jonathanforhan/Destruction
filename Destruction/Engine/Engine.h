#pragma once

#include<SDL.h>

#include"../Game/Entity.h"
#include"../Game/Ball.h"
#include"../Game/Platform.h"
#include"../Game/Block.h"

#include<vector>

#include<iostream>
#define eLog(x) std::cout << x << '\n';

class Engine
{
public:
	Engine(Ball* ballPtr, std::vector<Block>* blocksPtr, Platform* platformPtr);
	
	void GetDeltaTime(); // for timing across differnt systems and qualities

	void UpdateEntities(bool& ballStart);


private:
	// entities
	Ball* ball;
	std::vector<Block>* blocks;
	Platform* platform;

	Block* blockData;

	// timing info
	uint64_t lastTick;
	float dT{};

	// constants
	const float gravity = 1100.0f;

	// physics functions
	void ApplyVelocity(Entity* ent);
	void ApplyGravity(Entity* ent);
	void CheckCollision(Entity* ent, int index, Entity blockData[]);
};