#pragma once
#include <SDL.h>
#include <stdio.h>
#include <iostream>
#include "Utility.h"
#include "Renderer.h"

class GUI
{
public:
	int screenW;
	int screenH;

	int healthBarSize;
	SDL_Rect hBar;
	SDL_Rect baseHBar;
	SDL_Rect outline;
	double outlineThickness;
	SDL_Color hBarColor;
	SDL_Color baseHBarColor;

	std::string healthText;
	std::string helperText;
	std::string farmHP;
	std::string ammoText;
	std::string fatLevelText;

	bool init(int sW, int sH, Renderer* r);
	void setHBar(int hp, int maxHP);
	SDL_Rect getHBar();
	SDL_Rect getBaseHBar();
	SDL_Rect getHPOutline();
	SDL_Color getHBarColor();
	SDL_Color getBaseHBarColor();
	void setAmmoText(int mag, int ammo);
	void setHelperText(std::string t);
	void setFarmHPText(int farmHP);
	std::string getHealthText();
	std::string getHelperText();
	std::string getFarmHPText();
	std::string getAmmoText();
};

