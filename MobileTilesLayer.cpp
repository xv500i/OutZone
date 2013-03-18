
#include "MobileTilesLayer.h"
#include <iostream>
#include <sstream>
#include <fstream>


const char* MobileTilesLayer::FILE_NAME_PREFIX = "level";
const char* MobileTilesLayer::FILE_NAME_SUFIX = "mobile";
const char* MobileTilesLayer::FILE_EXT = ".txt";

MobileTilesLayer::MobileTilesLayer(void) {}

MobileTilesLayer::~MobileTilesLayer(void) {}


/* Loading */
bool MobileTilesLayer::load(int level, GameData *data)
{
	setLevel(level);

	// Open the file
	std::stringstream ss;
	ss << FILE_NAME_PREFIX << level << FILE_NAME_SUFIX << FILE_EXT;
	std::ifstream file(ss.str());

	// Read the file
	std::string line;
	if (file.is_open()) {
		while (file.good()) {
			getline(file, line);

			// Read the tile info
			MobileTile tile;
			int i = 0;
			std::stringstream sstr(line);
			while (!sstr.eof()) {
				switch (i) {
				case 0: sstr >> tile.index; break;
				case 1:
					sstr >> tile.xStart;
					if (sstr.peek() == ',') sstr.ignore();
					sstr >> tile.yStart;
					tile.x = tile.xStart;
					tile.y = tile.yStart;
					break;
				case 2:
					sstr >> tile.xEnd;
					if (sstr.peek() == ',') sstr.ignore();
					sstr >> tile.yEnd;
					break;
				case 3:
					sstr >> tile.vx;
					if (sstr.peek() == ',') sstr.ignore();
					sstr >> tile.vy;
					break;
				case 4:
					sstr >> tile.width;
					if (sstr.peek() == ',') sstr.ignore();
					sstr >> tile.height;
					break;
				case 5:
					char loopChar;
					sstr >> loopChar;
					if (loopChar == 'T') tile.loop = true;
					else if (loopChar == 'F') tile.loop = false;
					break;
				default: break;
				}
				if (sstr.peek() == ' ') sstr.ignore();
				i++;
			}
			tile.type = data->getTileSheetTileType(getTileSheetIndex(), tile.index);
			map.push_back(tile);
		}
		file.close();
		return true;
	}
	else {
		std::cout << "Error carregant les tiles mobils del nivell " << level << std::endl;
		return false;
	}
}

/* Rendering */
void MobileTilesLayer::render(GameData *data) 
{
	for (std::vector<MobileTile>::iterator it = map.begin(); it != map.end(); it++) {
		renderTile(&(*it), data);
	}
}

void MobileTilesLayer::renderTile(MobileTile *tile, GameData *data)
{
	// Obtain the tile offset
	float tileOffsetX, tileOffsetY;
	data->getTileSheetTileOffset(getTileSheetIndex(), &tileOffsetX, &tileOffsetY);

	// Obtain the tile position inside the texture
	int s, t;
	data->getTileSheetTilePosition(getTileSheetIndex(), tile->index, &s, &t);
	float coordS = s*tileOffsetX;
	float coordT = t*tileOffsetY;

	// Compute the new position
	tile->x = tile->x + tile->vx;
	if (tile->x == tile->xEnd) {
		if (tile->loop) tile->vx *= -1.0f;
		else tile->vx = 0.0f;
	}
	else if (tile->x == tile->xStart) tile->vx *= -1;

	tile->y = tile->y + tile->vy;
	if (tile->y == tile->yEnd) {
		if (tile->loop) tile->vy *= -1.0f;
		else tile->vy = 0.0f;
	}
	else if (tile->y == tile->yStart) tile->vy *= -1;

	// Rendering
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, data->getTileSheetID(getTileSheetIndex()));
	glBegin(GL_QUADS);
		glTexCoord2f(coordS, coordT);
		glVertex2i(tile->x, tile->y);

		glTexCoord2f(coordS + tileOffsetX, coordT);
		glVertex2i(tile->x + tile->width, tile->y);

		glTexCoord2f(coordS + tileOffsetX, coordT + tileOffsetY);
		glVertex2i(tile->x + tile->width, tile->y - tile->height);

		glTexCoord2f(coordS, coordT + tileOffsetY);
		glVertex2i(tile->x, tile->y - tile->height);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}

/* Getters */
int MobileTilesLayer::getTileSheetIndex()	// TODO: Descomentar a mesura que s'afegeixin tileSheets
{
	int level = getLevel();
	switch (level) {
	case 1: return GameData::LEVEL1_MOBILETILES_INDEX;
	//case 2: return GameData::LEVEL2_MOBILETILES_INDEX;
	//case 3: return GameData::LEVEL3_MOBILETILES_INDEX;
	//case 4: return GameData::LEVEL4_MOBILETILES_INDEX;
	//case 5: return GameData::LEVEL5_MOBILETILES_INDEX;
	default: return -1;
	}
}
