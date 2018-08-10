#include "GUI.h"

bool GUI::init(int sW, int sH, Renderer* r)
{
	screenW = sW;
	screenH = sH;

	healthBarSize = sW / 2;
	baseHBar = { sW / 4, sH - (sH / 8), healthBarSize, 50 };
	baseHBarColor = { 255, 0, 0, 255 };

	outlineThickness = sH / 96;
	outline = { baseHBar.x - (int)outlineThickness, baseHBar.y - (int)outlineThickness, baseHBar.w + (int)(2 * outlineThickness), baseHBar.h + (int)(2 * outlineThickness) };
	
	hBar = { baseHBar.x, baseHBar.y, healthBarSize, 50 };
	hBarColor = { 0, 255, 0, 255 };

	healthText = "";
	helperText = "";
	ammoText = "";

	return true;
}

void GUI::setHBar(int hp, int maxHP)
{
	double percentHP = hp / (double)maxHP;

	healthText = std::to_string(hp) + "/" + std::to_string(maxHP);

	hBar.w = (int)(baseHBar.w * percentHP);
	if (hBar.w < 0)
	{
		hBar.w = 0;
	}
}

SDL_Rect GUI::getHBar()
{
	return hBar;
}

SDL_Rect GUI::getBaseHBar()
{
	return baseHBar;
}

SDL_Rect GUI::getHPOutline()
{
	return outline;
}

SDL_Color GUI::getHBarColor()
{
	return hBarColor;
}

SDL_Color GUI::getBaseHBarColor()
{
	return baseHBarColor;
}

void GUI::setAmmoText(int mag, int ammo)
{
	ammoText = std::to_string(mag) + "/" + std::to_string(ammo);
}

void GUI::setHelperText(std::string t)
{
	helperText = t;
}

void GUI::setFarmHPText(int fHP)
{
	int percent = 100.0 - ((fHP / 100.0) * 100);
	farmHP = "Farm Damage: " + std::to_string(percent) + "%";
}

std::string GUI::getHealthText()
{
	return healthText;
}

std::string GUI::getHelperText()
{
	return helperText;
}

std::string GUI::getFarmHPText()
{
	return farmHP;
}

std::string GUI::getAmmoText()
{
	return ammoText;
}