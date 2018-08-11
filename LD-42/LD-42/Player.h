#pragma once
#include "Entity.h"
#include <Math.h>
#include "Timer.h"
#include "Utility.h"

#define _USE_MATH_DEFINES

class Player :
	public Entity
{
public:

	const static int walkAnimationSpeedMod = 1;

	int direction = 0;

	bool shooting = false;
	bool moving = false;

	int movementSpeedMS = 250;
	Timer movementTimer;

	bool init(int X, int Y);
	bool initAnimations();
	void update();
	void move(int dir);
	int getDirection();
	void close();
};

