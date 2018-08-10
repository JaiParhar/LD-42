#include "Enemy.h"

bool Enemy::init(int X, int Y, int W, int H, int cW, int cH, double rotation)
{
	x = X;
	y = Y;
	w = W;
	h = H;
	collisionWidth = cW;
	collisionHeight = cH;

	threshold = 20;

	removeTimeMS = 1000;
	dyingTimer.initTimer(1000);

	walkSpeed[FARM_ATTACKER] = 0.25;
	walkSpeed[PLAYER_ATTACKER] = 0.75;

	damage[FARM_ATTACKER] = 5;
	damage[PLAYER_ATTACKER] = 10;

	hp[FARM_ATTACKER] = 5;
	hp[PLAYER_ATTACKER] = 5;

	walkAnimation[FARM_ATTACKER].init(1000/2);
	walkAnimation[PLAYER_ATTACKER].init(1000/4);

	deathAnimation[FARM_ATTACKER].init(100);
	deathAnimation[PLAYER_ATTACKER].init(100);

	walkAnimation[PLAYER_ATTACKER].addFrame(0);
	walkAnimation[PLAYER_ATTACKER].addFrame(1);
	walkAnimation[PLAYER_ATTACKER].addFrame(2);

	deathAnimation[PLAYER_ATTACKER].addFrame(3);
	deathAnimation[PLAYER_ATTACKER].addFrame(4);
	deathAnimation[PLAYER_ATTACKER].addFrame(5);

	walkAnimation[FARM_ATTACKER].addFrame(6);
	walkAnimation[FARM_ATTACKER].addFrame(7);
	walkAnimation[FARM_ATTACKER].addFrame(8);
	
	deathAnimation[FARM_ATTACKER].addFrame(9);
	deathAnimation[FARM_ATTACKER].addFrame(10);
	deathAnimation[FARM_ATTACKER].addFrame(11);

	return true;
}

void Enemy::update()
{
	checkDeath();
	dyingTimer.checkTimer();
	if (!dying)
	{
		x += xvel;
		y += yvel;
		walkAnimation[enemyID].update();
	}
	else
	{
		deathAnimation[enemyID].updateIndividualAnimation(false);
	}

	if (dyingTimer.isTimerDone())
	{
		dead = true;
	}
}

void Enemy::moveToward(int X, int Y)
{
	int dx = X - getCenterX();
	int dy = Y - getCenterY();

	double angle = atan2(dy, dx);

	if (abs(dy) < threshold)
	{
		yvel = 0;
	}
	else
	{
		yvel = walkSpeed[enemyID] * (sin(angle));
	}

	if (abs(dx) < threshold)
	{
		xvel = 0;
	}
	else
	{
		xvel = walkSpeed[enemyID] * (cos(angle));
	}

	if (xvel > 0)
	{
		flip = SDL_FLIP_HORIZONTAL;
	}
	else 
	{
		flip = SDL_FLIP_NONE;
	}
}

void Enemy::checkDeath()
{
	if (hp[enemyID] <= 0 && !dying)
	{
		dying = true;
		dyingTimer.startTimer();
	}
}

void Enemy::setID(int ID)
{
	enemyID = ID;
}

Animation* Enemy::getCurrentAnimation()
{
	if (dying)
	{
		return &deathAnimation[enemyID];
	}
	return &walkAnimation[enemyID];
}

void Enemy::close()
{
}
