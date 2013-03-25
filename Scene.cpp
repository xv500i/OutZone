
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
	enemyShots.clear();
	Enemy en(120.0f, 130.f, -1, 16, 16, true);
	en.setPhantom(false);
	enemies.push_back(en);

	Enemy en2(300.0f, 50.f, -1, 16, 16, true);
	en2.setPhantom(false);
	enemies.push_back(en2);

	Enemy en3(player, 120.0f, 550.f, -1, 16, 16, true);
	en3.setPhantom(false);
	enemies.push_back(en3);

	Enemy en4(player, 50, 120.0f, 850.f, -1, 16, 16, true);
	en4.setPhantom(false);
	enemies.push_back(en4);

	player = Player(50.0f, 50.0f, GameData::PLAYER1_SPRITE_INDEX, 20, 20, true, 0.0f, 0.0f);
	player.setPhantom(false);
	
	// Loading layers
	bool b = levels[level - 1].staticTilesLayer.load(level, data);
	if (!b) return false;
	//return levels[level - 1].mobileTilesLayer.load(level, data);
	return true;
}

void Scene::render(int level, GameData *data, Viewport *viewport)
{
	// Rendering layers
	levels[level - 1].staticTilesLayer.render(data, viewport);
	//levels[level - 1].mobileTilesLayer.render(data);

	unsigned int i;
	for (i = 0; i < obstacles.size(); i++) {
		obstacles[i].render(data);
	}

	player.render(data);
	
	for (i = 0; i < enemies.size(); i++) {
		enemies[i].render(data);
	}
	
	for (i = 0; i < playerShots.size(); i++) {
		playerShots[i].render(data);
	}

	for (i = 0; i < enemyShots.size(); i++) {
		enemyShots[i].render(data);
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
	float catet = 2.0f;
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

void Scene::update(Viewport *viewport)
{
	int maxX, maxY, minX, minY;
	minX = minY = 0;
	getLevelSizeInPixels(currentLevel, maxX, maxY);

	int size = playerShots.size();
	vector<GameObject> v;
	getCollisioningGameObjects(v);
	std::vector<Bullet>::iterator it;
	for (it = playerShots.begin() ; it != playerShots.end(); ) {
		it->update(obstacles);
		float x = it->getX();
		float y = it->getY();
		

		if (maxX < x || minX > x || maxY < y || minY > y) {
			it = playerShots.erase(it);
		} else {
			bool hasCollisioned = false;
			for(std::vector<GameObject>::iterator ito = obstacles.begin(); !hasCollisioned && ito != obstacles.end(); ito++) {
				hasCollisioned = it->isIntersecting(*ito);
			}
			for(std::vector<Enemy>::iterator ie = enemies.begin(); !hasCollisioned && ie != enemies.end(); ) {
				if (it->isIntersecting(*ie)) {
					/* kill enemy */
					// TODO ANIMATION
					hasCollisioned = true;
					ie = enemies.erase(ie);
				} else {
					ie++;
				}
			}
			if (!hasCollisioned && !it->isDead()) it++;
			else {
				it = playerShots.erase(it);
			}
		}
	}
	for (it = enemyShots.begin() ; it != enemyShots.end(); ) {
		it->update(obstacles);
		float x = it->getX();
		float y = it->getY();
		if (maxX < x || minX > x || maxY < y || minY > y) {
			it = enemyShots.erase(it);
		} else {
			bool hasCollisioned = false;
			for(std::vector<GameObject>::iterator ito = obstacles.begin(); !hasCollisioned && ito != obstacles.end(); ito++) {
				hasCollisioned = it->isIntersecting(*ito);
			}
			if (it->isIntersecting(player)) {
				/* kill player */
				// TODO ANIMATION
				hasCollisioned = true;
			}
			if (!hasCollisioned && !it->isDead()) it++;
			else {
				it = enemyShots.erase(it);
			}
		}
	}
	player.update(v);
	if (player.getX() + player.getWidth()/2 > maxX) {
		float inc = maxX - player.getWidth()/2 - player.getX();
		player.updateBBox(inc, 0.0f);
		player.setX(maxX - player.getWidth()/2);
	}
	else if (player.getX() - player.getWidth()/2 < minX) {
		float inc = minX  + player.getWidth()/2 - player.getX();
		player.updateBBox(inc, 0.0f);
		player.setX(minX + player.getWidth()/2);
	}
	if (player.getY() + player.getLength()/2 > maxY) {
		float inc = maxY - player.getLength()/2 - player.getY();
		player.updateBBox(0.0f, inc);
		player.setY(maxY - player.getLength()/2);
	}
	else if (player.getY() - player.getLength()/2 < minY) {
		float inc = minY + player.getLength()/2 - player.getY();
		player.updateBBox(0.0f, inc);
		player.setY(minY + player.getLength()/2);
	}
	for (unsigned int i = 0; i < enemies.size(); i++) {
		enemies[i].update(v, enemyShots);
		if (enemies[i].getX() + enemies[i].getWidth()/2 > maxX) {
			float inc = maxX - enemies[i].getWidth()/2 - enemies[i].getX();
			enemies[i].updateBBox(inc, 0.0f);
			enemies[i].setX(maxX - enemies[i].getWidth()/2);
		}
		else if (enemies[i].getX() - enemies[i].getWidth()/2 < minX) {
			float inc = minX  + enemies[i].getWidth()/2 - enemies[i].getX();
			enemies[i].updateBBox(inc, 0.0f);
			enemies[i].setX(minX + enemies[i].getWidth()/2);
		}
		if (enemies[i].getY() + enemies[i].getLength()/2 > maxY) {
			float inc = maxY - enemies[i].getLength()/2 - enemies[i].getY();
			enemies[i].updateBBox(0.0f, inc);
			enemies[i].setY(maxY - enemies[i].getLength()/2);
		}
		else if (enemies[i].getY() - enemies[i].getLength()/2 < minY) {
			float inc = minY + enemies[i].getLength()/2 - enemies[i].getY();
			enemies[i].updateBBox(0.0f, inc);
			enemies[i].setY(minY + enemies[i].getLength()/2);
		}
	}

	viewport->updateWithPosition(player.getX(), player.getY());
}

void Scene::getLevelSizeInPixels(int level, int &w, int &h) 
{
	levels[level - 1].staticTilesLayer.getSizeInPixels(&w, &h);
}

void Scene::getCollisioningGameObjects(vector<GameObject> &v)
{
	// FIXME I'M FAMOUS
	//AB.reserve( A.size() + B.size() ); // preallocate memory
	//AB.insert( AB.end(), A.begin(), A.end() );
	//AB.insert( AB.end(), B.begin(), B.end() );
	std::vector<GameObject> res;
	res.reserve(obstacles.size() + 1 + enemies.size());
	res.insert(res.end(), obstacles.begin(), obstacles.end());
	res.insert(res.end(), enemies.begin(), enemies.end());
	res.push_back(player);
	v = res;
}