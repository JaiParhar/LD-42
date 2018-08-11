#include "Camera.h"

bool Camera::init(int X, int Y, int SW, int SH)
{
	x = X;
	y = Y;
	screenWidth = SW;
	screenHeight = SH;

	movementSpeedMS = 1000;

	movementTimer.initTimer(movementSpeedMS);

	return true;
}

void Camera::setCameraPos(int X, int Y) 
{
	x = X;
	y = Y;
}

void Camera::moveCameraScreen(int dir)
{
	if (!moving)
	{
		moving = true;
		movementTimer.startTimer();

		prevX = x;
		prevY = y;

		direction = dir;
	}
}

void Camera::update()
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
