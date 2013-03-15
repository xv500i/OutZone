
#include "Level.h"
#include <iostream>
#include <sstream>
#include <fstream>


const char* Level::FILE_NAME_PREFIX = "level";
const char* Level::FILE_EXT = ".txt";

Level::Level(void) {}

Level::~Level(void) {}


/* Loading */
bool Level::load(int level)
{
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
				tile.type = TileType::LAND; // TODO: obtenir el tile.type!
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
void Level::render(GameData *data) 
{
	for (int i = 0; i < heightInTiles; i++) {
		for (int j = 0; j < widthInTiles; j++) {
			renderTile(map[i*widthInTiles + j].index, TILE_WIDTH_IN_PIXELS*j, TILE_HEIGHT_IN_PIXELS*i, data);
		}
	}
}

void Level::renderTile(int tileIndex, int posX, int posY, GameData *data) 
{
	// Obtain the tile offset
	float tileOffsetX, tileOffsetY;
	data->getSpriteTileOffset(GameData::LEVEL1_TILES_INDEX, &tileOffsetX, &tileOffsetY);	// TODO: Obtenir depenent del nivell!

	// Obtain the tile position inside the texture
	int s, t;
	data->getSpriteTilePosition(GameData::LEVEL1_TILES_INDEX, tileIndex, &s, &t);	// TODO: Obtenir depenent del nivell!
	float coordS = s*tileOffsetX;
	float coordT = t*tileOffsetY;

	// Rendering
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, data->getSpriteID(GameData::LEVEL1_TILES_INDEX));
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
void Level::getSizeInTiles(int *width, int *height)
{
	*width = widthInTiles;
	*height = heightInTiles;
}

void Level::getTileSizeInPixels(int *width, int *height)
{
	*width = TILE_WIDTH_IN_PIXELS;
	*height = TILE_HEIGHT_IN_PIXELS;
}