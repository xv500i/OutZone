
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
