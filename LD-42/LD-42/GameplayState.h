#pragma once
#include "GameState.h"
#include "Spritesheet.h"
#include "Animation.h"
#include "Player.h"
#include "Terrain.h"
#include "InputManager.h"
#include "GUI.h"
#include "Farm.h"
#include "Enemy.h"
#include "PowerUp.h"
//#include <SDL_mixer.h>

class GameplayState :
	public GameState
{
public:
	int* currentState;

	Spritesheet playerSheet;
	Player player;

	Spritesheet gunSheet;

	Spritesheet terrainSheet;
	Terrain terrain;

	Spritesheet farmSheet;
	Farm farm;

	Spritesheet enemySheet;
	std::vector<Enemy> enemies;
	int maxEnemies;
	int enemySpawnThreshold;

	Spritesheet bulletSheet;
	std::vector<Bullet> bullets;

	Spritesheet powerupSheet;
	std::vector<PowerUp> powerups;

	InputManager inputM;

	GUI gui;

	//Mix_Music* music = NULL;

	bool init(int* cS, Renderer* r, Camera* c);
	bool close();

	void pause();
	void resume();

	void input(SDL_Event* event);
	void update();
	void render();

};

