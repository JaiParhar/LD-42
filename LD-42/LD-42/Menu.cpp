#include "Menu.h"

bool Menu::init(int * cS, Renderer * r, Camera * c)
{
	currentState = cS;
	renderer = r;
	camera = c;

	mainMenu = loadTexture("./res/MenuScreen.png", renderer->get_SDL_Renderer());

	inputTimer.initTimer(0, false);
	inputTimer.timerReset();
	inputTimer.startTimer();

	return true;
}

void Menu::input(SDL_Event * event)
{
	if (inputTimer.isTimerDone())
	{
		if (event->type == SDL_KEYDOWN)
		{
			SDL_Delay(1000);
			init(currentState, renderer, camera);
			*currentState = 1;
		}
	}
}

void Menu::update()
{
	inputTimer.checkTimer();
}

void Menu::render()
{
	renderer->renderSDLTextureOnScreen(mainMenu, 0, 0, camera->getScreenWidth(), camera->getScreenHeight());
}
