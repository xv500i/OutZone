
#include "GameData.h"


const char* GameData::SPRITE_EXT = ".png";

GameData::GameData(void) 
{
	sprites = std::vector<Sprite>(NUM_SPRITES);
}

GameData::~GameData(void) {}


/* Sprites */
bool GameData::loadSprites()
{
	const char* filenames[NUM_SPRITES] = {"OutZoneLevel1"}; 
	for (int i = 0; i < sprites.size(); i++) {
		bool b = sprites[i].load(filenames[i], SPRITE_EXT);
		if (!b) return false;
	}
	return true;
}

int GameData::getSpriteID(int spriteIndex)
{
	return sprites[spriteIndex].getID();
}

void GameData::getSpriteTilePosition(int spriteIndex, int tileIndex, int *x, int *y)
{
	sprites[spriteIndex].getTilePosition(tileIndex, x, y);
}

void GameData::getSpriteTileSizeInPixels(int spriteIndex, int *width, int *height)
{
	sprites[spriteIndex].getTileSizeInPixels(width, height);
}

void GameData::getSpriteTileOffset(int spriteIndex, float *offsetX, float *offsetY)
{
	sprites[spriteIndex].getTileOffset(offsetX, offsetY);
}

void GameData::getSpriteSizeInPixels(int spriteIndex, int *width, int *height)
{
	sprites[spriteIndex].getSizeInPixels(width, height);
}