#pragma once
#include "Renderer.h"
#include "GameState.h"
#include "GameplayState.h"
#include "Menu.h"
#include "GameOver.h"
#include <vector>

class GameStateManager
{
public:
	void initManager();
	void closeManager();

	void setState(int s);

	bool initStates(Renderer* r, Camera* c);
	bool closeStates();

	void input(SDL_Event* event);
	void update();
	void render();

	bool shouldQuit();
	void setQuit(bool q);

private:
	std::vector<GameState*> gameStates;
	int currentState;
};

