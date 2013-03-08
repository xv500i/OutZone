
#include "Scene.h"


Scene::Scene(void)
{
}

Scene::~Scene(void)
{
}

bool Scene::loadLevel(int level)
{
	return levels[level - 1].load(level);
}

void Scene::render(int level, GameData *data)
{
	levels[level - 1].render(data);
}

void Scene::getLevelSize(int level, int *width, int *height)
{
	levels[level - 1].getSize(width, height);
}