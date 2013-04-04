
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
bool EnemiesLayer::load(int level, GameData *data) 
{
	setLevel(level);

	// Open the file
	std::stringstream ss;
	ss << FILE_NAME_PREFIX << level << FILE_NAME_SUFIX << FILE_EXT;
	std::ifstream file(ss.str());

	// Read the file
	std::string line;
	if (file.is_open()) {
		while (file.good()) {
			getline(file, line);
			std::stringstream sstr(line);
			int x, y, width, height;
			char enemyCategory;
			char enemyType;
			sstr >> enemyCategory;
			sstr >> enemyType;
			if (sstr.peek() == ' ') sstr.ignore();
			sstr >> x;
			if (sstr.peek() == ',') sstr.ignore();
			sstr >> y;
			if (sstr.peek() == ' ') sstr.ignore();
			sstr >> width;
			if (sstr.peek() == ',') sstr.ignore();
			sstr >> height;
	
			// GuardPathStates
			std::vector<GuardPathState> path;
			while (sstr.peek() == ' ') {
				sstr.ignore();
				int vx, vy, tics;
				sstr >> vx;
				if (sstr.peek() == ',') sstr.ignore();
				sstr >> vy;
				if (sstr.peek() == ',') sstr.ignore();
				sstr >> tics;
				path.push_back(GuardPathState(vx, vy, tics));
			}

			EnemyType type;
			switch (enemyCategory) {
			case 'B':
				switch (enemyType) {
				case '1': type = BAT_1; break;
				case '2': type = BAT_2; break;
				case '3': type = BAT_3; break;
				default: break;
				}
				break;
			case 'S':
				switch (enemyType) {
				case '2': type = SPIDER_1; break;
				case '1': type = SPIDER_2; break;
				default: break;
				}
				break;
			default: break;
			}
			Enemy enemy(type, x*TILE_WIDTH_IN_PIXELS + TILE_WIDTH_IN_PIXELS/2, y*TILE_HEIGHT_IN_PIXELS + TILE_HEIGHT_IN_PIXELS/2, width, height, path);
			enemies.push_back(enemy);
		}
		return true;
	}
	else {
		std::cout << "Error obrint el fitxer de càrrega de la capa d'enemics del nivell " << level << std::endl;
		return false;
	}

	return true;
}

/* Updating */
void EnemiesLayer::update(GameData *data, Viewport *viewport, std::vector<GameObject> &collisionObjects, std::vector<bool> &collisionTiles, Player *player)
{
	for (std::vector<Enemy>::iterator it = enemies.begin(); it != enemies.end();) {
		it->update(data, viewport, collisionObjects, collisionTiles, *player);
		if (it->isDead()) it = enemies.erase(it);
		else it++;
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
std::vector<Enemy>& EnemiesLayer::getEnemies()
{
	return enemies;
}