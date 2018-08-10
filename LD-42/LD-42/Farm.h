#pragma once
#include "Entity.h"
#include "Animation.h"

class Farm
	: public Entity
{
public:
	Animation farmAnimation;

	int hp = 100;

	bool init(int X, int Y, int W, int H, int cW, int cH, double rotation = 0.0);
	void setCenterPos(int x, int y);
	void update();
	Animation* getAnimation();
	void close();
	void subHP(int h) { hp -= h; }
	int getHP() { return hp; }
	void setHP(int h) { hp = h; }
};

