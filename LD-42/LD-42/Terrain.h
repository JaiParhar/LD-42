#pragma once
#include <SDL.h>
#include <iostream>
#include <fstream>
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

	Tile** tileMap;
	int width, height;

	bool init(std::string fPath);
	Tile** getTileMap();
	Tile* getTile(int x, int y);
	int getWidth();
	int getHeight();
	void updateArea(int x, int y, int w, int h);

private:
	void loadTileMap(std::string fPath);
};

