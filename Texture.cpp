
#include "Texture.h"
#include <iostream>
#include <sstream>


Texture::Texture(void) {}

Texture::~Texture(void) {}


/* Loading */
bool Texture::load(const char *filename, const char *ext, int type, int wraps, int wrapt, int magf, int minf, bool mipmap)
{
	// Open the file
	std::stringstream ss;
	ss << filename << ext;
	corona::Image* img = corona::OpenImage(ss.str().c_str());

	int components;
	if (type == GL_RGB) components = 3;
	else if (type == GL_RGBA) components = 4;
    else return false;

	if (img == NULL) {
		std::cout << "Error carregant la textura " << filename << ext << std::endl;
		return false;
	}

	// Get the image width and height
	widthInPixels = img->getWidth();
	heightInPixels = img->getHeight();

	// Generate the texture
	glGenTextures(1, &id);				// Generate 1 texture name
	glBindTexture(GL_TEXTURE_2D, id);	// Active the texture id with the GL_TEXTURE_2D bound

	// Texture parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wraps);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapt);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magf);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minf);

	// Texture loading
	if (!mipmap) {
		glTexImage2D(GL_TEXTURE_2D, 0, components, widthInPixels, heightInPixels, 0, type, GL_UNSIGNED_BYTE, img->getPixels());
	}
	else {
		gluBuild2DMipmaps(GL_TEXTURE_2D, components, widthInPixels, heightInPixels, type, GL_UNSIGNED_BYTE, img->getPixels());
	}
	return true;
}

/* Getters */
int Texture::getID() 
{
	return id;
}
	
void Texture::getSizeInPixels(int *width, int *height)
{
	*width = this->widthInPixels;
	*height = this->heightInPixels;
}