#pragma once
#include "Entity.h"
#include <stdio.h>
#include <iostream>
#include <Math.h>

#define FOOD 0
#define AMMO 1

class PowerUp:
	public Entity
{
public:
	int id;
	int type;
	int numItems;
	bool init(int X, int Y, int W, int H, int cW, int cH, double rotation = 0.0);
	int getID() { return id; }
	void update() {}
	void close() {}
};

