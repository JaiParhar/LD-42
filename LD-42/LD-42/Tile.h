#pragma once
#include "Animation.h"
#include "Utility.h"

class Tile
{
public:
	bool collidable;

	Animation* animation;

	int ID;

	int x;
	int y;

	float angle;

	void init(int X, int Y, Animation* a, bool col, int i, float ang = 0.0f);
	void update();
	Animation* getAnimation();
	bool isCollidable();
	int getX();
	int getY();
	float getAngle();
	int getID();
};

