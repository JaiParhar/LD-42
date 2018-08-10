#pragma once
class Camera
{
public:
	Camera();

	int x;
	int y;
	int screenWidth;
	int screenHeight;

	bool init(int X, int Y, int SW, int SH);
	void setCameraCenterPos(int X, int Y);
	void setCameraPos(int X, int Y);

	int getX() { return x; }
	int getY() { return y; }
	int getScreenWidth() { return screenWidth; }
	int getScreenHeight() { return screenHeight; }

	~Camera();
};

