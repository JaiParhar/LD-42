#pragma once
#include <SDL.h>

class Entity
{
public:
	double x;
	double y;
	int w;
	int h;
	double rot = 0.0;
	int flip = SDL_FLIP_NONE;
	double xvel = 0.0;
	double yvel = 0.0;
	
	int scaleX = 1;
	int scaleY = 1;

	virtual bool init(int X, int Y, int W, int H, double rotation = 0.0) = 0;
	virtual void update() = 0;

	void setX(int X) { x = X; }
	void setY(int Y) { y = Y; }
	void setXVel(double Xvel) { xvel = Xvel; }
	void setYVel(double Yvel) { yvel = Yvel; }
	void setAngle(double r) { rot = r; }

	int getX() { return x; }
	int getY() { return y; }
	int getXVel() { return xvel; }
	int getYVel() { return yvel; }
	int getCenterX() { return x+(getW()/2); }
	int getCenterY() { return y+(getH()/2); }
	int getW() { return w; }
	int getH() { return h; }
	double getAngle() { return rot; }
	int getFlip() { return flip; }
	
	SDL_Rect* hitBox(int xvel = 0, int yvel = 0) { SDL_Rect* hitBox = new SDL_Rect; hitBox->x = x + xvel; hitBox->y = y + yvel; hitBox->w = w; hitBox->h = h; return hitBox; }

	bool checkCollision(Entity* e, int xvel = 0, int yvel = 0)
	{
		SDL_Rect* collRect = new SDL_Rect;
		return SDL_IntersectRect(hitBox(xvel, yvel), e->hitBox(), collRect) == SDL_TRUE;
	}

	virtual void close() = 0;
};

