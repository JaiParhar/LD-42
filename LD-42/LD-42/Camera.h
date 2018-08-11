#pragma once
#include "Timer.h"
#include "Utility.h"

class Camera
{
public:
	double x;
	double y;
	
	int screenWidth;
	int screenHeight;

	int movementSpeedMS;
	Timer movementTimer;

	int direction = 0;

	bool moving = false;

	double prevX;
	double prevY;

	bool init(int X, int Y, int SW, int SH);
	void setCameraPos(int X, int Y);

	void moveCameraScreen(int dir);
	void update();

	double getXPos() { return x*screenWidth; }
	double getYPos() { return y*screenHeight; }
	int getScreenWidth() { return screenWidth; }
	int getScreenHeight() { return screenHeight; }
};

