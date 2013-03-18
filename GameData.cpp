
#include "GameData.h"


const char* GameData::TILESHEET_EXT = ".png";
const char* GameData::SPRITE_EXT = ".png";

GameData::GameData(void) 
{
	tileSheets = std::vector<TileSheet>(NUM_TILESHEETS);
	sprites = std::vector<Sprite>(NUM_SPRITES);
}

GameData::~GameData(void) {}


/* Tile Sheets */
bool GameData::loadTileSheets()
{
	const char* filenames[NUM_TILESHEETS] = {"pokemon", "pokemon3"}; 
	for (unsigned int i = 0; i < tileSheets.size(); i++) {
		bool b = tileSheets[i].load(filenames[i], TILESHEET_EXT);
		if (!b) return false;
	}
	return true;
}

int GameData::getTileSheetID(int tileSheetIndex)
{
	return tileSheets[tileSheetIndex].getID();
}

void GameData::getTileSheetTilePosition(int tileSheetIndex, int tileIndex, int *x, int *y)
{
	tileSheets[tileSheetIndex].getTilePosition(tileIndex, x, y);
}

TileType GameData::getTileSheetTileType(int tileSheetIndex, int tileIndex)
{
	return tileSheets[tileSheetIndex].getTileType(tileIndex);
}

void GameData::getTileSheetTileSizeInPixels(int tileSheetIndex, int *width, int *height)
{
	tileSheets[tileSheetIndex].getTileSizeInPixels(width, height);
}

void GameData::getTileSheetTileOffset(int tileSheetIndex, float *offsetX, float *offsetY)
{
	tileSheets[tileSheetIndex].getTileOffset(offsetX, offsetY);
}

void GameData::getTileSheetSizeInPixels(int tileSheetIndex, int *width, int *height)
{
	tileSheets[tileSheetIndex].getSizeInPixels(width, height);
}


/* Sprites */
bool GameData::loadSprites()
{
	const char* filenames[NUM_SPRITES] = {"ContraPlayer1", "ContraPlayer2"}; 
	for (unsigned int i = 0; i < sprites.size(); i++) {
		bool b = sprites[i].load(filenames[i], SPRITE_EXT);
		if (!b) return false;
	}
	return true;
}

int GameData::getSpriteID(int spriteIndex)
{
	return sprites[spriteIndex].getID();
}

void GameData::getSpriteSizeInPixels(int spriteIndex, int *width, int *height)
{
	sprites[spriteIndex].getSizeInPixels(width, height);
}