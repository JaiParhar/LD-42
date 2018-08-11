#include "Player.h"

bool Player::init(int X, int Y, int W, int H, double rotation)
{
	x = X;
	y = Y;
	w = W;
	h = H;

	baseWalkSpeed = 3.5;

	initAnimations();

	return true;
}

bool Player::initAnimations()
{
	return true;
}

void Player::update()
{
	//Will be pos if above or to the left of
	x += xvel;
	y += yvel;

	switch (direction)
	{
	case UP:
		flip = SDL_FLIP_NONE;
		break;
		
	case DOWN:
		flip = SDL_FLIP_NONE;
		break;

	case LEFT:
		flip = SDL_FLIP_HORIZONTAL;
		break;

	case RIGHT:
		flip = SDL_FLIP_NONE;
		break;
	}

	if (yvel == 0 && xvel == 0)
	{
		moving = false;
	}
}

void Player::move(int dir)
{
	moving = true;
	if (!shooting)
	{
		direction = dir;
	}

	if (dir == UP)
	{
		yvel = -baseWalkSpeed;
	}

	if (dir == DOWN)
	{
		yvel = baseWalkSpeed;
	}

	if (dir == LEFT)
	{
		xvel = -baseWalkSpeed;
	}

	if (dir == RIGHT)
	{
		xvel = baseWalkSpeed;
	}
}

void Player::stopMovingX()
{
	xvel = 0;
}

void Player::stopMovingY()
{
	yvel = 0;
}

void Player::close() 
{
}

int Player::getDirection()
{
	return direction;
}