#include "InputManager.h"

bool InputManager::init()
{
	for (int i = 0; i < numKeys; i++)
	{
		keyPressed[i] = false;
	}
	return true;
}

void InputManager::input(SDL_Event * event)
{
	if (event->type == SDL_KEYDOWN)
	{
		if (event->key.keysym.sym == SDLK_w)
		{
			keyPressed[K_W] = true;
		}

		if (event->key.keysym.sym == SDLK_s)
		{
			keyPressed[K_S] = true;
		}

		if (event->key.keysym.sym == SDLK_a)
		{
			keyPressed[K_A] = true;
		}

		if (event->key.keysym.sym == SDLK_d)
		{
			keyPressed[K_D] = true;
		}

		if (event->key.keysym.sym == SDLK_r)
		{
			keyPressed[K_R] = true;
		}

		if (event->key.keysym.sym == SDLK_UP)
		{
			keyPressed[K_UP] = true;
		}

		if (event->key.keysym.sym == SDLK_DOWN)
		{
			keyPressed[K_DOWN] = true;
		}

		if (event->key.keysym.sym == SDLK_LEFT)
		{
			keyPressed[K_LEFT] = true;
		}

		if (event->key.keysym.sym == SDLK_RIGHT)
		{
			keyPressed[K_RIGHT] = true;
		}

		if (event->key.keysym.sym == SDLK_1) 
		{
			keyPressed[K_1] = true;
		}

		if (event->key.keysym.sym == SDLK_2)
		{
			keyPressed[K_2] = true;
		}

		if (event->key.keysym.sym == SDLK_3)
		{
			keyPressed[K_3] = true;
		}

		if(event->key.keysym.sym == SDLK_4)
		{
			keyPressed[K_4] = true;
		}
		
		if (event->key.keysym.sym == SDLK_5)
		{
			keyPressed[K_5] = true;
		}

		if (event->key.keysym.sym == SDLK_6)
		{
			keyPressed[K_6] = true;
		}

		if (event->key.keysym.sym == SDLK_7)
		{
			keyPressed[K_7] = true;
		}

		if (event->key.keysym.sym == SDLK_8)
		{
			keyPressed[K_8] = true;
		}

		if (event->key.keysym.sym == SDLK_9)
		{
			keyPressed[K_9] = true;
		}

		if (event->key.keysym.sym == SDLK_0)
		{
			keyPressed[K_0] = true;
		}
	}

	if (event->type == SDL_KEYUP)
	{
		if (event->key.keysym.sym == SDLK_w)
		{
			keyPressed[K_W] = false;
		}

		if (event->key.keysym.sym == SDLK_s)
		{
			keyPressed[K_S] = false;
		}

		if (event->key.keysym.sym == SDLK_a)
		{
			keyPressed[K_A] = false;
		}

		if (event->key.keysym.sym == SDLK_d)
		{
			keyPressed[K_D] = false;
		}

		if (event->key.keysym.sym == SDLK_r)
		{
			keyPressed[K_R] = false;
		}

		if (event->key.keysym.sym == SDLK_UP)
		{
			keyPressed[K_UP] = false;
		}

		if (event->key.keysym.sym == SDLK_DOWN)
		{
			keyPressed[K_DOWN] = false;
		}

		if (event->key.keysym.sym == SDLK_LEFT)
		{
			keyPressed[K_LEFT] = false;
		}

		if (event->key.keysym.sym == SDLK_RIGHT)
		{
			keyPressed[K_RIGHT] = false;
		}

		if (event->key.keysym.sym == SDLK_1)
		{
			keyPressed[K_1] = false;
		}

		if (event->key.keysym.sym == SDLK_2)
		{
			keyPressed[K_2] = false;
		}

		if (event->key.keysym.sym == SDLK_3)
		{
			keyPressed[K_3] = false;
		}

		if (event->key.keysym.sym == SDLK_4)
		{
			keyPressed[K_4] = false;
		}

		if (event->key.keysym.sym == SDLK_5)
		{
			keyPressed[K_5] = false;
		}

		if (event->key.keysym.sym == SDLK_6)
		{
			keyPressed[K_6] = false;
		}

		if (event->key.keysym.sym == SDLK_7)
		{
			keyPressed[K_7] = false;
		}

		if (event->key.keysym.sym == SDLK_8)
		{
			keyPressed[K_8] = false;
		}

		if (event->key.keysym.sym == SDLK_9)
		{
			keyPressed[K_9] = false;
		}

		if (event->key.keysym.sym == SDLK_0)
		{
			keyPressed[K_0] = false;
		}
	}
}
