
#pragma once

#include <vector>
#include "Texture.h"


class TileSheet : public Texture
{
private:
	/* File constants */
	const static char* DESCRIPTOR_FILE_EXT;

	int tileWidthInPixels;		/* Tile width in pixels */
	int tileHeightInPixels;		/* Tile height in pixels */
	float tileOffsetX;			/* Tile offset of X axis */
	float tileOffsetY;			/* Tile offset of Y axis */

	bool loadDescriptionFile(const char *filename);

public:
	TileSheet(void);
	~TileSheet(void);

	/* Loading */
	bool load(const char *filename, const char *ext, int type = GL_RGBA, int wraps = GL_REPEAT, 
			  int wrapt = GL_REPEAT, int magf = GL_NEAREST, int minf = GL_NEAREST, bool mipmap = false);

	/* Getters */
	void getTilePosition(int tileIndex, int *x, int *y);
	void getTileSizeInPixels(int *width, int *height);
	void getTileOffset(float *offsetX, float *offsetY);
};

