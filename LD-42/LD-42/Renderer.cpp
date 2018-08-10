#include "Renderer.h"

Renderer::~Renderer()
{

}

Renderer::Renderer()
{

}

bool Renderer::init(SDL_Window* window) 
{
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == NULL)
	{
		printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
		return false;
	}
	else 
	{
		SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
		if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
		{
			printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
			return false;
		}
		if (TTF_Init() == -1) 
		{
			printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
		}

		textFont[SMALL] = TTF_OpenFont("./res/pixelFont.ttf", 16);
		textFont[MEDIUM] = TTF_OpenFont("./res/pixelFont.ttf", 32);
		textFont[LARGE] = TTF_OpenFont("./res/pixelFont.ttf", 64);
		textFont[X_LARGE] = TTF_OpenFont("./res/pixelFont.ttf", 128);
	}
	return true;
}

void Renderer::renderSDLTextureOnScreen(SDL_Texture* renderTexture, int x, int y, int w, int h, SDL_Rect* clip, double rot, SDL_Point* center, int scale, SDL_RendererFlip flip)
{
	w *= scale;
	h *= scale;

	SDL_Rect dstRect = { x, y, w, h };

	SDL_RenderCopyEx(renderer, renderTexture, clip, &dstRect, rot, center, flip);
}

void Renderer::renderSDLTexture(SDL_Texture* renderTexture, Camera* c, int x, int y, int w, int h, SDL_Rect* clip, double rot, SDL_Point* center, int scale, SDL_RendererFlip flip, Uint8 r, Uint8 g, Uint8 b)
{
	x -= (c->getX());
	y -= (c->getY());

	w *= scale;
	h *= scale;

	if ((x < c->screenWidth) || (x + w > 0) || (y < c->screenHeight) && (y + h > 0))
	{
		SDL_Rect dstRect = { x, y, w, h };
		SDL_SetTextureColorMod(renderTexture, r, g, b);
		SDL_RenderCopyEx(renderer, renderTexture, clip, &dstRect, rot, center, flip);
	}
}

void Renderer::setLogicalResolution(int width, int height)
{
	SDL_RenderSetLogicalSize(renderer, width, height);
}

void Renderer::renderSDLRectangle(int x, int y, int w, int h, SDL_Color c)
{
	SDL_Rect renderRect = { x,y,w,h };
	SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, c.a);
	SDL_RenderFillRect(renderer, &renderRect);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
}

void Renderer::renderText(std::string text, int ID_Size, int x, int y, int w, int h, SDL_Color c)
{
	if (w == NULL && h == NULL)
	{
		textTexture = loadTextureFromString(text, textFont[ID_Size], renderer, c, &w, &h);
	}
	else if (w == NULL && h != NULL || w != NULL && h == NULL)
	{
		printf("You set either w or h only... don't do that...");
		textTexture = loadTextureFromString(text, textFont[ID_Size], renderer, c);
	}
	else 
	{
		textTexture = loadTextureFromString(text, textFont[ID_Size], renderer, c);
	}

	renderSDLTextureOnScreen(textTexture, x, y, w, h);
	SDL_DestroyTexture(textTexture);
}

SDL_Renderer* Renderer::get_SDL_Renderer()
{
	return renderer;
}