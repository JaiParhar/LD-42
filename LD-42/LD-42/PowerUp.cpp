#include "PowerUp.h"

bool PowerUp::init(int X, int Y, int W, int H, int cW, int cH, double rotation)
{
	x = X;
	y = Y;
	w = W;
	h = H;
	collisionWidth = cW;
	collisionHeight = cH;

	numItems = 4 + 2;

	id = rand() % numItems;
	//0-3
	printf("ID=%d\n", id);
	if (id <= 3)
	{
		type = FOOD;
	}
	else
	{
		type = AMMO;
	}
	
	return true;
}
