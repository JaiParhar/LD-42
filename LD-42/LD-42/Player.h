#pragma once
#include "Entity.h"
#include <Math.h>
#include "Gun.h"
#include "Timer.h"
#include "Bullet.h"
#include "Farm.h"

#define _USE_MATH_DEFINES
#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3

#define SIDE 2

class Player :
	public Entity
{
public:
	int fatLevel;
	int fatAnimation;
	const static int maxFatLevel = 10;
	const static int maxFatAnimationLevel = 8;
	const static int fatTrigger = 2;

	const static int walkAnimationSpeedMod = 1;

	const static int numFatLevelAnimations = maxFatAnimationLevel / fatTrigger;
	Animation walkCycles[numFatLevelAnimations][3];

	double walkSpeedMod;
	double baseWalkSpeed;
	int direction = 0;

	int distanceWalked;
	const static int loseWeightDistance = 500;

	bool shooting = false;
	bool moving = false;

	Gun gun;
	Timer gunTimer;
	Timer reloadTimer;
	bool isReloading;

	int hp;
	int maxHP;
	double HPMod;

	Farm* farm;

	Timer damageColorTimer;

	bool init(int X, int Y, int W, int H, int cW, int cH, double rotation = 0.0);
	bool initAnimations();
	void update();
	void move(int dir);
	void stopMovingX();
	void stopMovingY();
	void startShooting(int dir);
	std::vector<Bullet> shoot();
	bool isShooting();
	void stopShooting();
	void reload();
	Gun* getPlayerGun();
	void setPlayerGun(int id);
	void loseWeightLevel(int levels);
	void addFatLevel(int levels);
	void addHP(int h);
	bool getIsReloading();
	int getDirection();
	void resetDistance();
	void subtractHP(int h);
	int getHP();
	int getMaxHP();
	Animation* getCurrentAnimation();
	void setFarm(Farm* f);
	bool shoudDamageColor();
	void close();
};

