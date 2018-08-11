#include "Tile.h"

void Tile::init(int X, int Y, Animation* a, bool col, int i, float ang) 
{
	x = X;
	y = Y;
	animation = a;
	collidable = col;
	ID = i;
	angle = ang;
}

void Tile::update()
{
	animation->update();
}

Animation* Tile::getAnimation() 
{
	return animation;
}

bool Tile::isCollidable()
{
	return collidable;
}

int Tile::getX()
{
	return x;
}

int Tile::getY()
{
	return y;
}

float Tile::getAngle()
{
	return angle;
}

int Tile::getID()
{
	return ID;
}