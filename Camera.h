
#pragma once

#include <gl/glut.h>
#include "Scene.h"


class Camera
{
private:
	const static float Z_NEAR;
	const static float Z_FAR;

	/* Orthogonal camera */
	float left;		/* Orthogonal camera left parameter */
	float right;	/* Orthogonal camera right parameter */
	float bottom;	/* Orthogonal camera bottom parameter */
	float top;		/* Orthogonal camera top parameter */

public:
	Camera(void);
	~Camera(void);

	/* Orthogonal camera */
	void initOrtho(float left, float right, float bottom, float top);
	void updateOrtho(float dX, float dY, Scene *scene);
	void loadOrtho();
};

