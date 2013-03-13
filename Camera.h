
#pragma once

#include <gl/glut.h>
#include "Scene.h"


class Camera
{
private:
	const static float Z_NEAR;	// = -1.0f;
	const static float Z_FAR;	// = 1.0f;

	/* Orthogonal camera */
	float left;		/* Orthogonal camera left parameter */
	float top;		/* Orthogonal camera top parameter */
	float width;	/* Orthogonal camera width parameter */
	float height;	/* Orthogonal camera height parameter */
	float orthoVX;	/* Orthogonal camera X velocity */
	float orthoVY;	/* Orthogonal camera Y velocity */

public:
	Camera(void);
	~Camera(void);

	/* Orthogonal camera */
	void initOrtho(float left, float top, float width, float height);
	void updateOrtho(long msec);
	void loadOrtho();
	void setOrthoVX(float newOrthoVX);
	void setOrthoVY(float newOrthoVY);
};

