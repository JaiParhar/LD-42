#pragma once
#include <iostream>
#include <String>
#include <Vector>
#include <fstream>
#include "Renderer.h"
#include <SDL.h>
#include "Utility.h"

class Spritesheet
{
public:
	Spritesheet();

	SDL_Texture* spritesheet;
	SDL_Texture* getSpritesheet();
	bool loadSpritesheet(std::string fp, std::string IDp, Renderer* r);
	SDL_Rect* getSprite(int ID);

	std::vector<SDL_Rect> sprites;

	~Spritesheet();

private:
	void loadSpritesID(std::string IDp);
	int numberOfSprites;
};

