#include "Entity.h"

Entity::Entity()
	:x(static_cast<float>(self.x)), y(static_cast<float>(self.y))
{
}

Entity::~Entity()
{
}

void Entity::Move(float px, float py)
{
	x = px;
	y = py;
	self.x = (int)x;
	self.y = (int)y;
}

const float& Entity::GetX()
{
	return x;
}

const float& Entity::GetY()
{
	return y;
}

const SDL_Rect* Entity::GetRect()
{
	return &self;
}

const SDL_Color* Entity::GetColor()
{
	return &color;
}

SDL_Texture* Entity::GetTexture()
{
	return texture;
}

const SDL_Rect* Entity::GetTextureSprite()
{
	return &textureSprite;
}

const char& Entity::GetID()
{
	return identity;
}

const float& Entity::GetSpeed()
{
	return speed;
}

const float& Entity::GetAngleX()
{
	return angle_x;
}

const float& Entity::GetAngleY()
{
	return angle_y;
}

const float& Entity::GetGFactor()
{
	return gFactor;
}

void Entity::SetRect(int x, int y, uint32_t w, uint32_t h)
{
	self.x = x; self.y = y;
	self.w = w; self.h = h;
	this->x = (float)x;
	this->y = (float)y;
}

void Entity::SetColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	color.r = r;
	color.g = g;
	color.b = b;
	color.a = a;
}

void Entity::SetTexture(SDL_Renderer* renderer, const char* filepath)
{
	if (!(texture = IMG_LoadTexture(renderer, filepath)))
		throw SDL_GetError();
}

void Entity::SetIdentity(const char& id)
{
	identity = id;
}

void Entity::SetSpeed(const float& p_speed)
{
	speed = p_speed;
}

void Entity::SetAngleX(const float& p_angle)
{
	angle_x = p_angle;
}

void Entity::SetAngleY(const float& p_angle)
{
	angle_y = p_angle;
}

void Entity::TickGFactor(const float& Gs)
{
		gFactor *= 1 + (1.0f / Gs);
}

void Entity::ResetGFactor()
{
	gFactor = 980;
}

void Entity::DisableGFactor()
{
	gFactor = 0;
}