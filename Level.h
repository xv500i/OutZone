
#pragma once

#include <vector>
#include "GameData.h"


enum TileType {
	LAND,
	WALL,
	HOLE
};

struct Tile {
	int index;
	TileType type;
};

class Level
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
	std::vector<Tile> map;	/* Level map */

	void renderTile(int tileIndex, int posX, int posY, GameData *data);

public:
	Level(void);
	~Level(void);

	/* Loading */
	bool load(int level);

	/* Rendering */
	void render(GameData *data);

	/* Getters */
	void getSizeInTiles(int *width, int *height);
	void getTileSizeInPixels(int *width, int *height);
};

