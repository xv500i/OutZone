
#pragma once

#include <vector>
#include "Layer.h"
#include "GameObject.h"


class ObjectsLayer : public Layer 
{
private:
	/***** File estructure *****
	x,y,width,height,spriteIndex
	x,y,width,height,spriteIndex
	...
	x = x position IN TILES
	y = y position IN TILES
	width = object width
	height = object height
	spriteIndex = index of the sprite used by this object
	****************************/

	/* File constants */
	const static char* FILE_NAME_PREFIX;
	const static char* FILE_NAME_SUFIX;
	const static char* FILE_EXT;

	/* Tile size constants */
	const static int TILE_WIDTH_IN_PIXELS = 32;
	const static int TILE_HEIGHT_IN_PIXELS = 32;

	std::vector<GameObject> objects;

public:
	ObjectsLayer(void);
	~ObjectsLayer(void);

	/* Loading */
	virtual bool load(int level, GameData *data);

	/* Updating */
	virtual void update(GameData *data);

	/* Rendering */
	virtual void render(GameData *data, Viewport *viewport);
};

