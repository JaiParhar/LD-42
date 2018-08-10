#pragma once
#include <SDL.h>
#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include "Utility.h"

#define NULL_TILE -1
#define GRASS 0

class Terrain
{
public:

	SDL_Surface* map;
	int* tileMap;
	int width, height;
	int tileWidth = 64;
	int tileHeight = 64;

	bool init(std::string fPath);
	void loadTileMap();
	int* getTileMap();
	int getTileWidth();
	int getTileHeight();
	int getWidth();
	int getHeight();
};

