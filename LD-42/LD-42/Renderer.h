#pragma once
#include "Camera.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <iostream>
#include "Utility.h"

#define SMALL 0
#define MEDIUM 1
#define LARGE 2
#define X_LARGE 3

class Renderer
{
public:
	SDL_Renderer* renderer;
	
	TTF_Font* textFont[4];

	bool init(SDL_Window* window);

	SDL_Renderer* get_SDL_Renderer();

	SDL_Texture* textTexture;

	void renderSDLTextureOnScreen(SDL_Texture* renderTexture, int x, int y, int w, int h, SDL_Rect* clip = NULL, double rot = 0.0, SDL_Point* center = NULL, int scale = 1, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void renderSDLTexture(SDL_Texture* renderTexture, Camera* c, int x, int y, int w, int h, SDL_Rect* clip = NULL, double rot = 0.0, SDL_Point* center = NULL, int scale = 1, SDL_RendererFlip flip = SDL_FLIP_NONE, Uint8 r = 255, Uint8 g = 255, Uint8 b = 255);
	void setLogicalResolution(int width, int height);
	void renderSDLRectangle(Camera* c, int x, int y, int w, int h, SDL_Color col = {0, 0, 0, 255});
	void renderSDLRectangleOnScreen(int x, int y, int w, int h, SDL_Color col = { 0, 0, 0, 255 });
	void renderText(std::string text, int ID_Size, int x, int y, int w = NULL, int h = NULL, SDL_Color c = {0, 0, 0, 255});
	void close();
};

