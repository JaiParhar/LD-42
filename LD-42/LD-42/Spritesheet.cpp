#include "Spritesheet.h"

Spritesheet::Spritesheet()
{
	
}

SDL_Texture* Spritesheet::getSpritesheet() 
{
	return spritesheet;
}

bool Spritesheet::loadSpritesheet(std::string fp, std::string IDp, Renderer* r)
{
	spritesheet = loadTexture(fp, r->get_SDL_Renderer());
	printf("Spritesheet has been loaded.\n");
	loadSpritesID(IDp);
	return true;
}

SDL_Rect* Spritesheet::getSprite(int ID)
{
	if (ID >= numberOfSprites || ID < 0)
	{
		printf("Error: Sprite %d does not exist. NULL will be returned instead.\n", ID);
		return NULL;
	}
	return &sprites.at(ID);
}

void Spritesheet::loadSpritesID(std::string IDp)
{
	numberOfSprites = 0;
	std::ifstream spriteIDFile(IDp);
	while(!spriteIDFile.eof())
	{
		SDL_Rect newRect;
		std::string dataLine;
		std::getline(spriteIDFile, dataLine);
		
		int x = std::stoi(parseLine(dataLine, "X="));
		int y = std::stoi(parseLine(dataLine, "Y="));
		int w = std::stoi(parseLine(dataLine, "W="));
		int h = std::stoi(parseLine(dataLine, "H="));

		SDL_Rect spriteRect = {x, y, w, h};

		sprites.push_back(spriteRect);
		numberOfSprites++;
	}
	printf("Number of Sprites: %d\n", numberOfSprites);
}

Spritesheet::~Spritesheet()
{
	SDL_DestroyTexture(spritesheet);
}
