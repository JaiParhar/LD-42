#pragma once
#include <SDL.h>

class Entity
{
public:
	int x;
	int y;
	int flip = SDL_FLIP_NONE;
	
	int scaleX = 1;
	int scaleY = 1;

	virtual bool init(int X, int Y) = 0;
	virtual void update() = 0;

	void setX(int X) { x = X; }
	void setY(int Y) { y = Y; }

	int getX() { return x; }
	int getY() { return y; }
	int getFlip() { return flip; }

	virtual void close() = 0;
};

