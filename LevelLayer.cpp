
#include "LevelLayer.h"
#include <iostream>
#include <sstream>
#include <fstream>


const char* LevelLayer::FILE_NAME_PREFIX = "level";
const char* LevelLayer::FILE_EXT = ".txt";

LevelLayer::LevelLayer(void) {}

LevelLayer::~LevelLayer(void) {}


/* Loading */
bool LevelLayer::load(int level, GameData *data)
{
	setLevel(level);
	widthInTiles = 0;
	heightInTiles = 0;

	// Open the file
	std::stringstream ss;
	ss << FILE_NAME_PREFIX << level << FILE_EXT;
	std::ifstream file(ss.str());

	// Read the file
	bool first = true;
	std::string line;
	if (file.is_open()) {
		while (file.good()) {
			getline(file, line);

			// Update level height
			heightInTiles++;

			// Read the tile info
			int tileIndex;
			std::stringstream sstr(line);
			while (sstr >> tileIndex) {
				Tile tile;
				tile.index = tileIndex;
				tile.type = data->getTileSheetTileType(getTileSheetIndex(), tileIndex);
				map.push_back(tile);
				if (sstr.peek() == ',') sstr.ignore();
				// Update level width
				if (first) widthInTiles++;
			}
			first = false;
		}
		file.close();
		return true;
	}
	else {
		std::cout << "Error carregant el nivell " << level << std::endl;
		return false;
	}
}

/* Rendering */
void LevelLayer::render(GameData *data) 
{
	for (int i = 0; i < heightInTiles; i++) {
		for (int j = 0; j < widthInTiles; j++) {
			renderTile(map[i*widthInTiles + j].index, TILE_WIDTH_IN_PIXELS*j, TILE_HEIGHT_IN_PIXELS*i, data);
		}
	}
}

void LevelLayer::renderTile(int tileIndex, int posX, int posY, GameData *data) 
{
	// Obtain the tile offset
	float tileOffsetX, tileOffsetY;
	data->getTileSheetTileOffset(getTileSheetIndex(), &tileOffsetX, &tileOffsetY);	

	// Obtain the tile position inside the texture
	int s, t;
	data->getTileSheetTilePosition(getTileSheetIndex(), tileIndex, &s, &t);
	float coordS = s*tileOffsetX;
	float coordT = t*tileOffsetY;

	// Rendering
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, data->getTileSheetID(GameData::LEVEL1_TILES_INDEX));	// TODO: Obtenir depenent del nivell!
	glBegin(GL_QUADS);
		glTexCoord2f(coordS, coordT);
		glVertex2i(posX, heightInTiles*TILE_HEIGHT_IN_PIXELS - posY);

		glTexCoord2f(coordS + tileOffsetX, coordT);
		glVertex2i(posX + TILE_WIDTH_IN_PIXELS, heightInTiles*TILE_HEIGHT_IN_PIXELS - posY);

		glTexCoord2f(coordS + tileOffsetX, coordT + tileOffsetY);
		glVertex2i(posX + TILE_WIDTH_IN_PIXELS, heightInTiles*TILE_HEIGHT_IN_PIXELS - (posY + TILE_HEIGHT_IN_PIXELS));

		glTexCoord2f(coordS, coordT + tileOffsetY);
		glVertex2i(posX, heightInTiles*TILE_HEIGHT_IN_PIXELS - (posY + TILE_HEIGHT_IN_PIXELS));
	glEnd();
	glDisable(GL_TEXTURE_2D);
}

/* Getters */
void LevelLayer::getSizeInTiles(int *width, int *height)
{
	*width = widthInTiles;
	*height = heightInTiles;
}

void LevelLayer::getSizeInPixels(int *width, int *height)
{
	int widthInTiles, heightInTiles;
	int tileWidth, tileHeight;
	getSizeInTiles(&widthInTiles, &heightInTiles);
	getTileSizeInPixels(&tileWidth, &tileHeight);
	*width = widthInTiles*tileWidth;
	*height = heightInTiles*tileHeight;
}

void LevelLayer::getTileSizeInPixels(int *width, int *height)
{
	*width = TILE_WIDTH_IN_PIXELS;
	*height = TILE_HEIGHT_IN_PIXELS;
}

int LevelLayer::getTileSheetIndex()	// TODO: Descomentar a mesura que s'afegeixin tileSheets
{
	int level = getLevel();
	switch (level) {
	case 1: return GameData::LEVEL1_TILES_INDEX;
	//case 2: return GameData::LEVEL2_TILES_INDEX;
	//case 3: return GameData::LEVEL3_TILES_INDEX;
	//case 4: return GameData::LEVEL4_TILES_INDEX;
	//case 5: return GameData::LEVEL5_TILES_INDEX;
	default: return -1;
	}
}