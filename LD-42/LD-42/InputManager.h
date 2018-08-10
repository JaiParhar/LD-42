#pragma once
#include <SDL.h>

#define K_UP 0
#define K_DOWN 1
#define K_LEFT 2
#define K_RIGHT 3

#define K_W 4
#define K_S 5
#define K_A 6
#define K_D 7
#define K_R 18

#define K_1 8
#define K_2 9
#define K_3 10
#define K_4 11
#define K_5 12
#define K_6 13
#define K_7 14
#define K_8 15
#define K_9 16
#define K_0 17

class InputManager
{
public:
	const static int numKeys = 19;
	bool keyPressed[numKeys];
	bool init();
	void input(SDL_Event* event);
};

