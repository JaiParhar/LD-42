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

	void init(int X, int Y, Animation * a, Animation * cA, bool col, void(*f)(SpecialTile *tile, bool first), int i);
	void update();

	void setConditon(bool c);
	
	Animation* getAnimation();
	Animation* getCallbackAnimation();
};

