
#include "GameData.h"


const char* GameData::TEX_EXT = ".png";
const char* GameData::TILES_TEX_FILENAME = "pokemon";

GameData::GameData(void)
{
}

GameData::~GameData(void)
{
}

/* Textures */
int GameData::getTextureID(int texType)
{
	return textures[texType].getID();
}

void GameData::getTextureTilePosition(int texType, int tile, int *s, int *t)
{
	textures[texType].getTilePosition(tile, s, t);
}

void GameData::getTextureTileSize(int texType, int *width, int *height)
{
	textures[texType].getTileSize(width, height);
}

void GameData::getTextureTileOffset(int texType, float *offsetX, float *offsetY)
{
	textures[texType].getTileOffset(offsetX, offsetY);
}

void GameData::getTextureSize(int texType, int *width, int *height)
{
	textures[texType].getSize(width, height);
}

bool GameData::loadTexture(int texType, const char *filename, const char *ext, int type)
{
	return textures[texType].load(filename, ext, type);
}
