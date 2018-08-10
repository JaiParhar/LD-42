#include "Terrain.h"

bool Terrain::init(std::string fPath)
{
	map = loadSurface(fPath);
	width = map->w;
	height = map->h;
	tileWidth = 64;
	tileHeight = 64;
	loadTileMap();
	return true;
}

void Terrain::loadTileMap()
{
	const static int W = width;
	const static int H = height;

	tileMap = new int[W*H];

	for (int i = 0; i < height*width; i++)
	{
		int y = floor(i / width);
		int x = i % width;

		//printf("%d %d %d %d %d\n", x, y, getPixelColor(map, x, y).r, getPixelColor(map, x, y).g, getPixelColor(map, x, y).b);
		if (getPixelColor(map, x, y).r == 0 && getPixelColor(map, x, y).g == 255 && getPixelColor(map, x, y).b == 0)
		{
			tileMap[i] = GRASS;
		}
		else
		{
			tileMap[i] = NULL_TILE;
		}
	}
}

int* Terrain::getTileMap()
{
	return tileMap;
}

int Terrain::getTileWidth()
{
	return tileWidth;
}

int Terrain::getTileHeight()
{
	return tileHeight;
}

int Terrain::getWidth()
{
	return width;
}

int Terrain::getHeight()
{
	return height;
}