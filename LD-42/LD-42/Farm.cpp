#include "Farm.h"

bool Farm::init(int X, int Y, int W, int H, int cW, int cH, double rotation)
{
	x = X;
	y = Y;
	w = W;
	h = H;
	collisionWidth = cW;
	collisionHeight = cH;

	farmAnimation.init(500);
	farmAnimation.addFrame(0);
	farmAnimation.addFrame(1);

	setHP(100);

	return true;
}

void Farm::setCenterPos(int X, int Y)
{
	x = X - (w / 2);
	y = Y - (h / 2);
}

void Farm::update()
{
	farmAnimation.update();
	if (hp < 0)
	{
		hp = 0;
	}
}

Animation* Farm::getAnimation()
{
	return &farmAnimation;
}

void Farm::close()
{
}
