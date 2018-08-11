#include "Utility.h"

SDL_Texture* loadTexture(std::string path, SDL_Renderer* r) 
{
	SDL_Texture* texture = NULL; 
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() ); 
	if( loadedSurface == NULL ) 
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	} 
	else
	{
		texture = SDL_CreateTextureFromSurface(r, loadedSurface); 
		if( texture == NULL ) 
		{ 
			printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() ); 
		} 
		SDL_FreeSurface( loadedSurface ); 
	} 
	return texture;
}

SDL_Texture* loadTextureFromString(std::string text, TTF_Font* font,SDL_Renderer* r, SDL_Color c, int* w, int* h)
{
	SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), c);
	if (textSurface == NULL) 
	{
		printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
	}
	else
	{
		if (w != nullptr)
		{
			*w = textSurface->w;
		}
		if (h != nullptr)
		{
			*h = textSurface->h;
		}

		T = SDL_CreateTextureFromSurface(r, textSurface);
		if (T == NULL)
		{
			printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
		}

		SDL_FreeSurface(textSurface);
		return T;
	}
	SDL_FreeSurface(textSurface);
	return NULL;
}

SDL_Surface* loadSurface(std::string path)
{
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	return loadedSurface;
}

SDL_Color getPixelColor(SDL_Surface* img, int x, int y)
{
	Uint8 r, g, b, a;
	SDL_GetRGBA(get_pixel32(img, x, y), img->format, &r, &g, &b, &a);
	SDL_Color pixelColor;
	pixelColor.r = r;
	pixelColor.g = g;
	pixelColor.b = b;
	pixelColor.a = a;
	return pixelColor;
}

Uint32 get_pixel32(SDL_Surface *surface, int x, int y)
{
	Uint32 *pixels = (Uint32 *)surface->pixels;
	return pixels[(y * surface->w) + x];
}

std::string parseLine(std::string line, std::string getData)
{
	int dataPos = line.find(getData);
	line = line.substr(dataPos);
	
	int endDataPos = line.find(" ");
	if (endDataPos != std::string::npos)
	{
		line.erase(endDataPos, -1);
	}

	line.erase(0, getData.length());

	return line;
}

std::string parseBracketData(std::string line, int num)
{
	//012345
	//1,2,3,
	line.erase(0, 1);
	line.replace(line.length()-1, 1, ",");
	int cPos;
	for (int i = 0; i < num; i++)
	{
		cPos = line.find(",");
		line.erase(0, cPos+1);
	}

	cPos = line.find(",");
	line.erase(cPos);
	return line;
}

std::string splitString(std::string s, std::string delimiter, int iteration, int size)
{
	size_t pos = 0;
	std::string token;
	for (int i = 0; i <= iteration; i++) 
	{
		if ((pos = s.find(delimiter)) != std::string::npos) {
			token = s.substr(0, pos);
			s.erase(0, pos + delimiter.length());
		}
	}
	if (iteration == size-1) { return s; }
	return token;
}
