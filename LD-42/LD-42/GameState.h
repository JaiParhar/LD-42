#pragma once
#include "Renderer.h"
#include "Camera.h"

class GameState
{
public:
	Camera* camera;
	Renderer* renderer;
	int* currentState;
	bool quit = false;

	virtual bool init(int* cS, Renderer* r, Camera* c) = 0;
	virtual bool close() = 0;

	virtual void pause() = 0;
	virtual void resume() = 0;

	virtual void input(SDL_Event* event) = 0;
	virtual void update() = 0;
	virtual void render() = 0;

	bool shouldQuit()
	{
		return quit;
	}

	void setQuit(bool q)
	{
		quit = q;
	}

};

