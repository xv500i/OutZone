
#pragma once

#include <gl/glut.h>


class Viewport
{
private:
	/* Orthogonal camera */
	const static float ZNEAR;
	const static float ZFAR;

	float left;			/* Viewport left parameter */
	float top;			/* Viewport top parameter */
	float width;		/* Viewport width */
	float height;		/* Viewport height */

	float maxTop;		/* Viewport max top */
	float minBottom;	/* Viewport min bottom */
	float minLeft;		/* Viewport min left */
	float maxRight;		/* Viewport max right */ 

	void defineOrthogonalCamera();

public:
	Viewport(void);
	~Viewport(void);

	/* Viewport lifetime */
	void init(float left, float top, float width, float height);
	void updateWithPosition(int x, int y, bool topLocked);

	/* Getters */
	float getLeft();
	float getTop();
	float getWidth();
	float getHeight();

	/* Setters */
	bool setLimits(float minLeft, float maxTop, float maxRight, float minBottom);
};

