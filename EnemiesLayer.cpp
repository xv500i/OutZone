
#include "EnemiesLayer.h"
#include <iostream>
#include <sstream>
#include <fstream>


const char* EnemiesLayer::FILE_NAME_PREFIX = "level";
const char* EnemiesLayer::FILE_NAME_SUFIX = "Enemies";
const char* EnemiesLayer::FILE_EXT = ".txt";

EnemiesLayer::EnemiesLayer(void) {}

EnemiesLayer::~EnemiesLayer(void) {}


/* Loading */
bool EnemiesLayer::load(int level, GameData *data) {}

/* Updating */
void EnemiesLayer::update(GameData *data, Viewport *viewport, std::vector<GameObject> &collisionObjects, std::vector<bool> &collisionTiles, Player *player)
{
	for (unsigned int i = 0; i < enemies.size(); i++) {
		enemies[i].update(data, viewport, collisionObjects, collisionTiles, *player);
	}
}

/* Rendering */
void EnemiesLayer::render(GameData *data, Viewport *viewport)
{
	// Simulate an object with the viewport coordinates
	GameObject viewportObject = GameObject(viewport->getLeft() + viewport->getWidth()/2,
										   viewport->getTop() - viewport->getHeight()/2,
										   -1, viewport->getWidth(), viewport->getHeight(), false);
	for (unsigned int i = 0; i < enemies.size(); i++) {
		if (enemies[i].isIntersecting(viewportObject)) enemies[i].render(data);
	}
}

/* Getters */
std::vector<Enemy> EnemiesLayer::getEnemies()
{
	return enemies;
}