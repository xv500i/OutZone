
#pragma once

#include <vector>
#include <fstream>
#include "Layer.h"
#include "TileType.h"


struct Tile {
	int index;
	TileType type;
};

class StaticTilesLayer : public Layer
{
private:
	/* File constants */
	const static char* FILE_NAME_PREFIX;
	const static char* FILE_EXT;

	int widthInTiles;		/* Level width in tiles */
	int heightInTiles;		/* Level height in tiles */
	int tileWidthInPixels;	/* Tile width in pixels */
	int tileHeightInPixels;	/* Tile height in pixels */
	std::vector<Tile> backgroundLayer;	/* Background layer tiles array */
	std::vector<Tile> hoverLayer;		/* Hover layer tiles array */

	/* Loading */
	bool loadHeader(std::ifstream &file);
	bool loadCollisionLayer(std::ifstream &file);
	bool loadBackgroundLayer(std::ifstream &file);
	bool loadHoverLayer(std::ifstream &file);

	void renderTile(int tileIndex, int posX, int posY, int depth, GameData *data);
	int getTileSheetIndex();

public:
	StaticTilesLayer(void);
	~StaticTilesLayer(void);

	/* Loading */
	virtual bool load(int level, GameData *data);

	/* Rendering */
	virtual void render(GameData *data);

	/* Getters */
	void getSizeInTiles(int *width, int *height);
	void getSizeInPixels(int *width, int *height);
	void getTileSizeInPixels(int *width, int *height);
};

