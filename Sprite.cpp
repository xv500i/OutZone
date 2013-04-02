
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
				if (sstr.peek() == ' ') sstr.ignore();
				sstr >> frame.widthToRender;
				if (sstr.peek() == ',') sstr.ignore();
				sstr >> frame.heightToRender;
				frames.push_back(frame);
			}
			// Read animation info
			else if (lineType == 'A') {
				Animation anim;
				char animationType;
				sstr >> animationType;
				if (animationType == 'L') anim.loop = true;
				else anim.loop = false;
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
					if (sstr.peek() == ',') sstr.ignore();
					sstr >> keyFrame.angle;
					anim.animation.push_back(keyFrame);
				}
				animations.push_back(anim);
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
void Sprite::getFrameInfo(int animationIndex, int frameIndex, int *s, int *t, int *width, int *height, int *widthToRender, int *heightToRender)
{
	Frame frame = frames[animations[animationIndex].animation[frameIndex].frameId];
	*s = frame.s;
	*t = frame.t;
	*width = frame.width;
	*height = frame.height;
	*widthToRender = frame.widthToRender;
	*heightToRender = frame.heightToRender;
}

int Sprite::getFrameDuration(int animationIndex, int frameIndex)
{
	return animations[animationIndex].animation[frameIndex].duration;
}

void Sprite::getFrameTranslation(int animationIndex, int frameIndex, int *tx, int *ty)
{
	*tx = animations[animationIndex].animation[frameIndex].tx;
	*ty = animations[animationIndex].animation[frameIndex].ty;
}

float Sprite::getFrameRotation(int animationIndex, int frameIndex)
{
	return animations[animationIndex].animation[frameIndex].angle;
}

int Sprite::getAnimationNumFrames(int animationIndex)
{
	return animations[animationIndex].animation.size();
}

bool Sprite::isAnimationLoop(int animationIndex)
{
	return animations[animationIndex].loop;
}