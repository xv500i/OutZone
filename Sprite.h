
#pragma once

#include <vector>
#include "Texture.h"
#include "SpriteAction.h"


struct KeyFrame {
	int frameId;		/* The frame identifier */
	int duration;		/* Duration of this frame inside the animation */
	int tx, ty;			/* Translation performed by the object during this frame */
	float angle;		/* Rotation performed by the object during this frame */
};

struct Animation {
	std::vector<KeyFrame> animation;	/* The keyframes that conforms the animation */
	bool loop;							/* If true, the keyframes start all over again when the animation finish */
};

struct Frame {
	int s, t;							/* Frame texture coords */
	int width, height;					/* Frame size */
	int widthToRender, heightToRender;	/* Frame size used to render the frame */
};

class Sprite : public Texture
{
private:
	/* File constants */
	const static char* DESCRIPTOR_FILE_EXT;

	std::vector<Frame> frames;			/* Contains all the sprite frames */
	std::vector<Animation> animations;	/* Contains all the animations */

	bool loadDescriptionFile(const char *filename);

public:
	Sprite(void);
	~Sprite(void);

	/* Loading */
	bool load(const char *filename, const char *ext, int type = GL_RGBA, int wraps = GL_REPEAT, 
			  int wrapt = GL_REPEAT, int magf = GL_NEAREST, int minf = GL_NEAREST, bool mipmap = false);

	/* Getters */
	void getFrameInfo(int animationIndex, int frameIndex, int *s, int *t, int *width, int *height, int *widthToRender, int *heightToRender);
	int getFrameDuration(int animationIndex, int frameIndex);
	void getFrameTranslation(int animationIndex, int frameIndex, int *tx, int *ty);
	float getFrameRotation(int animationIndex, int frameIndex);
	int getAnimationNumFrames(int animationIndex);
	bool isAnimationLoop(int animationIndex);
};