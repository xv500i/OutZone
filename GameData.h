
#pragma once

#include <vector>
#include "TileSheet.h"


class GameData
{
private:
	/* TileSheets */
	const static int NUM_TILESHEETS = 2;	// TODO: modificar depenent del numero de tile sheets carregats
	const static char* TILESHEET_EXT;

	std::vector<TileSheet> tileSheets;	/* All loaded tile sheets */
	//std::vector<SpriteSheet> sprites;	/* All loaded sprite sheets */

public:
	/* TileSheet indexes */		// TODO: afegir indexs de tots els sprites carregats
	const static int LEVEL1_TILES_INDEX = 0;
	//const static int LEVEL1_TILES_INDEX = 2;
	//const static int LEVEL1_TILES_INDEX = 4;
	//const static int LEVEL1_TILES_INDEX = 6;
	//const static int LEVEL1_TILES_INDEX = 8;
	const static int LEVEL1_MOBILETILES_INDEX = 1;
	//const static int LEVEL1_MOBILETILES_INDEX = 3;
	//const static int LEVEL1_MOBILETILES_INDEX = 5;
	//const static int LEVEL1_MOBILETILES_INDEX = 7;
	//const static int LEVEL1_MOBILETILES_INDEX = 9;

	GameData(void);
	~GameData(void);

	/* Tile Sheets */
	bool loadTileSheets();
	int getTileSheetID(int tileSheetIndex);
	void getTileSheetTilePosition(int tileSheetIndex, int tileIndex, int *x, int *y);
	TileType getTileSheetTileType(int tileSheetIndex, int tileIndex);
	void getTileSheetTileSizeInPixels(int tileSheetIndex, int *width, int *height);
	void getTileSheetTileOffset(int tileSheetIndex, float *offsetX, float *offsetY);
	void getTileSheetSizeInPixels(int tileSheetIndex, int *width, int *height);
};