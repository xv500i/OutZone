
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
	GameObject go2(75.0f, 300.0f, -1, 60, 30, false);
	obstacles.push_back(go2);
	GameObject go3(100.0f, 200.0f, -1, 30, 60, false);
	obstacles.push_back(go3);
	GameObject go4(120.0f, 100.0f, -1, 15, 15, false);
	obstacles.push_back(go4);
	playerShots.clear();
	Enemy en(300.0f, 100.f, -1, 16, 16, true); 
	enemies.push_back(en);
	Enemy en2(300.0f, 50.f, -1, 16, 16, true); 
	enemies.push_back(en2);
	player = Player(50.0f, 50.0f, -1, 16, 16, true, 0.0f, 0.0f);
	player.setPhantom(false);
	
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

	unsigned int i;
	for (i = 0; i < obstacles.size(); i++) {
		obstacles[i].render();
	}

	player.render();
	
	for (i = 0; i < enemies.size(); i++) {
		enemies[i].render();
	}
	
	for (i = 0; i < playerShots.size(); i++) {
		playerShots[i].render();
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
		player.shotPrimaryWeapon(playerShots);
	}
}

void Scene::update()
{
	int maxX, maxY, minX, minY;
	minX = minY = 0;
	getLevelSizeInPixels(currentLevel, maxX, maxY);
	
	int size = playerShots.size();
	for (std::vector<MobileGameObject>::iterator it = playerShots.begin() ; it != playerShots.end(); ) {
		it->update(obstacles);
		float x = it->getX();
		float y = it->getY();
		vector<GameObject> v;
		getCollisioningGameObjects(v);
		if (maxX < x || minX > x || maxY < y || minY > y) {
			it = playerShots.erase(it);
		} else {
			bool hasCollisioned = false;
			for(std::vector<GameObject>::iterator ito = obstacles.begin(); !hasCollisioned && ito != obstacles.end(); ito++) {
				hasCollisioned = it->isIntersecting(*ito);
			}
			if (!hasCollisioned) it++;
			else {
				it = playerShots.erase(it);
			}
		}
	}
	player.update(obstacles);

	for (unsigned int i = 0; i < enemies.size(); i++) {
		enemies[i].update(obstacles);
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