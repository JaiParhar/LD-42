#include "GameplayState.h"

//TODO
//ADD SCREEN TO SHOW CONTROLS
//IMPLEMENT MUSIC

bool GameplayState::init(int* cS, Renderer* r, Camera* c)
{
	currentState = cS;
	renderer = r;
	camera = c;

	playerSheet.loadSpritesheet("./res/PlayerSpritesheet.png",
		"./res/PlayerSpritesheetData.txt", renderer);
	
	terrainSheet.loadSpritesheet("./res/MapSpritesheet.png",
		"./res/MapSpritesheetData.txt", renderer);

	
	//ONLY WORKS WITH 32 BIT IMAGES - MAKE SURE LEVEL IS 32 BIT
	terrain.init("./res/level_map.png");
	player.init((terrain.getWidth()*terrain.getTileWidth())/2, ((terrain.getHeight()*terrain.getTileHeight()) / 2 )+250, 100, 100, 100, 100);
	
	player.move(DOWN);
	player.stopMovingY();
	player.stopMovingX();
	
	inputM.init();

	//music = Mix_LoadMUS("./res/GameMusic.mp3");

	//Mix_PlayMusic(music, -1);

	return true;
}

bool GameplayState::close()
{
	return true;
}

void GameplayState::pause() {}
void GameplayState::resume() {}

void GameplayState::input(SDL_Event* event) 
{
	inputM.input(event);
	
	if (inputM.keyPressed[K_UP])
	{
		player.move(UP);
	}
	else if (inputM.keyPressed[K_DOWN])
	{
		player.move(DOWN);
	}
	else
	{
		player.stopMovingY();
	}
	
	if (inputM.keyPressed[K_LEFT])
	{
		player.move(LEFT);
	}
	else if (inputM.keyPressed[K_RIGHT])
	{
		player.move(RIGHT);
	}
	else
	{
		player.stopMovingX();
	}
}

void GameplayState::update()
{
	player.update();

	if (player.getX() < 0)
	{
		player.setX(0);
	}
	else if (player.getX() + player.getW() > terrain.getTileWidth()*terrain.getWidth())
	{
		player.setX(terrain.getTileWidth() * terrain.getWidth() - player.getW());
	}

	if (player.getY() < 0)
	{
		player.setY(0);
	}
	else if (player.getY() + player.getH() > terrain.getTileHeight()*terrain.getHeight())
	{
		player.setY(terrain.getTileHeight() * terrain.getHeight() - player.getH());
	}

	camera->setCameraCenterPos(player.getCenterX(), player.getCenterY());
	if (camera->getX() < 0)
	{
		camera->setCameraPos(0, camera->getY());
	}
	else if (camera->getX()+camera->getScreenWidth() > terrain.getTileWidth()*terrain.getWidth())
	{
		camera->setCameraPos(terrain.getTileWidth() * terrain.getWidth() - camera->getScreenWidth(), camera->getY());
	}

	if (camera->getY() < 0)
	{
		camera->setCameraPos(camera->getX(), 0);
	}
	else if (camera->getY()+camera->getScreenHeight() > terrain.getTileHeight()*terrain.getHeight())
	{
		camera->setCameraPos(camera->getX(), terrain.getTileHeight() * terrain.getHeight() - camera->getScreenHeight());
	}
}
void GameplayState::render()
{
	//RENDER TERRAIN
	int k = 0;
	for (int i = 0; i < terrain.getHeight() * terrain.getHeight(); i++)
	{
		int y = floor(i / terrain.getWidth());
		int x = i % terrain.getWidth();
		if ((abs(camera->getX() - x*terrain.getTileWidth()) < (camera->getScreenWidth()) + terrain.getTileWidth()) &&
			(abs(camera->getY() - y*terrain.getTileHeight()) < (camera->getScreenHeight()) + terrain.getTileHeight() ))
		{
			int s = terrain.getTileMap()[i];
			if (s != NULL_TILE)
			{
				renderer->renderSDLTexture(terrainSheet.getSpritesheet(), camera, x*terrain.getTileWidth(), y*terrain.getTileHeight(), terrain.getTileWidth(), terrain.getTileHeight(), terrainSheet.getSprite(s));
			}
		}
	}

	//RENDER PLAYER
	renderer->renderSDLRectangle();
}