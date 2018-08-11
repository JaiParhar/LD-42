#pragma once
#include "GameState.h"
#include "Spritesheet.h"
#include "Animation.h"
#include "Player.h"
#include "Terrain.h"
#include "InputManager.h"
#include <SDL_mixer.h>

class GameplayState :
	public GameState
{
public:
	int* currentState;

	Spritesheet playerSheet;
	Player player;

	Spritesheet terrainSheet;
	Terrain terrain;

	InputManager inputM;

	bool init(int* cS, Renderer* r, Camera* c);
	bool close();

	void pause();
	void resume();

	void input(SDL_Event* event);
	void update();
	void render();

};

