
#include "Scene.h"

Scene::Scene(void)
{
}

Scene::~Scene(void)
{
}

bool Scene::loadLevel(int level, GameData *data)
{
	currentLevel = level;
	GameObject go(100.0f, 100.0f, -1, 30, 30, false);
	obstacles.push_back(go);
	bales.clear();
	player = Player(50.0f, 50.0f, -1, 16, 16, true, 0.0f, 0.0f);
	
	// Loading layers
	bool b = levels[level - 1].staticTilesLayer.load(level, data);
	if (!b) return false;
	//return levels[level - 1].mobileTilesLayer.load(level, data);
	return true;
}

void Scene::render(int level, GameData *data)
{
	// Rendering layers
	levels[level - 1].staticTilesLayer.render(data);
	//levels[level - 1].mobileTilesLayer.render(data);


	for (unsigned int x = 0; x < obstacles.size(); x++) {
		obstacles[x].render();
	}
	player.render();
	for (unsigned int i = 0; i < bales.size(); i++) {
		bales[i].render();
	}
}

void Scene::getLevelSize(int level, int *width, int *height)
{
	levels[level - 1].staticTilesLayer.getSizeInTiles(width, height);
}

void Scene::getLevelTileSize(int level, int *width, int *height)
{
	levels[level - 1].staticTilesLayer.getTileSizeInPixels(width, height);
}

void Scene::resolveInput(InputHandler &input) {
	// player control
	// HARDCODED
	float vDes = 5.0f;
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

void Scene::update()
{
	int maxX, maxY, minX, minY;
	minX = minY = 0;
	getLevelSizeInPixels(currentLevel, maxX, maxY);
	player.update();
	int size = bales.size();
	for (std::vector<MobileGameObject>::iterator it = bales.begin() ; it != bales.end(); ) {
		it->update();
		float x = it->getX();
		float y = it->getY();
		vector<GameObject> v;
		getCollisioningGameObjects(v);
		if (maxX < x || minX > x || maxY < y || minY > y) {
			it = bales.erase(it);
		} else {
			bool hasCollisioned = false;
			for(std::vector<GameObject>::iterator ito = obstacles.begin(); !hasCollisioned && ito != obstacles.end(); ito++) {
				hasCollisioned = it->isIntersecting(*ito);
			}
			if (!hasCollisioned) it++;
			else {
				it = bales.erase(it);
			}
		}
	}

}

void Scene::getLevelSizeInPixels(int level, int &w, int &h) 
{
	levels[level - 1].staticTilesLayer.getSizeInPixels(&w, &h);
}

void Scene::getCollisioningGameObjects(vector<GameObject> &v)
{
	v = obstacles;
}