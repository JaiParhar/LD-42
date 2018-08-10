#pragma once
#include "Entity.h"
#include "Utility.h"
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <String>
#include <vector>

class Bullet
	: public Entity
{
public:
	int ID;

	int bulletSpeed;
	int bulletDamage;
	int spriteID;

	bool init(int X, int Y, int W, int H, int cW, int cH, double rotation = 0.0);
	void setBulletID(int BulletID);

	void update();

	void loadBulletType(std::string fPath, int bulletID);

	int getBulletSpeed();
	int getSpriteID();

	void close();
};

