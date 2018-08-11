#pragma once
#include "Animation.h"

class Tile
{
public:
	bool collidable;

	Animation* animation;

	int ID;

	int x;
	int y;

	void init(int X, int Y, Animation* a, bool col, int i);
	void update();
	Animation* getAnimation();
	bool isCollidable();
	int getX();
	int getY();
	int getID();
};

