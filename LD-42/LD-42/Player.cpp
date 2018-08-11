#include "Player.h"

bool Player::init(int X, int Y)
{
	x = X;
	y = Y;

	movementTimer.initTimer(250);

	initAnimations();

	return true;
}

bool Player::initAnimations()
{
	return true;
}

void Player::update()
{
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

	movementTimer.checkTimer();
	if (movementTimer.isTimerDone()) 
	{
		moving = false;

	}
}

void Player::move(int dir)
{
	if (!moving)
	{
		moving = true;
		movementTimer.startTimer();
		
		int addX = 0;
		int addY = 0;
	}
}

void Player::close() 
{
}

int Player::getDirection()
{
	return direction;
}