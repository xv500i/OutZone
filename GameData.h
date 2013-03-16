
#pragma once

#include <vector>
#include "Sprite.h"


class GameData
{
private:
	/* Sprites */
	const static int NUM_SPRITES = 2;	// TODO: modificar depenent del numero de sprites carregats
	const static char* SPRITE_EXT;

	std::vector<Sprite> sprites;	/* All loaded sprites */

public:
	/* Sprite indexes */	// TODO: afegir indexs de tots els sprites carregats
	const static int LEVEL1_TILES_INDEX = 0;
	const static int LEVEL1_MOBILETILES_INDEX = 1;

	GameData(void);
	~GameData(void);

	/* Sprites */
	bool loadSprites();
	int getSpriteID(int spriteIndex);
	void getSpriteTilePosition(int spriteIndex, int tileIndex, int *x, int *y);
	TileType getSpriteTileType(int spriteIndex, int tileIndex);
	void getSpriteTileSizeInPixels(int spriteIndex, int *width, int *height);
	void getSpriteTileOffset(int spriteIndex, float *offsetX, float *offsetY);
	void getSpriteSizeInPixels(int spriteIndex, int *width, int *height);
};