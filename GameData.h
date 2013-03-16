
#pragma once

#include <vector>
#include "TileSheet.h"


class GameData
{
private:
	/* Sprites */
	const static int NUM_TILESHEETS = 2;	// TODO: modificar depenent del numero de sprites carregats
	const static char* TILESHEET_EXT;

	std::vector<TileSheet> tileSheets;	/* All loaded tile sheets */

public:
	/* TileSheet indexes */	// TODO: afegir indexs de tots els sprites carregats
	const static int LEVEL1_TILES_INDEX = 0;
	const static int LEVEL1_MOBILETILES_INDEX = 1;

	GameData(void);
	~GameData(void);

	/* Sprites */
	bool loadTileSheets();
	int getTileSheetID(int tileSheetIndex);
	void getTileSheetTilePosition(int tileSheetIndex, int tileIndex, int *x, int *y);
	TileType getTileSheetTileType(int tileSheetIndex, int tileIndex);
	void getTileSheetTileSizeInPixels(int tileSheetIndex, int *width, int *height);
	void getTileSheetTileOffset(int tileSheetIndex, float *offsetX, float *offsetY);
	void getTileSheetSizeInPixels(int tileSheetIndex, int *width, int *height);
};