
#include "Sprite.h"
#include <iostream>
#include <sstream>
#include <fstream>


const char* Sprite::DESCRIPTOR_FILE_EXT = ".txt";

Sprite::Sprite(void) 
{
	currentAnimationIndex = -1;
	currentAction = STATIC;
}

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
	if (file.is_open()) {
		while (file.good()) {
			std::string line;
			getline(file, line);
			std::stringstream sstr(line);
			char lineType;
			sstr >> lineType;

			// Read frame info
			if (lineType == 'F') {
				Frame frame;
				if (sstr.peek() == ' ') sstr.ignore();
				sstr >> frame.s;
				if (sstr.peek() == ',') sstr.ignore();
				sstr >> frame.t;
				if (sstr.peek() == ' ') sstr.ignore();
				sstr >> frame.width;
				if (sstr.peek() == ',') sstr.ignore();
				sstr >> frame.height;
				frames.push_back(frame);
			}
			// Read animation info
			else if (lineType == 'A') {
				std::vector<KeyFrame> animation;
				while (sstr.peek() == ' ') {
					sstr.ignore();
					KeyFrame keyFrame;
					sstr >> keyFrame.frameId;
					if (sstr.peek() == ',') sstr.ignore();
					sstr >> keyFrame.duration;
					if (sstr.peek() == ',') sstr.ignore();
					sstr >> keyFrame.tx;
					if (sstr.peek() == ',') sstr.ignore();
					sstr >> keyFrame.ty;
					animation.push_back(keyFrame);
				}
				animations.push_back(animation);
			}
		}
		file.close();
		return true;
	}
	else {
		std::cout << "Error carregant el fitxer de descripcio de l'sprite " << filename << std::endl;
		return false;
	}
}

/* Getters */
void Sprite::getFrameInfo(PlayerAction action, int *s, int *t, int *width, int *height, float *offsetX, float *offsetY)
{
	if (currentAction == action) currentAnimationIndex++;
	else currentAnimationIndex = 0;

	std::vector<KeyFrame> animation = animations.at(action);
	KeyFrame keyFrame = animation.at(currentAnimationIndex);
	Frame frame = frames.at(keyFrame.frameId);

	int textureWidth, textureHeight;
	getSizeInPixels(&textureWidth, &textureHeight);

	*s = frame.s/textureWidth;
	*t = frame.t/textureHeight;
	*width = frame.width;
	*height = frame.height;
	*offsetX = frame.width/textureWidth;
	*offsetY = frame.height/textureHeight;
}