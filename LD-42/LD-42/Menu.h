#pragma once
#include "GameState.h"
#include "Utility.h"
#include "Timer.h"

class Menu:
	public GameState
{
public:

	SDL_Texture* mainMenu;

	Timer inputTimer;
	
	bool init(int* cS, Renderer* r, Camera* c);
	bool close() { return true; }

	void pause() {};
	void resume() {};

	void input(SDL_Event* event);
	void update();
	void render();
};

