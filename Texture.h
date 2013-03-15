
#pragma once
#pragma comment(lib, "corona")

#include <gl/glut.h>
#include <corona.h>


class Texture
{
private:
	unsigned int id;		/* Texture identifier */
	int widthInPixels;		/* Image width in pixels */
	int heightInPixels;		/* Image height in pixels */

public:
	Texture(void);
	~Texture(void);

	/* Loading */
	bool load(const char *filename, const char *ext, int type = GL_RGBA, int wraps = GL_REPEAT, 
			  int wrapt = GL_REPEAT, int magf = GL_NEAREST, int minf = GL_NEAREST, bool mipmap = false);

	/* Getters */
	int getID();
	void getSizeInPixels(int *width, int *height);
};

