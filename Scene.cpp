
#include "Scene.h"

Scene::Scene(void)
{
}

Scene::~Scene(void)
{
}

bool Scene::loadLevel(int level)
{
	currentLevel = level;
	GameObject go(100.0f, 100.0f, -1, 30, 30, false);
	obstacles.push_back(go);
	bales.clear();
	player.setX(0);
	player.setY(0);
	player.setWidth(16);
	player.setLength(16);
	return levels[level - 1].load(level);
}

void Scene::render(int level, GameData *data)
{
	levels[level - 1].render(data);
	player.render();
	for (int i = 0; i < bales.size(); i++) {
		bales[i].render();
	}
}

void Scene::getLevelSize(int level, int *width, int *height)
{
	levels[level - 1].getSizeInTiles(width, height);
}

void Scene::getLevelTileSize(int level, int *width, int *height)
{
	levels[level - 1].getTileSizeInPixels(width, height);
}

void Scene::resolveInput(InputHandler &input) {
	// player control
	// HARDCODED
	float vDes = 0.3f;
	// TODO COLISIONS
	if (input.keyIsDown(input.getMoveUpKey())) {
		player.setVY(vDes);
	} else if (input.keyIsDown(input.getMoveDownKey())) {
		player.setVY(-vDes);
	} else {
		player.setVY(0.0f);
	}
	if (input.keyIsDown(input.getMoveRightKey())) {
		player.setVX(vDes);
	} else if (input.keyIsDown(input.getMoveLeftKey())) {
		player.setVX(-vDes);
	} else {
		player.setVX(0.0f);
	}

	if (input.keyIsDown(input.getPrimaryWeaponKey())) {
		player.shotPrimaryWeapon(bales);
	}
	
}

void Scene::update(long msec)
{
	int maxX, maxY, minX, minY;
	minX = minY = 0;
	getLevelSizeInPixels(currentLevel, maxX, maxY);
	player.update(msec);
	int size = bales.size();
	for (std::vector<MobileGameObject>::iterator it = bales.begin() ; it != bales.end(); ) {
		it->update(msec);
		float x = it->getX();
		float y = it->getY();
		vector<GameObject> v;
		getCollisioningGameObjects(v);
		if (maxX < x || minX > x || maxY < y || minY > y) {
			it = bales.erase(it);
		} else {

			it++;
		}
	}

}

void Scene::getLevelSizeInPixels(int level, int &w, int &h) 
{
	int tileWidth, tileHeight, tilesWidth, tilesHeigth;
	levels[level - 1].getTileSizeInPixels(&tileWidth, &tileHeight);
	levels[level - 1].getSizeInTiles(&tilesWidth, &tilesHeigth);
	w = tilesWidth * tileWidth;
	h = tilesHeigth * tileHeight;
}

void Scene::getCollisioningGameObjects(vector<GameObject> &v)
{
	v = obstacles;
}