
#pragma once

#include <vector>
#include "Texture.h"
#include "TileType.h"


struct TileInfo {
	std::pair<int, int> position;
	TileType type;
};

class Sprite : public Texture
{
private:
	/* File constants */
	const static char* DESCRIPTOR_FILE_EXT;

	int tileWidthInPixels;		/* Tile width in pixels */
	int tileHeightInPixels;		/* Tile height in pixels */
	float tileOffsetX;			/* Tile offset of X axis */
	float tileOffsetY;			/* Tile offset of Y axis */
	std::vector<TileInfo> tileInfo;		/* Tile positions inside the texture and type*/

	bool loadDescriptionFile(const char *filename);

public:
	Sprite(void);
	~Sprite(void);

	/* Loading */
	bool load(const char *filename, const char *ext, int type = GL_RGBA, int wraps = GL_REPEAT, 
			  int wrapt = GL_REPEAT, int magf = GL_NEAREST, int minf = GL_NEAREST, bool mipmap = false);

	/* Getters */
	void getTilePosition(int tileIndex, int *x, int *y);
	TileType getTileType(int tileIndex);
	void getTileSizeInPixels(int *width, int *height);
	void getTileOffset(float *offsetX, float *offsetY);
};

