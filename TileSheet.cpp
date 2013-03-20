
#include "TileSheet.h"
#include <iostream>
#include <sstream>
#include <fstream>


const char* TileSheet::DESCRIPTOR_FILE_EXT = ".txt";

TileSheet::TileSheet(void) {}

TileSheet::~TileSheet(void) {}


/* Loading */
bool TileSheet::load(const char *filename, const char *ext, int type, int wraps, int wrapt, int magf, int minf, bool mipmap)
{
	bool b = Texture::load(filename, ext, type, wraps, wrapt, magf, minf, mipmap);
	if (!b) return false;
	return loadDescriptionFile(filename);
}

bool TileSheet::loadDescriptionFile(const char *filename)
{
	// Open the file
	std::stringstream ss;
	ss << filename << DESCRIPTOR_FILE_EXT;
	std::ifstream file(ss.str());

	// Read the file
	std::string line;
	if (file.is_open()) {
		while (file.good()) {
			getline(file, line);
			// Read the tile size
			if (line.find("tilewidth") != std::string::npos) tileWidthInPixels = atoi(line.substr(line.find("=") + 1).c_str());
			else if (line.find("tileheight") != std::string::npos) tileHeightInPixels = atoi(line.substr(line.find("=") + 1).c_str());
		}
		// Compute the tile offset
		int width, height;
		getSizeInPixels(&width, &height);
		tileOffsetX = 1.0f/((float)width/(float)tileWidthInPixels);
		tileOffsetY = 1.0f/((float)height/(float)tileHeightInPixels);

		file.close();
		return true;
	}
	else {
		std::cout << "Error carregant el fitxer de descripcio del tilesheet " << filename << std::endl;
		return false;
	}
}

/* Getters */
void TileSheet::getTilePosition(int tileIndex, int *x, int *y)
{
	int index = tileIndex - 1;	// tileIndex starts with 1, not 0

	// Compute widthInTiles
	int widthInPixels, heightInPixels;
	getSizeInPixels(&widthInPixels, &heightInPixels);
	int widthInTiles = widthInPixels/tileWidthInPixels;

	*x = index%widthInTiles;
	*y = index/widthInTiles;
}

void TileSheet::getTileSizeInPixels(int *width, int *height)
{
	*width = tileWidthInPixels;
	*height = tileHeightInPixels;
}

void TileSheet::getTileOffset(float *offsetX, float *offsetY)
{
	*offsetX = tileOffsetX;
	*offsetY = tileOffsetY;
}