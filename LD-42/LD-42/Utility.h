#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include <stdio.h>
#include <String>

#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3

#define TILESIZE 64

static SDL_Texture* T;

SDL_Texture* loadTexture(std::string path, SDL_Renderer* r);
SDL_Texture* loadTextureFromString(std::string text, TTF_Font* font, SDL_Renderer* r, SDL_Color c = {0, 0, 0, 255}, int* w = NULL, int* h = NULL);
SDL_Surface* loadSurface(std::string path);
Uint32 get_pixel32(SDL_Surface *surface, int x, int y);
SDL_Color getPixelColor(SDL_Surface* img, int x, int y);
std::string parseLine(std::string line, std::string getData);
std::string parseBracketData(std::string line, int num);
std::string splitString(std::string s, std::string delimiter, int iteration, int size);