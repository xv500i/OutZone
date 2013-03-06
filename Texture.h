
#pragma once
#pragma comment(lib, "corona")

#include <gl/glut.h>
#include <corona.h>
#include <vector>


class Texture
{
private:
	const static char* DESCR_FILE_EXT;
	const static char DESCR_FILE_DELIMITATOR = ' ';

	GLuint id;			/* Texture identifier */
	int width;			/* Image width */
	int height;			/* Image height */
	int tileWidth;		/* Tile width */
	int tileHeight;		/* Tile height */
	float tileOffsetX;	/* Tile offset of X axis */
	float tileOffsetY;	/* Tile offset of Y axis */
	std::vector<std::pair<int, int>> tilePosition;	/* Tile positions inside the texture */

	bool loadDescriptionFile(const char *filename);

public:
	Texture(void);
	~Texture(void);

	/* Getters */
	int getID();
	void getTilePosition(int tile, int *s, int *t);
	void getTileSize(int *width, int *height);
	void getTileOffset(float *offsetX, float *offsetY);
	void getSize(int *width, int *heigth);

	/* Loading */
	bool load(const char *filename, const char *ext, int type = GL_RGBA, int wraps = GL_REPEAT, 
			  int wrapt = GL_REPEAT, int magf = GL_NEAREST, int minf = GL_NEAREST, bool mipmap = false);
};

