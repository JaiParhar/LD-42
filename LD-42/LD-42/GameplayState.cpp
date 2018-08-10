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
	
	gunSheet.loadSpritesheet("./res/GunSpritesheet.png",
		"./res/GunSpritesheetData.txt", renderer);

	bulletSheet.loadSpritesheet("./res/BulletSpritesheet.png",
		"./res/BulletSpritesheetData.txt", renderer);

	terrainSheet.loadSpritesheet("./res/MapSpritesheet.png",
		"./res/MapSpritesheetData.txt", renderer);

	farmSheet.loadSpritesheet("./res/FarmSpritesheet.png",
		"./res/FarmSpritesheetData.txt", renderer);

	enemySheet.loadSpritesheet("./res/EnemySpritesheet.png",
		"./res/EnemySpritesheetData.txt", renderer);

	powerupSheet.loadSpritesheet("./res/PowerUpSpritesheet.png",
		"./res/PowerUpSpritesheetData.txt", renderer);

	//ONLY WORKS WITH 32 BIT IMAGES - MAKE SURE LEVEL IS 32 BIT
	terrain.init("./res/level_map.png");
	player.init((terrain.getWidth()*terrain.getTileWidth())/2, ((terrain.getHeight()*terrain.getTileHeight()) / 2 )+250, 100, 100, 100, 100);
	farm.init((terrain.getWidth()*terrain.getTileWidth()) / 2, (terrain.getHeight()*terrain.getTileHeight()) / 2, (player.getW()/50)*(150), (player.getH() / 50)*(250), (player.getW() / 50)*(150), (player.getH() / 50)*(250));
	farm.setCenterPos((terrain.getWidth()*terrain.getTileWidth()) / 2, (terrain.getHeight()*terrain.getTileHeight()) / 2);
	
	player.move(DOWN);
	player.stopMovingY();
	player.stopMovingX();
	
	player.setFarm(&farm);

	enemies.clear();
	bullets.clear();
	powerups.clear();

	enemySpawnThreshold = camera->getScreenWidth();
	maxEnemies = 30;
	for (int i = 0; i < maxEnemies; i++)
	{
		int randID = rand() % 2;
		int randX = (rand() % terrain.getWidth()) * terrain.getTileWidth();
		int randY = (rand() % terrain.getHeight()) * terrain.getTileHeight();

		Enemy addEnemy;
		addEnemy.init(randX, randY, 100, 100, 100, 100);
		addEnemy.setID(randID);
		enemies.push_back(addEnemy);
	}

	inputM.init();

	gui.init(camera->getScreenWidth(), camera->getScreenHeight(), renderer);

	player.stopShooting();

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

	if (inputM.keyPressed[K_1])
	{
		player.setPlayerGun(0);
		std::cout << player.getPlayerGun()->getGunName() << std::endl;
	}
	else if (inputM.keyPressed[K_2])
	{
		player.setPlayerGun(1);
		std::cout << player.getPlayerGun()->getGunName() << std::endl;
	}
	else if (inputM.keyPressed[K_3])
	{
		player.setPlayerGun(2);
		std::cout << player.getPlayerGun()->getGunName() << std::endl;
	}
	
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

	if (inputM.keyPressed[K_W])
	{
		player.startShooting(UP);
	}
	else if (inputM.keyPressed[K_S])
	{
		player.startShooting(DOWN);
	} 
	else if (inputM.keyPressed[K_A])
	{
		player.startShooting(LEFT);
	}
	else if (inputM.keyPressed[K_D])
	{
		player.startShooting(RIGHT);
	}
	else
	{
		player.stopShooting();
	}

	if (inputM.keyPressed[K_R])
	{
		player.reload();
	}

	if (inputM.keyPressed[K_8])
	{
		farm.subHP(1);
	}
}

void GameplayState::update()
{
	player.update();

	for (int i = 0; i < powerups.size(); i++)
	{
		if (player.checkCollision(&powerups.at(i)))
		{
			if (powerups.at(i).getID() <= 3)
			{
				player.resetDistance();
				player.addHP(10);
				player.addFatLevel(2);
			}
			else
			{
				player.getPlayerGun()->addAmmo(powerups.at(i).getID() - 3, player.getPlayerGun()->gunMagSize.at(powerups.at(i).getID() - 3));
			}
			powerups.erase(powerups.begin() + i);
		}
	}

	for (int i = 0; i < enemies.size(); i++)
	{
		enemies.at(i).update();
		if (enemies.at(i).enemyID == PLAYER_ATTACKER)
		{
			enemies.at(i).moveToward(player.getCenterX(), player.getCenterY());
		}
		else if (enemies.at(i).enemyID == FARM_ATTACKER)
		{
			enemies.at(i).moveToward(farm.getCenterX(), farm.getCenterY());
		}

		for (int j = 0; j < bullets.size(); j++)
		{
			if (enemies.at(i).checkCollision(&bullets.at(j)) && !enemies.at(i).isDying())
			{
				PowerUp newPowerUp;
				newPowerUp.init(enemies.at(i).getCenterX(), enemies.at(i).getCenterY(), 25, 25, 25, 25);
				powerups.push_back(newPowerUp);
				enemies.at(i).setHP(0);
			}
		}

		if (player.checkCollision(&enemies.at(i)))
		{
			enemies.at(i).setHP(0);
			if (!enemies.at(i).isDying())
			{
				player.subtractHP(10);
			}
		}

		if (farm.checkCollision(&enemies.at(i)))
		{
			enemies.at(i).setHP(0);
			if (!enemies.at(i).isDying())
			{
				farm.subHP(1);
			}
		}

		if (enemies.at(i).isDead())
		{
			enemies.erase(enemies.begin() + i);
			int randID = rand() % 2;
			int randX = (rand() % terrain.getWidth()) * terrain.getTileWidth();
			int randY = (rand() % terrain.getHeight()) * terrain.getTileHeight();
			int randShift = rand() % 2;

			if (abs(player.getCenterX() - randX) < enemySpawnThreshold)
			{
				//Player is to the right
				if (player.getCenterX() - randX > 0)
				{
					randX -= enemySpawnThreshold;
				}
				else
				{
					randX += enemySpawnThreshold;
				}
			}

			if (abs(player.getCenterY() - randY) < enemySpawnThreshold)
			{
				//Player is below
				if (player.getCenterY() - randY > 0)
				{
					randY -= enemySpawnThreshold;
				}
				else
				{
					randY += enemySpawnThreshold;
				}
			}

			Enemy addEnemy;
			addEnemy.init(randX, randY, 100, 100, 100, 100);
			addEnemy.setID(randID);
			enemies.push_back(addEnemy);
		}

		enemies.at(i).update();
	}

	farm.update();

	if (farm.getHP() <= 0 || player.getHP() <= 0)
	{
		init(currentState, renderer, camera);
		*currentState = 2;
	}

	gui.setHBar(player.getHP(), player.getMaxHP());
	gui.setFarmHPText(farm.getHP());

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

	if (player.isShooting())
	{
		std::vector<Bullet> addBullets = player.shoot();
		bullets.insert(bullets.end(), addBullets.begin(), addBullets.end());
	}

	for (int i = 0; i < bullets.size(); i++)
	{
		bullets.at(i).update();
		if (abs(camera->getX() - bullets.at(i).getX()) > (camera->getScreenWidth()) ||
			abs(camera->getY() - bullets.at(i).getY()) > (camera->getScreenHeight()))
		{
			bullets.erase(bullets.begin() + i);
		}
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

	gui.setAmmoText(player.getPlayerGun()->getCurrGunMag(), player.getPlayerGun()->getGunAmmo());
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

	renderer->renderSDLTexture(farmSheet.getSpritesheet(), camera, farm.getX(), farm.getY(), farm.getW(), farm.getH(), farmSheet.getSprite(farm.getAnimation()->getFrame()));

	//RENDER ENTITIES
	for (int i = 0; i < bullets.size(); i++)
	{
		renderer->renderSDLTexture(bulletSheet.getSpritesheet(), camera, bullets.at(i).getX(), bullets.at(i).getY(), bullets.at(i).getW(), bullets.at(i).getH(), bulletSheet.getSprite(bullets.at(i).getSpriteID()), bullets.at(i).getAngle(), NULL, 1, (SDL_RendererFlip)bullets.at(i).getFlip());
	}

	for (int i = 0; i < powerups.size(); i++)
	{
		renderer->renderSDLTexture(powerupSheet.getSpritesheet(), camera, powerups.at(i).getX(), powerups.at(i).getY(), powerups.at(i).getW(), powerups.at(i).getH(), powerupSheet.getSprite(powerups.at(i).getID()));
	}

	for (int i = 0; i < enemies.size(); i++)
	{
		renderer->renderSDLTexture(enemySheet.getSpritesheet(), camera, enemies.at(i).getX(), enemies.at(i).getY(), enemies.at(i).getW(), enemies.at(i).getH(), enemySheet.getSprite(enemies.at(i).getCurrentAnimation()->getFrame()), 0.0, NULL, 1, (SDL_RendererFlip)enemies.at(i).getFlip());
	}

	if (player.getDirection() == UP)
	{
		if (player.shoudDamageColor())
		{
			renderer->renderSDLTexture(gunSheet.getSpritesheet(), camera, player.getPlayerGun()->getX(), player.getPlayerGun()->getY(), player.getPlayerGun()->getW(), player.getPlayerGun()->getH(), gunSheet.getSprite(player.getPlayerGun()->getGunAnimation()->getFrame()), NULL, NULL, 1, (SDL_RendererFlip)player.getPlayerGun()->getFlip(), 255, 128, 128);
			renderer->renderSDLTexture(playerSheet.getSpritesheet(), camera, player.getX(), player.getY(), player.getW(), player.getH(), playerSheet.getSprite(player.getCurrentAnimation()->getFrame()), 0.0, NULL, 1, (SDL_RendererFlip)player.getFlip(), 255, 128, 128);
		}
		else
		{
			renderer->renderSDLTexture(playerSheet.getSpritesheet(), camera, player.getX(), player.getY(), player.getW(), player.getH(), playerSheet.getSprite(player.getCurrentAnimation()->getFrame()), 0.0, NULL, 1, (SDL_RendererFlip)player.getFlip());
		}
	}
	else
	{
		if (player.shoudDamageColor())
		{
			renderer->renderSDLTexture(playerSheet.getSpritesheet(), camera, player.getX(), player.getY(), player.getW(), player.getH(), playerSheet.getSprite(player.getCurrentAnimation()->getFrame()), 0.0, NULL, 1, (SDL_RendererFlip)player.getFlip(), 255, 128, 128);
			renderer->renderSDLTexture(gunSheet.getSpritesheet(), camera, player.getPlayerGun()->getX(), player.getPlayerGun()->getY(), player.getPlayerGun()->getW(), player.getPlayerGun()->getH(), gunSheet.getSprite(player.getPlayerGun()->getGunAnimation()->getFrame()), NULL, NULL, 1, (SDL_RendererFlip)player.getPlayerGun()->getFlip(), 255, 128, 128);
		}
		else
		{
			renderer->renderSDLTexture(playerSheet.getSpritesheet(), camera, player.getX(), player.getY(), player.getW(), player.getH(), playerSheet.getSprite(player.getCurrentAnimation()->getFrame()), 0.0, NULL, 1, (SDL_RendererFlip)player.getFlip());
			renderer->renderSDLTexture(gunSheet.getSpritesheet(), camera, player.getPlayerGun()->getX(), player.getPlayerGun()->getY(), player.getPlayerGun()->getW(), player.getPlayerGun()->getH(), gunSheet.getSprite(player.getPlayerGun()->getGunAnimation()->getFrame()), NULL, NULL, 1, (SDL_RendererFlip)player.getPlayerGun()->getFlip());
		}
	}

	//RENDER GUI
	renderer->renderSDLRectangle(gui.getHPOutline().x, gui.getHPOutline().y, gui.getHPOutline().w, gui.getHPOutline().h);
	renderer->renderSDLRectangle(gui.getBaseHBar().x, gui.getBaseHBar().y, gui.getBaseHBar().w, gui.getBaseHBar().h, gui.getBaseHBarColor());
	renderer->renderSDLRectangle(gui.getHBar().x, gui.getHBar().y, gui.getHBar().w, gui.getHBar().h, gui.getHBarColor());
	renderer->renderText(gui.getHealthText(), MEDIUM, gui.getBaseHBar().x+10, gui.getBaseHBar().y+10);
	renderer->renderText(player.getPlayerGun()->getGunName() + ": " + gui.getAmmoText(), MEDIUM, 10, 10);
	renderer->renderText(gui.getFarmHPText(), MEDIUM, camera->getScreenWidth()/2 + 90, 10);
	if (player.getIsReloading())
	{
		renderer->renderText("Reloading", MEDIUM, 10, 60);
	}
}