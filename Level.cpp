
#include "Level.h"
#include <sstream>
#include <fstream>


const char* Level::FILE_NAME = "level";
const char* Level::FILE_EXT = ".txt";

Level::Level(void)
{
}

Level::~Level(void)
{
}

void Level::getSize(int *width, int *height)
{
	*width = levelWidth;
	*height = levelHeight;
}

/* Loading */
bool Level::load(int level)
{
	levelWidth = 0;
	levelHeight = 0;

	// Open the file
	std::stringstream ss;
	ss << FILE_NAME << level << FILE_EXT;
	std::ifstream file(ss.str());

	// Read the file
	bool first = true;
	std::string line;
	if (file.is_open()) {
		while (file.good()) {
			getline(file, line);

			// Update level size
			levelHeight++;

			int tileID;
			std::stringstream sstr(line);
			while (sstr >> tileID) {
				if (tileID == EMPTY_SPACE) map.push_back(0);
				else map.push_back(tileID);

				if (first) levelWidth++;
				if (sstr.peek() == ',') sstr.ignore();
			}
			if (first) first = false;
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
	for (int i = 0; i < levelHeight; i++) {
		for (int j = 0; j < levelWidth; j++) {
			renderTile(map[i*levelWidth + j], TILE_SIZE*j, TILE_SIZE*i, data);
		}
	}
}

void Level::renderTile(int tileID, int posX, int posY, GameData *data) 
{
	if (tileID != 0) {
		// TileOffset
		float tileOffsetX, tileOffsetY;
		data->getTextureTileOffset(GameData::TILES_TEX_ID, &tileOffsetX, &tileOffsetY);

		// Obtain the tile position inside the texture
		int s, t;
		data->getTextureTilePosition(GameData::TILES_TEX_ID, tileID, &t, &s);

		float coordS = s*tileOffsetX;
		float coordT = t*tileOffsetY;

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, data->getTextureID(GameData::TILES_TEX_ID));
		glBegin(GL_QUADS);
			glTexCoord2f(coordS, coordT);
			glVertex2i(posX, levelHeight*TILE_SIZE - posY);

			glTexCoord2f(coordS + tileOffsetX, coordT);
			glVertex2i(posX + TILE_SIZE, levelHeight*TILE_SIZE - posY);

			glTexCoord2f(coordS + tileOffsetX, coordT + tileOffsetY);
			glVertex2i(posX + TILE_SIZE, levelHeight*TILE_SIZE - (posY + TILE_SIZE));

			glTexCoord2f(coordS, coordT + tileOffsetY);
			glVertex2i(posX, levelHeight*TILE_SIZE - (posY + TILE_SIZE));
		glEnd();
		glDisable(GL_TEXTURE_2D);
	}
}