
#include "Level.h"


const float Level::PLAYER_INITIAL_X = 240.0f;
const float Level::PLAYER_INITIAL_Y = 112.0f;

Level::Level()
{
	levelNumber = -1;
}

Level::Level(int level) : levelNumber(level) {}

Level::~Level(void) {}


/* Loading */
bool Level::load(GameData *data)
{
	bool b = staticTilesLayer.load(levelNumber, data);
	if (!b) return false;
	//b = mobileTilesLayer.load(levelNumber, data);
	//if (!b) return false;
	b = objectsLayer.load(levelNumber, data);
	if (!b) return false;
	//b = enemiesLayer.load(levelNumber, data);
	//if (!b) return false;
	player = Player(PLAYER_INITIAL_X, PLAYER_INITIAL_Y, GameData::PLAYER1_SPRITE_INDEX, 20, 20, true, 0.0f, 0.0f);
	player.setPhantom(false);
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
	//mobileTilesLayer.update(data);
	objectsLayer.update(data);
	//enemiesLayer.update(data);

	// TODO: Afegir els enemics 
	std::vector<Enemy> shit;
	player.update(data, viewport, getCollisionObjects(), staticTilesLayer.getCollisionMap(), shit);

	// Viewport
	viewport->updateWithPosition(player.getX(), player.getY());
}


/* Rendering */
void Level::render(GameData *data, Viewport *viewport)
{
	staticTilesLayer.render(data, viewport);
	mobileTilesLayer.render(data, viewport);
	objectsLayer.render(data, viewport);
	//enemiesLayer.render(data, viewport);
	player.render(data);
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
	return objectsLayer.getCollisionObjects();
	//TODO: afegir els enemics i el player!!
}