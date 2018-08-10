#include "Gun.h"

void Gun::loadGunConfig(std::string fPath)
{
	numberOfGuns = 0;
	std::ifstream gunConfigFile(fPath);
	while (!gunConfigFile.eof())
	{
		std::string dataLine;
		std::getline(gunConfigFile, dataLine);
		
		gunName.push_back(parseLine(dataLine, "Name="));

		gunMagSize.push_back(std::stoi(parseLine(dataLine, "MagazineSize=")));
		gunReloadTime.push_back(std::stoi(parseLine(dataLine, "ReloadTime=")));

		currGunMag.push_back(0);
		
		if (parseLine(dataLine, "Name=") == "Pistol")
		{
			gunAmmo.push_back(999);
		}
		else
		{
			gunAmmo.push_back(0);
		}

		std::string frames[3];
		frames[UP] = parseLine(dataLine, "UPSpritesheetID=");
		frames[DOWN] = parseLine(dataLine, "DOWNSpritesheetID=");
		frames[SIDE] = parseLine(dataLine, "SIDESpritesheetID=");
		
		std::vector<Animation> currGunAnimation;
		Animation UPanimation;
		Animation DOWNanimation;
		Animation SIDEanimation;
		UPanimation.init(std::stoi(parseLine(dataLine, "AnimationSpeed=")), false);
		DOWNanimation.init(std::stoi(parseLine(dataLine, "AnimationSpeed=")), false);
		SIDEanimation.init(std::stoi(parseLine(dataLine, "AnimationSpeed=")), false);

		for (int i = 0; i < std::count(frames[UP].begin(), frames[UP].end(), ',') + 1; i++)
		{
			UPanimation.addFrame(std::stoi(parseBracketData(frames[UP], i)));
		}
		
		for (int i = 0; i < std::count(frames[DOWN].begin(), frames[DOWN].end(), ',') + 1; i++)
		{
			DOWNanimation.addFrame(std::stoi(parseBracketData(frames[DOWN], i)));
		}

		for (int i = 0; i < std::count(frames[SIDE].begin(), frames[SIDE].end(), ',') + 1; i++)
		{
			SIDEanimation.addFrame(std::stoi(parseBracketData(frames[SIDE], i)));
		}
		
		currGunAnimation.push_back(UPanimation);
		currGunAnimation.push_back(DOWNanimation);
		currGunAnimation.push_back(SIDEanimation);

		gunAnimation.push_back(currGunAnimation);

		gunFireRate.push_back(std::stoi(parseLine(dataLine, "GunFireRate=")));

		gunRecoil.push_back(std::stod(parseLine(dataLine, "GunRecoil=")));

		bulletID.push_back(std::stoi(parseLine(dataLine, "BulletID=")));

		numPellets.push_back(std::stoi(parseLine(dataLine, "Pellets=")));

		spread.push_back(std::stod(parseLine(dataLine, "Spread=")));

		numberOfGuns++;
	}
}

bool Gun::init(int X, int Y, int W, int H, int cW, int cH, double rotation)
{
	x = X;
	y = Y;
	w = W;
	h = H;
	collisionWidth = cW;
	collisionHeight = cH;
	rot = rotation;

	direction = 0;

	loadGunConfig("./res/GunData.txt");
	setGun(0);
	return true;
}

void Gun::update()
{
	gunAnimation.at(currentGunID).at(direction).updateIndividualAnimation();
}

void Gun::runAnimation()
{
	gunAnimation.at(currentGunID).at(direction).startIndividualAnimation();
}

int Gun::getGunID() 
{
	return currentGunID;
}

void Gun::setGun(int ID)
{
	currentGunID = ID;
}

void Gun::addAmmo(int gunID, int ammo)
{
	gunAmmo.at(gunID) += ammo;
}

double Gun::getGunRecoil()
{
	return gunRecoil.at(currentGunID);
}

Animation* Gun::getGunAnimation()
{
	return &gunAnimation.at(currentGunID).at(direction);
}

void Gun::setGunPos(int X, int Y)
{
	x = X;
	y = Y;
}

void Gun::setFlip(int f)
{
	flip = f;
}

int Gun::getFireRate()
{
	return gunFireRate.at(currentGunID);
}

std::string Gun::getGunName()
{
	return gunName.at(currentGunID);
}

int Gun::getBulletID()
{
	return bulletID.at(currentGunID);
}

int Gun::getNumPellets()
{
	return numPellets.at(currentGunID);
}

double Gun::getSpread()
{
	return spread.at(currentGunID);
}

void Gun::reload()
{
	if (gunAmmo.at(currentGunID) - gunMagSize.at(currentGunID) - currGunMag.at(currentGunID) > -1)
	{
		gunAmmo.at(currentGunID) -= gunMagSize.at(currentGunID) - currGunMag.at(currentGunID);
		currGunMag.at(currentGunID) = gunMagSize.at(currentGunID);
	}
	else
	{
		currGunMag.at(currentGunID) = gunAmmo.at(currentGunID);
		gunAmmo.at(currentGunID) = 0;
	}
	
}

void Gun::shoot()
{
	currGunMag.at(currentGunID)--;
}

int Gun::getGunMagSize()
{
	return gunMagSize.at(currentGunID);
}

int Gun::getCurrGunMag()
{
	return currGunMag.at(currentGunID);
}

int Gun::getGunReloadTime()
{
	return gunReloadTime.at(currentGunID);
}

int Gun::getGunAmmo()
{
	return gunAmmo.at(currentGunID);
}

void Gun::setDirection(int dir)
{
	direction = dir;
	if (direction == 2 || direction == 3)
	{
		direction = SIDE;
	}
}

void Gun::close()
{
}

