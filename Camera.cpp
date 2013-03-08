
#include "Camera.h"


const float Camera::Z_NEAR = 0.0f;
const float Camera::Z_FAR = 1.0f;

Camera::Camera(void)
{
}

Camera::~Camera(void)
{
}

/* Orthogonal camera */
void Camera::initOrtho(float left, float right, float bottom, float top)
{
	this->left = left;
	this->right = right;
	this->bottom = bottom;
	this->top = top;
}

void Camera::updateOrtho(float dX, float dY, Scene *scene)
{
	left += dX;
	right += dX;
	bottom += dY;
	top += dY;

	if (bottom <= 0.0f) {
		top -= dY;
		bottom = 0.0f;
	}

	int width, height;
	scene->getLevelSize(1, &width, &height);	//TODO: modificar depenent del nivell carregat
	if (top >= (float)height*(float)Level::TILE_SIZE) {
		bottom -= dY;
		top = (float)height*(float)Level::TILE_SIZE;	//TODO: canviar per TILE_HEIGHT
	}
}

void Camera::loadOrtho()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(left, right, bottom, top, Z_NEAR, Z_FAR);
	glMatrixMode(GL_MODELVIEW);
}
