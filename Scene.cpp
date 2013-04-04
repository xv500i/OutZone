
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
	// HUD loading
	hud.load(viewport);

	// Level loading
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

	// TODO: passar la vida del player! level.getPlayerLife() --> player.getLife()
	// HUD update
	hud.update(data, viewport, 3);

	//boss.update(data, enemyShots, player.getX(), player.getY());
}


/* Rendering */
void Scene::render(GameData *data, Viewport *viewport)
{
	// Rendering the HUD
	hud.render(data, viewport);

	// Rendering the level
	levels[currentLevel - 1].render(data, viewport);

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