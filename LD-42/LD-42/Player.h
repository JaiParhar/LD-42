#pragma once
#include "Entity.h"
#include <Math.h>
#include "Timer.h"

#define _USE_MATH_DEFINES
#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3

#define SIDE 2

class Player :
	public Entity
{
public:

	const static int walkAnimationSpeedMod = 1;

	int baseWalkSpeed;

	int direction = 0;

	bool shooting = false;
	bool moving = false;

	bool init(int X, int Y, int W, int H, double rotation = 0.0);
	bool initAnimations();
	void update();
	void move(int dir);
	void stopMovingX();
	void stopMovingY();
	int getDirection();
	void close();
};

