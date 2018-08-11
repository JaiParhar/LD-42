#pragma once
#include <SDL.h>
#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include "Utility.h"
#include "Tile.h"

#define NULL_TILE -1
#define GRASS_TILE 0

class Terrain
{
public:

	SDL_Surface* map;
	Tile** tileMap;
	int width, height;

	bool init(std::string fPath);
	void loadTileMap();
	Tile** getTileMap();
	Tile* getTile(int x, int y);
	int getWidth();
	int getHeight();
	void updateArea(int x, int y, int w, int h);
};

