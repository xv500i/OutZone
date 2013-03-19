
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
	Directions d;
	bool up = input.keyIsDown(input.getMoveUpKey());
	bool down = input.keyIsDown(input.getMoveDownKey());
	bool left = input.keyIsDown(input.getMoveLeftKey());
	bool right = input.keyIsDown(input.getMoveRightKey());
	bool something = up || down || right || left;
	if (up) {
		if (right) {
			d = UP_RIGHT;	
		} else if (left) {
			d = UP_LEFT;
		} else {
			d = UP;
		}
		
	} else if (down) {
		if (right) {
			d = DOWN_RIGHT;
		} else if (left) {
			d = DOWN_LEFT;
		} else {
			d = DOWN;
		}
	} else if (right) {
		d = RIGHT;
	} else if (left) {
		d = LEFT;
	} else {
	
	}

	
	float vx = 0.0f, vy = 0.0f;
	float catet = 5.0f;
	float absv = sqrt(catet*catet*2);
	if (something) {
		switch (d) {
			case UP:
				vy = absv;
				break;
			case DOWN:
				vy = -absv;
				break;
			case LEFT:
				vx = -absv;
				break;
			case RIGHT:
				vx = absv;
				break;
			case UP_RIGHT:
				vx = catet;
				vy = catet;
				break;
			case DOWN_RIGHT:
				vx = catet;
				vy = -catet;
				break;
			case UP_LEFT:
				vx = -catet;
				vy = catet;
				break;
			case DOWN_LEFT:
				vx = -catet;
				vy = -catet;
				break;
		}
	}
	player.setVX(vx);
	player.setVY(vy);
	if (input.keyIsDown(input.getPrimaryWeaponKey())) {
		player.shotPrimaryWeapon(bales);
	}
}

void Scene::update()
{
	int maxX, maxY, minX, minY;
	minX = minY = 0;
	getLevelSizeInPixels(currentLevel, maxX, maxY);
	player.update(obstacles);
	int size = bales.size();
	for (std::vector<MobileGameObject>::iterator it = bales.begin() ; it != bales.end(); ) {
		it->update(obstacles);
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
	// FIXME I'M FAMOUS
	v = obstacles;
}