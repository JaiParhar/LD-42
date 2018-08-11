#include "Player.h"

bool Player::init(int X, int Y)
{
	x = X;
	y = Y;

	movementTimer.initTimer(movementSpeedMS);

	initAnimations();

	return true;
}

bool Player::initAnimations()
{
	return true;
}

void Player::setTerrain(Terrain * t)
{
	terrain = t;
}

void Player::update()
{
	movementTimer.checkTimer();
	if (movementTimer.isTimerDone()) 
	{
		movementTimer.timerReset();
		moving = false;
		
		x = prevX;
		y = prevY;

		switch (direction)
		{
		case UP:
			y--;
			break;

		case DOWN:
			y++;
			break;

		case LEFT:
			x--;
			break;

		case RIGHT:
			x++;
			break;
		}
	}

	if (moving)
	{
		switch (direction)
		{
		case UP:
			y = (double)(prevY - pow((1.0f / movementSpeedMS) * (movementTimer.getTime()), 4));
			break;

		case DOWN:
			y = (double)(prevY + pow((1.0f / movementSpeedMS) * (movementTimer.getTime()), 4));
			break;

		case LEFT:
			x = (double)(prevX - pow((1.0f / movementSpeedMS) * (movementTimer.getTime()), 4));
			break;

		case RIGHT:
			x = (double)(prevX + pow((1.0f / movementSpeedMS) * (movementTimer.getTime()), 4));
			break;
		}
	}
}

void Player::move(int dir)
{
	if (!moving)
	{
		moving = true;
		movementTimer.startTimer();
		
		prevX = x;
		prevY = y;

		direction = dir;
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
	}
}

void Player::close() 
{
}

int Player::getDirection()
{
	return direction;
}