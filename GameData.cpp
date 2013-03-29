
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
	const char* filenames[NUM_TILESHEETS] = {"Level1Tileset"};	// TOCHANGE: afegir el nom dels tileSheets
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

void GameData::getTileSheetSizeInPixels(int tileSheetIndex, int *width, int *height)
{
	tileSheets[tileSheetIndex].getSizeInPixels(width, height);
}

void GameData::getTileSheetTilePosition(int tileSheetIndex, int tileIndex, int *x, int *y)
{
	tileSheets[tileSheetIndex].getTilePosition(tileIndex, x, y);
}

void GameData::getTileSheetTileSizeInPixels(int tileSheetIndex, int *width, int *height)
{
	tileSheets[tileSheetIndex].getTileSizeInPixels(width, height);
}

void GameData::getTileSheetTileOffset(int tileSheetIndex, float *offsetX, float *offsetY)
{
	tileSheets[tileSheetIndex].getTileOffset(offsetX, offsetY);
}


/* Sprites */
bool GameData::loadSprites()
{
	const char* filenames[NUM_SPRITES] = {"Player1", "Player2", "Fire", "Fire2"};	// TOCHANGE: afegir el nom dels sprites
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


/* Sprite instances */
int GameData::createSpriteInstance(int spriteIndex)
{
	SpriteInstance spriteInstance(&sprites[spriteIndex]);
	// TODO: Per millorar l'eficiència del vector, s'hauria de recorrer per trobar forats que hagin quedat buits
	spriteInstances.push_back(spriteInstance);
	return spriteInstances.size() - 1;
}

void GameData::removeSpriteInstance(int spriteInstanceIndex)
{
	// TODO: Per fer (per millorar eficiència)
}

void GameData::getSpriteFrameInfo(int spriteInstanceIndex, SpriteAction action, float *s, float *t, int *width, int *height, float *offsetX, float *offsetY)
{
	spriteInstances[spriteInstanceIndex].getFrameInfo(action, s, t, width, height, offsetX, offsetY);
}