
#include "Texture.h"
#include <iostream>
#include <sstream>
#include <fstream>


const char* Texture::DESCR_FILE_EXT = ".txt";

Texture::Texture(void)
{
}

Texture::~Texture(void)
{
}

/* Getters */
int Texture::getID() 
{
	return id;
}

void Texture::getTilePosition(int tile, int *s, int *t)
{
	*s = tilePosition[tile - 1].first;
	*t = tilePosition[tile - 1].second;
}

void Texture::getTileSize(int *width, int *height)
{
	*width = tileWidth;
	*height = tileHeight;
}

void Texture::getTileOffset(float *offsetX, float *offsetY)
{
	*offsetX = tileOffsetX;
	*offsetY = tileOffsetY;
}

void Texture::getSize(int *width, int *height)
{
	*width = this->width;
	*height = this->height;
}

/* Loading */
bool Texture::load(const char *filename, const char *ext, int type, int wraps, int wrapt, int magf, int minf, bool mipmap)
{
	corona::Image* img;
	int components;
	
	// Open the file
	std::stringstream ss;
	ss << filename << ext;
	img = corona::OpenImage(ss.str().c_str());

	if (type == GL_RGB) components = 3;
	else if (type == GL_RGBA) components = 4;
    else return false;

	if (img == NULL) {
		std::cout << "Error carregant la textura " << filename << std::endl;
		return false;
	}

	// Get the image width and height
	width = img->getWidth();
	height = img->getHeight();

	glGenTextures(1, &id);				// Generate 1 texture name
	glBindTexture(GL_TEXTURE_2D, id);	// Active the texture id with the selected bound

	// Texture parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wraps);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapt);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magf);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minf);

	// Texture loading
	if (!mipmap) {
		glTexImage2D(GL_TEXTURE_2D, 0, components, width, height, 0, type, GL_UNSIGNED_BYTE, img->getPixels());
	}
	else {
		gluBuild2DMipmaps(GL_TEXTURE_2D, components, width, height, type, GL_UNSIGNED_BYTE, img->getPixels());
	}

	return loadDescriptionFile(filename);
}

bool Texture::loadDescriptionFile(const char *filename)
{
	// Open the file
	std::stringstream ss;
	ss << filename << DESCR_FILE_EXT;
	std::ifstream file(ss.str());

	// Read the file
	bool first = true;
	std::string line;
	if (file.is_open()) {
		while (file.good()) {
			getline(file, line);

			// Read the tile size and tile positions
			std::stringstream sstr(line.substr(line.find(DESCR_FILE_DELIMITATOR)));
			int x, y;
			sstr >> x;
			if (sstr.peek() == ',') sstr.ignore();
			sstr >> y;
			if (first) {
				tileWidth = x;
				tileHeight = y;
				first = false;
			}
			else {
				std::pair<int, int> pos(x, y);
				tilePosition.push_back(pos);
			}
		}
		// Compute the tile offset
		tileOffsetX = 1.0f/((float)width/(float)tileWidth);
		tileOffsetY = 1.0f/((float)height/(float)tileHeight);

		file.close();
		return true;
	}
	else {
		std::cout << "Error carregant el fitxer de descripcio de la textura " << filename << std::endl;
		return false;
	}
}