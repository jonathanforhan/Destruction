#pragma once

#include<SDL.h>
#include"Ball.h"

#include<iostream>
#define eLog(x) std::cout << x << '\n';

class EventHandler
{
public:
	EventHandler(Entity* entity);

	// Checkers
	bool MouseDown(int& x, int& y);

	// Actions
	void Drag(int& x, int& y);

private:
	Entity* ball; // could be changed later to other entities or entitiy vectors for sizabilty :)
	
	// Origin point
	int origin_x;
	int origin_y;
};