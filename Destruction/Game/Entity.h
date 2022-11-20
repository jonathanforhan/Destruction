#pragma once

#include<SDL.h>
#include<SDL_image.h>

class Entity
{
public:
	Entity();
	~Entity();

	// --Functions-- //
	void Move(float x, float y);

	// ---Getters--- //

	// rect info
	const float& GetX();
	const float& GetY();
	const SDL_Rect* GetRect();
	const SDL_Color* GetColor();
	// sprite info
	SDL_Texture* GetTexture();
	const SDL_Rect* GetTextureSprite();
	// ID
	const char& GetID();
	// physics info
	const float& GetSpeed();
	const float& GetAngleX();
	const float& GetAngleY();
	const float& GetGFactor();

	// ---Setters--- //

	// rect sets
	void SetRect(int x, int y, uint32_t w, uint32_t h);
	void SetColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
	// texture sets
	void SetTexture(SDL_Renderer* renderer, const char* filepath);
	// physics sets
	void SetIdentity(const char& id);
	void SetSpeed(const float& speed);
	void SetAngleX(const float& angle);
	void SetAngleY(const float& angle);
	void TickGFactor(const float& Gs);
	void ResetGFactor();
	void DisableGFactor();

	// for gravity
	bool bottom = false;
private:
	// rect default to 50x50 at 0, 0
	SDL_Rect self = { 0, 0, 50, 50 };
	float x;
	float y;
	// color default to white
	SDL_Color color = { 255, 255, 255, 255 };
	// Texture info
	SDL_Texture* texture = nullptr;
	SDL_Rect textureSprite = { 0, 0, 256, 256 };
	// ID info
	char identity = 'n';


	// Physics info
	float speed{};
	float angle_x{};
	float angle_y{};
	float gFactor{980}; // time spent in gravity fall

};

