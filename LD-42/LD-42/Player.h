#pragma once
#include "Entity.h"
#include <Math.h>
#include "Timer.h"
#include "Utility.h"
#include "Terrain.h"

#define _USE_MATH_DEFINES

class Player :
	public Entity
{
public:

	double prevX;
	double prevY;

	int direction = 0;

	bool shooting = false;
	bool moving = false;

	int movementSpeedMS = 125;
	Timer movementTimer;

	Terrain* terrain;

	bool init(int X, int Y);
	bool initAnimations();

	void setTerrain(Terrain* t);

	void update();

	void move(int dir);
	int getDirection();
	
	void close();
};

