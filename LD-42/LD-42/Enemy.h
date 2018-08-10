#pragma once
#include "Entity.h"
#include "Animation.h"
#include "Timer.h"

#define FARM_ATTACKER 0
#define PLAYER_ATTACKER 1

class Enemy
	: public Entity
{
public:
	int enemyID;
	const static int numberOfEnemies = 2;
	double walkSpeed[numberOfEnemies];
	int damage[numberOfEnemies];
	int hp[numberOfEnemies];

	int removeTimeMS;
	Timer dyingTimer;

	bool dying = false;
	bool dead = false;

	int threshold;

	Animation walkAnimation[numberOfEnemies];
	Animation deathAnimation[numberOfEnemies];

	bool init(int X, int Y, int W, int H, int cW, int cH, double rotation = 0.0);
	void update();
	void moveToward(int x, int y);
	void checkDeath();
	void setID(int ID);
	Animation * getCurrentAnimation();
	void setHP(int h) { hp[enemyID] = h; }
	bool isDead() { return dead; }
	bool isDying() { return dying; }
	void close();
};

