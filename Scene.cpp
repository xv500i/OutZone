
#include "Scene.h"


Scene::Scene(void)
{
}

Scene::~Scene(void)
{
}

bool Scene::loadLevel(int level)
{
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
	player.update(msec);
	for (int i = 0; i < bales.size(); i++) {
		bales[i].update(msec);
		// FIXME misa bala pantalla se sale, misa bala se pop()
	}
	//std::cout << player.getDirection() << std::endl;

}

void Scene::getLevelSizeInPixels(int level, int &w, int &h) 
{
	int tileWidth, tileHeight, tilesWidth, tilesHeigth;
	levels[level - 1].getTileSizeInPixels(&tileWidth, &tileHeight);
	levels[level - 1].getSizeInTiles(&tilesWidth, &tilesHeigth);
	w = tilesWidth * tileWidth;
	h = tilesHeigth * tileHeight;
}