#include "SpecialTile.h"

void SpecialTile::init(int X, int Y, Animation* a, Animation* cA , bool col, void(*f)(SpecialTile* tile, bool first), int i)
{
	x = X;
	y = Y;
	animation = a;
	callbackAnimation = cA;
	collidable = col;
	callback = f;
	condition = false;
	changedLastTick = false;
	ID = i;
}

void SpecialTile::update()
{
	if (!condition) 
	{
		animation->update();
	}
	else 
	{
		(*callback)(this, changedLastTick);
		if (changedLastTick)
		{
			changedLastTick = false;
			callbackAnimation->startIndividualAnimation();
		}
		callbackAnimation->updateIndividualAnimation();
	}
}

void SpecialTile::setConditon(bool c)
{
	condition = c;
	changedLastTick = true;
}

Animation* SpecialTile::getAnimation() 
{
	if (condition)
	{
		return callbackAnimation;
	}
	else
	{
		return animation;
	}
}

Animation* SpecialTile::getCallbackAnimation()
{
	return callbackAnimation;
}


//ADD CALLBACK STATEMENTS HERE
// |  |  |  |  |  |  |  |  |
// |  |  |  |  |  |  |  |  |
//\|/\|/\|/\|/\|/\|/\|/\|/\|/