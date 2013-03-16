
#pragma once

#include <vector>
#include "Layer.h"
#include "TileType.h"


struct Tile {
	int index;
	TileType type;
};

class LevelLayer : public Layer
{
private:
	/* File constants */
	const static char* FILE_NAME_PREFIX;
	const static char* FILE_EXT;

	/* Tile constants */
	const static int TILE_HEIGHT_IN_PIXELS = 32;
	const static int TILE_WIDTH_IN_PIXELS = 32;

	int widthInTiles;		/* Level width in tiles */
	int heightInTiles;		/* Level height in tiles */
	std::vector<Tile> map;	/* Level tiles array */

	void renderTile(int tileIndex, int posX, int posY, GameData *data);

public:
	LevelLayer(void);
	~LevelLayer(void);

	/* Loading */
	virtual bool load(int level, GameData *data);

	/* Rendering */
	virtual void render(GameData *data);

	/* Getters */
	void getSizeInTiles(int *width, int *height);
	void getSizeInPixels(int *width, int *height);
	void getTileSizeInPixels(int *width, int *height);
};

