
#pragma once

#include <vector>
#include "TileType.h"
#include "GameData.h"


struct MobileTile {
	int index;
	int xStart, yStart;	/* Start position */
	int xEnd, yEnd;		/* End position */
	float vx, vy;		/* Velocity */
	int width, height;	/* Size */
	int depth;
	TileType type;
	bool loop;			/* True = tile movement in loop (start-end-start-end...) */
};

class MobileTilesLayer
{
private:
	/* File constants */
	const static char* FILE_NAME_PREFIX;
	const static char* FILE_NAME_SUFIX;
	const static char* FILE_EXT;

	std::vector<MobileTile> map;	/* Level mobile tiles array */

	void renderTile(int tileIndex, int posX, int posY, GameData *data);

public:
	MobileTilesLayer(void);
	~MobileTilesLayer(void);

	/* Loading */
	bool load(int level, GameData *data);

	/* Rendering */
	void render(GameData *data);
};

