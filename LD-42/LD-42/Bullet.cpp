#include "Bullet.h"

void Bullet::loadBulletType(std::string fPath, int bulletID)
{
	std::ifstream bulletConfigFile(fPath);
	
	std::string dataLine;
	for (int i = 0; std::getline(bulletConfigFile, dataLine) && i <= bulletID; i++);
		
	bulletSpeed = std::stoi(parseLine(dataLine, "BulletSpeed="));
	bulletDamage = std::stoi(parseLine(dataLine, "Damage="));
	spriteID = std::stoi(parseLine(dataLine, "SpriteID="));
}

void Bullet::setBulletID(int bulletID)
{
	ID = bulletID;
}

bool Bullet::init(int X, int Y, int W, int H, int cW, int cH, double rotation)
{
	x = X;
	y = Y;
	w = W;
	h = H;
	collisionWidth = cW;
	collisionHeight = cH;
	rot = rotation;
	loadBulletType("./res/BulletData.txt", ID);
	return true;
}

void Bullet::update()
{
	x += xvel;
	y += yvel;
}

int Bullet::getBulletSpeed()
{
	return bulletSpeed;
}

int Bullet::getSpriteID()
{
	return spriteID;
}

void Bullet::close()
{
}