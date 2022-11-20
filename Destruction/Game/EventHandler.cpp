#include "EventHandler.h"

EventHandler::EventHandler(Entity* p_entity)
{
	ball = p_entity;
	origin_x = ball->GetRect()->x;
	origin_y = ball->GetRect()->y;
}

bool EventHandler::MouseDown(int& x, int& y)
{

	if (x > ball->GetRect()->x && x < ball->GetRect()->x + ball->GetRect()->w)
	{
		if (y > ball->GetRect()->y && y < ball->GetRect()->y + ball->GetRect()->h)
		{
			return true;
		}
	}
	return false;
}

void EventHandler::Drag(int& x, int& y)
{
	// distance from ball's origin
	int distance_x = x - origin_x;
	int distance_y = y - origin_y;
	// capping drag distance
	if (distance_x >= 800)
		distance_x = 800;
	else if (distance_x <= -800)
		distance_x = -800;
	if (distance_y >= 800)
		distance_y = 800;
	else if (distance_y <= -800)
		distance_y = -800;

	// drag functionality <need to offset origin calc so i add the w&h>
	ball->Move(origin_x + distance_x / 4, origin_y + distance_y / 4);

	// set ball speed on launch
	if ((distance_x < 500 && distance_x > -500) && (distance_y < 500 && distance_y > -500))
	{
		if (distance_x >= distance_y)
			ball->SetSpeed(abs(distance_x) * 2);
		else
			ball->SetSpeed(abs(distance_y) * 2);
	}
	else
	{
		ball->SetSpeed(1000); // speed cap
	}

	// set ball angle on launch
	ball->SetAngleX(distance_x / 80.0f);
	ball->SetAngleY(distance_y / 80.0f);
}
