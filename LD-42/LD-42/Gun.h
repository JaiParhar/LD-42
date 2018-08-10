#pragma once
#include <iostream>
#include <String>
#include <Vector>
#include <fstream>
#include <SDL.h>
#include "Entity.h"
#include "Animation.h"
#include "Utility.h"

#define UP 0
#define DOWN 1
#define SIDE 2

class Gun:
	public Entity
{
public:
	int currentGunID;
	int numberOfGuns;

	int direction;

	std::vector<std::string> gunName;
	std::vector<std::vector<Animation>> gunAnimation;
	std::vector<int> gunFireRate;
	std::vector<double> gunRecoil;
	std::vector<int> bulletID;
	std::vector<int> numPellets;
	std::vector<double> spread;

	std::vector<int> gunMagSize;
	std::vector<int> gunReloadTime;

	std::vector<int> currGunMag;
	std::vector<int> gunAmmo;

	bool init(int X, int Y, int W, int H, int cW, int cH, double rotation = 0.0);
	void update();
	void runAnimation();
	int getGunID();
	void setGun(int ID);
	double getGunRecoil();
	Animation* getGunAnimation();
	void setGunPos(int X, int Y);
	void setFlip(int flip);
	int getFireRate();
	std::string getGunName();
	int getBulletID();
	int getNumPellets();
	double getSpread();
	void reload();
	void shoot();
	int getGunMagSize();
	int getCurrGunMag();
	int getGunReloadTime();
	int getGunAmmo();
	void addAmmo(int gunID, int ammo);
	void setDirection(int dir);
	void close();

private:
	void loadGunConfig(std::string fPath);
};

