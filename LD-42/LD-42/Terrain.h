#pragma once
#include <SDL.h>
#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include "Utility.h"
#include "Tile.h"
#include "SpecialTile.h"

#define NULL_TILE 0
#define FLOOR_TILE 1
#define R_WALL_TILE 2

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

