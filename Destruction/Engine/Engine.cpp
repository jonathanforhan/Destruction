#include "Engine.h"

Engine::Engine(Ball* ballPtr, std::vector<Block>* blocksPtr, Platform* platformPtr)
	: ball(ballPtr), blocks(blocksPtr), platform(platformPtr), lastTick(SDL_GetTicks64())
{
	GetDeltaTime();
}

void Engine::GetDeltaTime()
{
	uint64_t current = SDL_GetTicks64();
	dT = (current - lastTick) / 1000.0f;
	lastTick = current;
}

void Engine::UpdateEntities(bool& ballStart)
{
	blockData = blocks->data();
	// loop through every entity and collision check them
	for (int i{}; i < 21; i++)
	{
		CheckCollision(&blockData[i], i, blockData);

		
		ApplyVelocity(&blockData[i]);
		ApplyGravity(&blockData[i]);
	}
	if (ballStart)
	{
		CheckCollision(ball, -1, blockData);
		ApplyVelocity(ball);
		ApplyGravity(ball);
	}
}

void Engine::ApplyVelocity(Entity* ent)
{
	ent->Move(ent->GetX() - (ent->GetAngleX() * ent->GetSpeed() * dT), ent->GetY());
	ent->Move(ent->GetX(), ent->GetY() - (ent->GetAngleY() * ent->GetSpeed() * dT));
	if(ent->GetSpeed() > 0)
		ent->SetSpeed(static_cast<float>(ent->GetSpeed() * 0.998));
}

void Engine::ApplyGravity(Entity* ent)
{
	if (ent->bottom == true)
		return;

	if (ent->GetGFactor() == 0)
		ent->ResetGFactor();

	ent->Move(ent->GetX(), ent->GetY() + ent->GetGFactor() * dT);
	ent->TickGFactor(gravity);
}

void Engine::CheckCollision(Entity* ent, int index, Entity blockData[])
{
	struct collision {
		bool top;
		bool bottom;
		bool left;
		bool right;
	};

	collision col = {};
	bool bottomTracker = {};

	for (int i{}; i < 21; i++)
	{

		if (i == index) // can't collide with itself
			continue;

		// collision detection for entities
		if (((ent->GetRect()->y <= blockData[i].GetRect()->y + blockData[i].GetRect()->h &&
			ent->GetRect()->y >= blockData[i].GetRect()->y) ||
			(ent->GetRect()->y + ent->GetRect()->h >= blockData[i]. GetRect()->y &&
			ent->GetRect()->y + ent->GetRect()->h <= blockData[i].GetRect()->y + blockData[i].GetRect()->h)) &&
			((ent->GetRect()->x <= blockData[i].GetRect()->x + blockData[i].GetRect()->w &&
			ent->GetRect()->x >= blockData[i].GetRect()->x) ||
			(ent->GetRect()->x + ent->GetRect()->w >= blockData[i].GetRect()->x &&
			ent->GetRect()->x + ent->GetRect()->w <= blockData[i].GetRect()->x + blockData[i].GetRect()->w)))
		{
			if (ent->GetRect()->x + ent->GetRect()->w >= blockData[i].GetRect()->x && ent->GetRect()->x <= blockData[i].GetRect()->x)
				col.right = true;
			if (ent->GetRect()->x <= blockData[i].GetRect()->x + blockData[i].GetRect()->w && ent->GetRect()->x + ent->GetRect()->w >= blockData[i].GetRect()->x + blockData[i].GetRect()->w)
				col.left = true;
			if (ent->GetRect()->y + ent->GetRect()->h >= blockData[i].GetRect()->y && ent->GetRect()->y < blockData[i].GetRect()->y)
				col.bottom = true;
			if (ent->GetRect()->y <= blockData[i].GetRect()->y + blockData[i].GetRect()->h && ent->GetRect()->y + ent->GetRect()->h >= blockData[i].GetRect()->y + blockData[i].GetRect()->h)
				col.top = true;
		}

		if (col.bottom && ent->GetID() != 'B')
		{
			ent->SetAngleY(0);
			ent->DisableGFactor();
			ent->SetSpeed(ent->GetSpeed() * 0.999f);
			bottomTracker = true;
		}
		if (col.right && col.left)
		{
			continue;
		}
		else if (col.right && ent->GetID() == 'B')
		{
			blockData[i].SetAngleX(ent->GetAngleX());
			ent->SetAngleX(-(ent->GetAngleX()));
			float speed = (ent->GetSpeed() + blockData[i].GetSpeed()) * 0.1f;
			ent->SetSpeed(ball->GetSpeed());
			blockData[i].SetSpeed(ball->GetSpeed() / 2);
			SDL_SetTextureColorMod(blockData[i].GetTexture(), ball->GetColor()->r, ball->GetColor()->g, ball->GetColor()->b);
		}
		else if (col.left && ent->GetID() == 'B')
		{
			blockData[i].SetAngleX(ent->GetAngleX());
			ent->SetAngleX(-(ent->GetAngleX()));
			float speed = (ent->GetSpeed() + blockData[i].GetSpeed() * 0.1f);
			ent->SetSpeed(ball->GetSpeed());
			blockData[i].SetSpeed(ball->GetSpeed() / 2);
			SDL_SetTextureColorMod(blockData[i].GetTexture(), ball->GetColor()->r, ball->GetColor()->g, ball->GetColor()->b);
		}
	}

	col = {};

	// platform physics
	if (((ent->GetRect()->y <= platform->GetRect()->y + platform->GetRect()->h &&
		ent->GetRect()->y >= platform->GetRect()->y) ||
		(ent->GetRect()->y + ent->GetRect()->h >= platform->GetRect()->y &&
		ent->GetRect()->y + ent->GetRect()->h <= platform->GetRect()->y + platform->GetRect()->h)) &&
		((ent->GetRect()->x <= platform->GetRect()->x + platform->GetRect()->w &&
		ent->GetRect()->x >= platform->GetRect()->x) ||
		(ent->GetRect()->x + ent->GetRect()->w >= platform->GetRect()->x &&
		ent->GetRect()->x + ent->GetRect()->w <= platform->GetRect()->x + platform->GetRect()->w)))
	{
		if (ent->GetRect()->x + ent->GetRect()->w >= platform->GetRect()->x && ent->GetRect()->x <= platform->GetRect()->x)
			col.right = true;
		if (ent->GetRect()->x <= platform->GetRect()->x + platform->GetRect()->w && ent->GetRect()->x + ent->GetRect()->w >= platform->GetRect()->x + platform->GetRect()->w)
			col.left = true;
		if (ent->GetRect()->y + ent->GetRect()->h >= platform->GetRect()->y && ent->GetRect()->y <= platform->GetRect()->y)
			col.bottom = true;
		if (ent->GetRect()->y <= platform->GetRect()->y + platform->GetRect()->h && ent->GetRect()->y + ent->GetRect()->h >= platform->GetRect()->y + platform->GetRect()->h)
			col.top = true;
	}
	if (col.bottom)
	{
		ent->SetAngleY(0);
		ent->DisableGFactor();
		ent->SetSpeed(ent->GetSpeed() * 0.999f);
		if (ent->GetY() + ent->GetRect()->h > platform->GetY())
			ent->Move(ent->GetX(), platform->GetY() - ent->GetRect()->h);
		bottomTracker = true;
	}
	if (col.right && !col.bottom)
	{
		ent->SetAngleX(-(ent->GetAngleX()));
	}
	else if (col.left && !col.bottom)
	{
		ent->SetAngleX(-(ent->GetAngleX()));
	}

	if (bottomTracker)
		ent->bottom = true;
	else
		ent->bottom = false;

	col = {};
}