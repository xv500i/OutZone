
#include "Sprite.h"
#include <iostream>
#include <sstream>
#include <fstream>


const char* Sprite::DESCRIPTOR_FILE_EXT = ".txt";

Sprite::Sprite(void) {}

Sprite::~Sprite(void) {}


/* Loading */
bool Sprite::load(const char *filename, const char *ext, int type, int wraps, int wrapt, int magf, int minf, bool mipmap)
{
	bool b = Texture::load(filename, ext, type, wraps, wrapt, magf, minf, mipmap);
	if (!b) return false;
	return loadDescriptionFile(filename);
}

bool Sprite::loadDescriptionFile(const char *filename)
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
				std::stringstream sstr(line.substr(line.find(DESCRIPTOR_FILE_DELIMITATOR)));
				sstr >> tileWidthInPixels;
				if (sstr.peek() == ',') sstr.ignore();
				sstr >> tileHeightInPixels;
				first = false;
			}
			// Read the tile position
			else {
				std::stringstream sstr(line);
				int pos, x, y;
				sstr >> pos;
				if (sstr.peek() == ' ') sstr.ignore();
				sstr >> x;
				if (sstr.peek() == ',') sstr.ignore();
				sstr >> y;
				std::pair<int, int> position(x, y);
				if (tilePosition.size() < pos + 1) tilePosition.resize(pos + 1);
				tilePosition[pos] = position;
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
		std::cout << "Error carregant el fitxer de descripcio de l'sprite " << filename << std::endl;
		return false;
	}
}

/* Getters */
void Sprite::getTilePosition(int tile, int *x, int *y)
{
	*x = tilePosition[tile].first;
	*y = tilePosition[tile].second;
}

void Sprite::getTileSizeInPixels(int *width, int *height)
{
	*width = tileWidthInPixels;
	*height = tileHeightInPixels;
}

void Sprite::getTileOffset(float *offsetX, float *offsetY)
{
	*offsetX = tileOffsetX;
	*offsetY = tileOffsetY;
}