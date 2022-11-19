#include "Entity.h"

Entity::Entity()
{
}

Entity::~Entity()
{
}

SDL_Rect Entity::GetRect()
{
	return self;
}

SDL_Color Entity::GetColor()
{
	return color;
}

void Entity::SetRect(uint32_t x, uint32_t y, uint32_t w, uint32_t h)
{
	self.x = x; self.y = y;
	self.w = w; self.h = h;
}

void Entity::SetColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	color.r = r;
	color.g = g;
	color.b = b;
	color.a = a;
}

