
#pragma once

#include "StaticTilesLayer.h"
#include "MobileTilesLayer.h"
#include "ObjectsLayer.h"


class Level
{
private:
	int levelNumber;
	StaticTilesLayer staticTilesLayer;
	MobileTilesLayer mobileTilesLayer;
	ObjectsLayer objectsLayer;

public:
	Level();
	Level(int levelNumber);
	~Level(void);

	/* Loading */
	bool load(GameData *data);

	/* Updating */
	void update(GameData *data, Viewport *viewport);

	/* Rendering */
	void render(GameData *data, Viewport *viewport);

	/* Getters */
	void getSizeInPixels(int *width, int *height);
	void getSizeInTiles(int *width, int *height);
	void getTileSizeInPixels(int *width, int *height);
};

