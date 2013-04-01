
#include "Scene.h"


Scene::Scene(void) 
{
	levels = vector<Level>(NUM_LEVELS);
	for (unsigned int i = 0; i < NUM_LEVELS; i++) {
		levels[i] = Level(i + 1);
	}
	currentLevel = -1;
}

Scene::~Scene(void) {}


/* Loading */
bool Scene::changeLevel(int newLevel, GameData *data, Viewport *viewport)
{
	currentLevel = newLevel;
	if (!loadLevel(data)) return false;

	int width, height;
	getLevelSizeInPixels(1, width, height);
	viewport->setLimits(0.0f, height, width, 0.0f);
	return true;
}

bool Scene::loadLevel(GameData *data)
{
	//boss = Boss(200.0f, 800.0f, 2, 300.0f, 100.0f, true, 100);
	
	// Loading level
	data->playSound(GameData::JUNGLE_THEME_INDEX);
	if (!levels[currentLevel - 1].load(data)) return false;
	return true;

	/*Enemy en(120.0f, 130.f, GameData::ALIEN1_SPRITE_INDEX, 16, 16, true);
	en.setPhantom(false);
	enemies.push_back(en);

	Enemy en2(300.0f, 50.f, GameData::ALIEN1_SPRITE_INDEX, 16, 16, true);
	en2.setPhantom(false);
	enemies.push_back(en2);

	Enemy en3(player, 120.0f, 550.f, GameData::ALIEN1_SPRITE_INDEX, 16, 16, true);
	en3.setPhantom(false);
	enemies.push_back(en3);

	Enemy en4(player, 50, 120.0f, 850.f, GameData::ALIEN1_SPRITE_INDEX, 16, 16, true);
	en4.setPhantom(false);
	enemies.push_back(en4);*/
}


/* Updating */
void Scene::resolveInput(InputHandler &input) 
{
	levels[currentLevel -1].resolveInput(&input);
}

void Scene::update(GameData *data, Viewport *viewport)
{
	// Level update 
	levels[currentLevel - 1].update(data, viewport);

	//boss.update(data, enemyShots, player.getX(), player.getY());
}


/* Rendering */
void Scene::render(GameData *data, Viewport *viewport)
{
	// Rendering the level
	levels[currentLevel - 1].render(data, viewport);
	
	// TODO: Canviar per enemiesLayer!!
	unsigned int i;
	for (i = 0; i < enemies.size(); i++) {
		enemies[i].render(data);
	}

	//boss.render(data);
}


/* Getters */
void Scene::getLevelSizeInPixels(int level, int &w, int &h) 
{
	levels[level - 1].getSizeInPixels(&w, &h);
}

void Scene::getLevelSize(int level, int *width, int *height)
{
	levels[level - 1].getSizeInTiles(width, height);
}

void Scene::getLevelTileSize(int level, int *width, int *height)
{
	levels[level - 1].getTileSizeInPixels(width, height);
}

void Scene::getCollisionEntities(vector<GameObject> *objects, vector<bool> *tiles)
{
	*tiles = levels[currentLevel - 1].getCollisionMap();
	*objects = levels[currentLevel - 1].getCollisionObjects();
	//TODO: afegir els enemics i el player!!
}