#include "SpecialTile.h"

void SpecialTile::initCallback(Animation* cA, void(*f)(SpecialTile* tile, bool first))
{
	callbackAnimation = cA;
	callback = f;
	condition = false;
	changedLastTick = false;
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