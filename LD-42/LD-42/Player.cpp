#include "Player.h"

bool Player::init(int X, int Y, int W, int H, int cW, int cH, double rotation)
{
	x = X;
	y = Y;
	w = W;
	h = H;
	collisionWidth = cW;
	collisionHeight = cH;

	baseWalkSpeed = 3.5;
	walkSpeedMod = 0.25;

	fatLevel = 0;

	initAnimations();

	hp = 100;
	maxHP = 100;
	HPMod = 10;

	gun.init(x, y, w, h, collisionWidth, collisionHeight);
	gunTimer.initTimer(gun.getFireRate(), true);
	gunTimer.startTimer();

	isReloading = false;

	reloadTimer.initTimer(gun.getGunReloadTime(), true);

	damageColorTimer.initTimer(250, true);

	return true;
}

bool Player::initAnimations()
{
	fatAnimation = 0;
	for (int i = 0; i < (numFatLevelAnimations); i+=1)
	{
		int walkCycleAnimationSpeed = 100 + (i*walkAnimationSpeedMod);

		walkCycles[i][UP].init(walkCycleAnimationSpeed);
		walkCycles[i][DOWN].init(walkCycleAnimationSpeed);
		walkCycles[i][SIDE].init(walkCycleAnimationSpeed);

		int frameMod = 9*i;

		walkCycles[i][DOWN].addFrame(0 + frameMod);
		walkCycles[i][DOWN].addFrame(1 + frameMod);
		walkCycles[i][DOWN].addFrame(2 + frameMod);
		walkCycles[i][DOWN].addFrame(1 + frameMod);

		walkCycles[i][UP].addFrame(3 + frameMod);
		walkCycles[i][UP].addFrame(4 + frameMod);
		walkCycles[i][UP].addFrame(5 + frameMod);
		walkCycles[i][UP].addFrame(4 + frameMod);

		walkCycles[i][SIDE].addFrame(6 + frameMod);
		walkCycles[i][SIDE].addFrame(7 + frameMod);
		walkCycles[i][SIDE].addFrame(8 + frameMod);
		walkCycles[i][SIDE].addFrame(7 + frameMod);
	}

	return true;
}

void Player::update()
{

	distanceWalked += abs(xvel);
	distanceWalked += abs(yvel);

	if (distanceWalked >= loseWeightDistance && fatLevel > 0)
	{
		loseWeightLevel(1);
		distanceWalked = 0;
	}

	//Will be pos if above or to the left of
	int diffX = farm->getX() - getX();
	int diffY = farm->getY() - getY();
	if ((diffX > 0 && xvel > 0) || (diffX < 0 && xvel < 0))
	{
		if (!checkCollision(farm, xvel, 0))
		{
			x += xvel;
		}
	}
	else 
	{
		x += xvel;
	}
	if ((diffY > 0 && yvel > 0) || (diffY < 0 && yvel < 0))
	{
		if (!checkCollision(farm, 0, yvel))
		{
			y += yvel;
		}
	}
	else
	{
		y += yvel;
	}

	fatAnimation = fatLevel / fatTrigger;
	if (fatAnimation > numFatLevelAnimations - 1)
	{
		fatAnimation = numFatLevelAnimations - 1;
	}

	switch (direction)
	{
	case UP:
		flip = SDL_FLIP_NONE;
		break;
		
	case DOWN:
		flip = SDL_FLIP_NONE;
		break;

	case LEFT:
		flip = SDL_FLIP_HORIZONTAL;
		break;

	case RIGHT:
		flip = SDL_FLIP_NONE;
		break;
	}

	if (moving)
	{
		getCurrentAnimation()->update();
	}

	if (yvel == 0 && xvel == 0)
	{
		moving = false;
	}

	gun.setDirection(direction);
	gun.update();
	gun.setGunPos(x, y);
	gun.setFlip(flip);
	gunTimer.setEndTime(gun.getFireRate());
	gunTimer.checkTimer();

	if (gun.getCurrGunMag() == 0 && gun.getGunAmmo() > 0 && !isReloading)
	{
		printf("Began Reload\n");
		reload();
	}

	if (reloadTimer.isTimerDone())
	{
		printf("End Reload\n");
		isReloading = false;
		gun.reload();
		reloadTimer.timerReset();
	}

	reloadTimer.setEndTime(gun.getGunReloadTime());
	reloadTimer.checkTimer();

	if (gun.getGunAmmo() <= 0 && gun.getCurrGunMag() <= 0)
	{
		gun.setGun(gun.currentGunID-1);
	}

	damageColorTimer.checkTimer();
}

void Player::move(int dir)
{
	moving = true;
	if (!shooting)
	{
		direction = dir;
	}

	if (dir == UP)
	{
		yvel = -(baseWalkSpeed/((fatLevel*walkSpeedMod)+1));
	}

	if (dir == DOWN)
	{
		yvel = (baseWalkSpeed / ((fatLevel*walkSpeedMod)+1));
	}

	if (dir == LEFT)
	{
		xvel = -(baseWalkSpeed / ((fatLevel*walkSpeedMod)+1));
	}

	if (dir == RIGHT)
	{
		xvel = (baseWalkSpeed / ((fatLevel*walkSpeedMod)+1));
	}
}

void Player::stopMovingX()
{
	xvel = 0;
}

void Player::stopMovingY()
{
	yvel = 0;
}

void Player::startShooting(int dir) 
{
	shooting = true;
	direction = dir;
}

std::vector<Bullet> Player::shoot()
{
	std::vector<Bullet> bullets;
	if (gunTimer.isTimerDone() && !isReloading)
	{
		gun.shoot();
		for (int i = 0; i < gun.getNumPellets(); i++)
		{
			Bullet bullet;
			bullet.setBulletID(gun.getBulletID());
			bullet.init(getCenterX(), getCenterY() - (16), 16, 16/4, 16, 16/4);
			double spread = 0;
			if (gun.getSpread() != 0) 
			{
				spread = (rand() % (int)gun.getSpread()) / 2;
			}

			if (rand() % 2)
			{
				spread *= -1;
			}

			double angle = 0;

			switch (direction)
			{
			case UP:
				angle = -90 + spread;
				break;

			case DOWN:
				angle = 90 + spread;
				break;

			case LEFT:
				angle = 180 + spread;
				break;

			case RIGHT:
				angle = 0 + spread;
				break;
			}

			bullet.setAngle(angle);

			bullet.setXVel(bullet.getBulletSpeed() * (cos(angle*M_PI / 180)));
			bullet.setYVel(bullet.getBulletSpeed() * (sin(angle*M_PI / 180)));
			bullets.push_back(bullet);
		}

		gun.runAnimation();
		gunTimer.timerReset();
		gunTimer.startTimer();
	}
	return bullets;
}

bool Player::isShooting()
{
	return shooting;
}

void Player::stopShooting()
{
	shooting = false;
}

void Player::reload()
{
	if (gun.getGunAmmo() > 0)
	{
		if (gun.getCurrGunMag() < gun.getGunMagSize())
		{
			reloadTimer.startTimer();
			isReloading = true;
		}
	}
}

void Player::subtractHP(int h)
{
	hp -= h;
	damageColorTimer.timerReset();
	damageColorTimer.startTimer();
	if (hp < 0)
	{
		hp = 0;
	}
}

int Player::getHP()
{
	return hp;
}

int Player::getMaxHP()
{
	return maxHP;
}

Animation* Player::getCurrentAnimation()
{
	if (direction == RIGHT)
	{
		return &walkCycles[fatAnimation][SIDE];
	}
	return &walkCycles[fatAnimation][direction];
}

void Player::setFarm(Farm* f)
{
	farm = f;
}

bool Player::shoudDamageColor()
{
	return !damageColorTimer.isTimerDone();
}

void Player::close() 
{
}

Gun* Player::getPlayerGun()
{
	return &gun;
}

void Player::setPlayerGun(int id)
{
	if (gunTimer.isTimerDone() && !isReloading)
	{
		gun.setGun(id);
	}
}

void Player::loseWeightLevel(int levels)
{
	fatLevel -= levels;
	double percentHP = hp / (double)maxHP;
	maxHP = 100 + (fatLevel * HPMod);
	hp = maxHP * percentHP;
}

void Player::addFatLevel(int levels)
{
	fatLevel += levels;
	double percentHP = hp / (double)maxHP;
	maxHP = 100 + (fatLevel * HPMod);
	hp = maxHP * percentHP;
}

void Player::addHP(int h)
{
	if (hp >= maxHP)
	{
		addFatLevel(2);
	}
	else if(hp+h >= maxHP)
	{
		hp = maxHP;
	}
	else 
	{
		hp += h;
	}
}

bool Player::getIsReloading()
{
	return isReloading;
}

int Player::getDirection()
{
	return direction;
}

void Player::resetDistance()
{
	distanceWalked = 0;
}
