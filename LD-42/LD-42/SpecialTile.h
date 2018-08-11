#pragma once
#include "Tile.h"
class SpecialTile :
	public Tile
{
public:
	bool condition;
	bool changedLastTick;

	Animation* callbackAnimation;
	void(*callback)(SpecialTile* tile, bool first);

	void initCallback(Animation * cA, void(*f)(SpecialTile *tile, bool first));
	void update();

	void setConditon(bool c);
	
	Animation* getAnimation();
	Animation* getCallbackAnimation();
};

