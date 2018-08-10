#include "GameOver.h"

bool GameOver::init(int * cS, Renderer * r, Camera * c)
{
	currentState = cS;
	renderer = r;
	camera = c;

	gameOver = loadTexture("./res/GameOver.png", renderer->get_SDL_Renderer());

	inputTimer.initTimer(0, false);
	inputTimer.startTimer();

	return true;
}

void GameOver::input(SDL_Event * event)
{
	if (inputTimer.isTimerDone())
	{
		if (event->type == SDL_KEYDOWN)
		{
			SDL_Delay(1000);
			init(currentState, renderer, camera);
			*currentState = 0;
		}
	}
}

void GameOver::update()
{
	inputTimer.checkTimer();
}

void GameOver::render()
{
	renderer->renderSDLTextureOnScreen(gameOver, 0, 0, camera->getScreenWidth(), camera->getScreenHeight());
}
