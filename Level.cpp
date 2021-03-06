
#include "Level.h"


const float Level::PLAYER_INITIAL_X = 240.0f;
const float Level::PLAYER_INITIAL_Y = 112.0f;
const float Level::BOSS_INITIAL_X = 240.0f;
const float Level::BOSS_INITIAL_Y = 9400.0f;

Level::Level()
{
	levelNumber = -1;
}

Level::Level(int level) : levelNumber(level) {}

Level::~Level(void) {}


/* Loading */
bool Level::load(GameData *data, Viewport *viewport)
{
	if (!staticTilesLayer.load(levelNumber, data)) return false;
	if (!objectsLayer.load(levelNumber, data)) return false;
	if (!enemiesLayer.load(levelNumber, data)) return false;
	player = Player(PLAYER_INITIAL_X, PLAYER_INITIAL_Y, GameData::PLAYER1_SPRITE_INDEX, 20, 30, true, 0.0f, 0.0f);
	viewport->updateWithPosition(player.getX(), player.getY(), false);
	if (levelNumber == BOSS_LEVEL) boss = Boss(BOSS_INITIAL_X, BOSS_INITIAL_Y, GameData::BOSS_TEX_INDEX, 480, 232, true, 100);
	//if (levelNumber == BOSS_LEVEL) boss = Boss(240, 600, GameData::BOSS_TEX_INDEX, 480, 232, true, 100);
	player.setLanternActivated(levelNumber == LANTERN_LEVEL);
	if (levelNumber == DEATH_WALL_LEVEL) deathWall = DeathWall(viewport->getWidth(), viewport->getHeight());
	bossTriggered = false;
	return true;
}


/* Input */
void Level::resolveInput(InputHandler *input)
{
	player.resolveInput(input);
}


/* Updating */
void Level::update(GameData *data, Viewport *viewport)
{
	bool viewportSetted = false;
	// Layers
	objectsLayer.update(data, viewport);
	enemiesLayer.update(data, viewport, getCollisionObjects(), staticTilesLayer.getCollisionMap(), &player);
	std::vector<BossTail*> parts;
	// Boss
	if (levelNumber == BOSS_LEVEL) {
		// Simulate an object with the viewport coordinates
		GameObject viewportObject = GameObject(viewport->getLeft() + viewport->getWidth()/2,
											   viewport->getTop() - viewport->getHeight()/2,
										       -1, viewport->getWidth(), viewport->getHeight(), false);
		if (boss.isIntersecting(viewportObject)) {
			if (!bossTriggered) {
				data->stopSound(GameData::JUNGLE_THEME_INDEX);
				data->playSound(GameData::BOSS_THEME_INDEX);
				bossTriggered = true;
			}
			// Viewport
			viewport->updateWithPosition(player.getX(), player.getY(), true);
			viewportSetted = false;

			parts = boss.getAliveParts();
			boss.update(data, viewport, getCollisionObjects(), staticTilesLayer.getCollisionMap(), player);
		}
	}
	// Player
	std::vector<GameObject> objectesColisionants = getCollisionObjects();
	for (unsigned int i = 0; i < parts.size(); i++) {
		objectesColisionants.push_back( *parts[i] );
	}
	int indexInteractiveObject = player.update(data, viewport, objectesColisionants, objectsLayer.getInteractiveObjects(), staticTilesLayer.getCollisionMap(), enemiesLayer.getEnemies(), parts);
	if (indexInteractiveObject >= 0) objectsLayer.removeObject(indexInteractiveObject);
	// DeathWall
	if (levelNumber == DEATH_WALL_LEVEL) {
		deathWall.update(data, enemiesLayer.getEnemies(), player);
	}
	// Viewport
	if (!viewportSetted) viewport->updateWithPosition(player.getX(), player.getY(), false);
}


/* Rendering */
void Level::render(GameData *data, Viewport *viewport)
{
	// Static layers
	staticTilesLayer.render(data, viewport);
	// DeathWall
	if (levelNumber == DEATH_WALL_LEVEL) deathWall.render(data);
	// Player
	player.render(data);
	// Boss
	if (levelNumber == BOSS_LEVEL) {
		// Simulate an object with the viewport coordinates
		GameObject viewportObject = GameObject(viewport->getLeft() + viewport->getWidth()/2,
											   viewport->getTop() - viewport->getHeight()/2,
										       -1, viewport->getWidth(), viewport->getHeight(), false);
		if (boss.isIntersecting(viewportObject)) boss.render(data);
	}
	// Dinamic layers
	enemiesLayer.render(data, viewport);
	objectsLayer.render(data, viewport);
}


/* Getters */
void Level::getSizeInPixels(int *width, int *height)
{
	staticTilesLayer.getSizeInPixels(width, height);
}

void Level::getSizeInTiles(int *width, int *height)
{
	staticTilesLayer.getSizeInTiles(width, height);
}

void Level::getTileSizeInPixels(int *width, int *height)
{
	staticTilesLayer.getTileSizeInPixels(width, height);
}

std::vector<GameObject> Level::getCollisionObjects()
{
	std::vector<GameObject> collisionObjects = objectsLayer.getCollisionObjects();
	std::vector<Enemy> enemies = enemiesLayer.getEnemies();
	collisionObjects.insert(collisionObjects.end(), enemies.begin(), enemies.end());
	collisionObjects.insert(collisionObjects.end(), player);
	return collisionObjects;
}

int Level::getPlayerLife()
{
	return player.getLife();
}

WeaponType Level::getPlayerWeaponType()
{
	return player.getWeaponType();
}

bool Level::playerHasLost()
{
	return player.isDead() && player.isAnimationFinished();
}

bool Level::playerHasWon()
{
	if (levelNumber != BOSS_LEVEL) return player.hasWon();
	else return boss.isDead();
}