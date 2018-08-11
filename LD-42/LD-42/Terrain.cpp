#include "Terrain.h"

bool Terrain::init(std::string fPath)
{
	map = loadSurface(fPath);
	width = map->w;
	height = map->h;
	loadTileMap();
	return true;
}

void Terrain::loadTileMap()
{
	const static int W = width;
	const static int H = height;

	tileMap = new Tile*[W*H];

	for (int i = 0; i < height*width; i++)
	{
		int y = floor(i / width);
		int x = i % width;

		if (getPixelColor(map, x, y).r == 0 && getPixelColor(map, x, y).g == 255 && getPixelColor(map, x, y).b == 0)
		{
			tileMap[i] = new Tile;
			Animation* a = new Animation;
			a->init(1000);
			a->addFrame(0);
			a->addFrame(2);
			tileMap[i]->init(x, y, a, false, FLOOR_TILE);
		}
		else
		{
			tileMap[i] = new Tile;
			Animation* a = new Animation;
			a->init(10000);
			a->addFrame(1);
			tileMap[i]->init(x, y, a, true, NULL_TILE);
		}
	}
}

Tile** Terrain::getTileMap()
{
	return tileMap;
}

Tile* Terrain::getTile(int x, int y)
{
	return tileMap[(y*width) + x];
}

int Terrain::getWidth()
{
	return width;
}

int Terrain::getHeight()
{
	return height;
}

void Terrain::updateArea(int x, int y, int w, int h)
{
	for (int Y = y; Y < y + h; Y++) {
		for (int X = x; X < x + w; X++) {
			tileMap[(Y*width) + X]->update();
		}
	}
}
