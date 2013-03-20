
#pragma once

#include <vector>
#include "Texture.h"


struct KeyFrame {
	int frameId;		/* The frame identifier */
	int duration;		/* Duration of this frame inside the animation */
	int tx, ty;			/* Translation performed by the object during this frame */
};

struct Frame {
	int s, t;			/* Frame texture coords */
	int width, height;	/* Frame size */
};

class Sprite : public Texture
{
private:
	/* File constants */
	const static char* DESCRIPTOR_FILE_EXT;

	std::vector<Frame> frames;						/* Contains all the sprite frames */
	std::vector<std::vector<KeyFrame>> animations;	/* Each vector contains the keyframes associated with an animation */

	bool loadDescriptionFile(const char *filename);

public:
	Sprite(void);
	~Sprite(void);

	/* Loading */
	bool load(const char *filename, const char *ext, int type = GL_RGBA, int wraps = GL_REPEAT, 
			  int wrapt = GL_REPEAT, int magf = GL_NEAREST, int minf = GL_NEAREST, bool mipmap = false);
};