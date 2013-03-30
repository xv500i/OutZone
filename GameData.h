
#pragma once

#include <vector>
#include "TileSheet.h"
#include "Sprite.h"
#include "SpriteInstance.h"


class GameData
{
private:
	/* TileSheets */
	const static int NUM_TILESHEETS = 1;	// TOCHANGE: modificar depenent del numero de tile sheets carregats
	const static char* TILESHEET_EXT;

	/* Sprites */
	const static int NUM_SPRITES = 4;		// TOCHANGE: modificar depenent del numero de sprites carregats
	const static char* SPRITE_EXT;

	std::vector<TileSheet> tileSheets;				/* All loaded tile sheets */
	std::vector<Sprite> sprites;					/* All loaded sprites */
	std::vector<SpriteInstance> spriteInstances;	/* All sprite instances of the loaded sprites */

public:
	/* TileSheet indexes */		// TOCHANGE: afegir indexs de tots els tile sheets carregats
	const static int LEVEL1_TILES_INDEX = 0;
	const static int LEVEL1_MOBILETILES_INDEX = 1;
	//const static int LEVEL2_TILES_INDEX = 2;
	//const static int LEVEL2_MOBILETILES_INDEX = 3;
	//...

	/* Sprite indexes */		// TOCHANGE: afegir indexs de tots els sprites carregats
	const static int PLAYER1_SPRITE_INDEX = 0;
	const static int PLAYER2_SPRITE_INDEX = 1;
	const static int FIRE_SPRITE_INDEX = 2;
	const static int FIRE2_SPRITE_INDEX = 3;
	//...

	GameData(void);
	~GameData(void);

	/* Tile Sheets */
	bool loadTileSheets();
	int getTileSheetID(int tileSheetIndex);
	void getTileSheetSizeInPixels(int tileSheetIndex, int *width, int *height);
	void getTileSheetTilePosition(int tileSheetIndex, int tileIndex, int *x, int *y);
	void getTileSheetTileSizeInPixels(int tileSheetIndex, int *width, int *height);
	void getTileSheetTileOffset(int tileSheetIndex, float *offsetX, float *offsetY);

	/* Sprites */
	bool loadSprites();
	int getSpriteID(int spriteIndex);
	void getSpriteSizeInPixels(int spriteIndex, int *width, int *height);

	/* Sprite instances */
	int createSpriteInstance(int spriteIndex);
	void removeSpriteInstance(int spriteInstanceIndex);
	void getSpriteFrameInfo(int spriteInstanceIndex, SpriteAction action, bool *finished, float *s, float *t, int *width, int *height, float *offsetX, float *offsetY);
};