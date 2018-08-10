#include "Camera.h"



Camera::Camera()
{
}

bool Camera::init(int X, int Y, int SW, int SH)
{
	x = X;
	y = Y;
	screenWidth = SW;
	screenHeight = SH;
	return true;
}

void Camera::setCameraCenterPos(int X, int Y) 
{
	x = X - ((getScreenWidth()) / 2);
	y = Y - ((getScreenHeight()) / 2);
}

void Camera::setCameraPos(int X, int Y) 
{
	x = X;
	y = Y;
}

Camera::~Camera()
{
}
