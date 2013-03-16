
#pragma once

#include <vector>
#include "Layer.h"
#include "TileType.h"


struct MobileTile {
	int index;
	int x, y;			/* Actual position */
	int xStart, yStart;	/* Start position */
	int xEnd, yEnd;		/* End position */
	float vx, vy;		/* Velocity. Restriction: vx has to be a divisor of xEnd - xStart (same for vy) */
	int width, height;	/* Size */
	//int depth;
	TileType type;
	bool loop;			/* True = tile movement in loop (start-end-start-end...) */
};

class MobileTilesLayer : public Layer
{
private:
	/* File constants */
	const static char* FILE_NAME_PREFIX;
	const static char* FILE_NAME_SUFIX;
	const static char* FILE_EXT;

	std::vector<MobileTile> map;	/* Level mobile tiles array */

	void renderTile(MobileTile *tile, GameData *data);

public:
	MobileTilesLayer(void);
	~MobileTilesLayer(void);

	/* Loading */
	virtual bool load(int level, GameData *data);

	/* Rendering */
	virtual void render(GameData *data);
};

