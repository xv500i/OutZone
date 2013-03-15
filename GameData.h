
#pragma once

#include <vector>
#include "Sprite.h"


class GameData
{
private:
	/* Sprites */
	const static int NUM_SPRITES = 1;
	const static char* SPRITE_EXT;

	std::vector<Sprite> sprites;	/* All loaded sprites */

public:
	/* Sprite indexes */
	const static int LEVEL1_TILES_INDEX = 0;

	GameData(void);
	~GameData(void);

	/* Sprites */
	bool loadSprites();
	int getSpriteID(int spriteIndex);
	void getSpriteTilePosition(int spriteIndex, int tileIndex, int *x, int *y);
	void getSpriteTileSizeInPixels(int spriteIndex, int *width, int *height);
	void getSpriteTileOffset(int spriteIndex, float *offsetX, float *offsetY);
	void getSpriteSizeInPixels(int spriteIndex, int *width, int *height);
};