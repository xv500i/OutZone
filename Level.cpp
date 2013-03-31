
#include "Level.h"


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
	return true;
}

/* Updating */
void Level::update(GameData *data, Viewport *viewport)
{
	//mobileTilesLayer.update();
	objectsLayer.update(data);
}

/* Rendering */
void Level::render(GameData *data, Viewport *viewport)
{
	staticTilesLayer.render(data, viewport);
	mobileTilesLayer.render(data, viewport);
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