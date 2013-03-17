
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
	bool first = true;
	std::string line;
	if (file.is_open()) {
		while (file.good()) {
			getline(file, line);
			// Read the tile size
			if (first) {
				std::stringstream sstr(line.substr(line.find(' ')));
				sstr >> tileWidthInPixels;
				if (sstr.peek() == ',') sstr.ignore();
				sstr >> tileHeightInPixels;
				first = false;
			}
			// Read the tile position
			else {
				std::stringstream sstr(line);
				unsigned int pos; 
				int x, y;
				char tileTypeID;
				sstr >> pos;
				if (sstr.peek() == ' ') sstr.ignore();
				sstr >> x;
				if (sstr.peek() == ',') sstr.ignore();
				sstr >> y;
				if (sstr.peek() == ' ') 
				sstr >> tileTypeID;

				// Store the tile info
				std::pair<int, int> position(x, y);
				if (tileInfo.size() < pos + 1) tileInfo.resize(pos + 1);
				tileInfo[pos].position = position;

				switch (tileTypeID) {
				case LAND_ID: tileInfo[pos].type = LAND; break;
				case WALL_ID: tileInfo[pos].type = WALL; break;
				case HOLE_ID: tileInfo[pos].type = HOLE; break;
				default: break;
				}
			}
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
	*x = tileInfo[tileIndex].position.first;
	*y = tileInfo[tileIndex].position.second;
}

TileType TileSheet::getTileType(int tileIndex)
{
	return tileInfo[tileIndex].type;
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