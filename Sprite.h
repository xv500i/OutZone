
#pragma once

#include "Texture.h"
#include <vector>


class Sprite : public Texture
{
private:
	const static char* DESCRIPTOR_FILE_EXT;
	const static char DESCRIPTOR_FILE_DELIMITATOR = ' ';

	int tileWidthInPixels;		/* Tile width */
	int tileHeightInPixels;		/* Tile height */
	float tileOffsetX;			/* Tile offset of X axis */
	float tileOffsetY;			/* Tile offset of Y axis */
	std::vector<std::pair<int, int>> tilePosition;	/* Tile positions inside the texture */

	bool loadDescriptionFile(const char *filename);

public:
	Sprite(void);
	~Sprite(void);

	/* Loading */
	bool load(const char *filename, const char *ext, int type = GL_RGBA, int wraps = GL_REPEAT, 
			  int wrapt = GL_REPEAT, int magf = GL_NEAREST, int minf = GL_NEAREST, bool mipmap = false);

	/* Getters */
	void getTilePosition(int tile, int *x, int *y);
	void getTileSizeInPixels(int *width, int *height);
	void getTileOffset(float *offsetX, float *offsetY);
};

