
#pragma once

#include "Texture.h"


class GameData
{
private:
	const static int NUM_TEX = 1;

	Texture textures[NUM_TEX];	/* Textures array */

public:
	/* Resources */
	const static char* TEX_EXT;
	const static int TILES_TEX_ID = 0;
	const static char* TILES_TEX_FILENAME;

	GameData(void);
	~GameData(void);

	/* Textures */
	int getTextureID(int texType);
	void getTextureTilePosition(int texType, int tile, int *s, int *t);
	void getTextureTileSize(int texType, int *width, int *height);
	void getTextureTileOffset(int texType, float *offsetX, float *offsetY);
	void getTextureSize(int texType, int *width, int *height);
	bool loadTexture(int texType, const char *filename, const char *ext, int type = GL_RGBA);
};

