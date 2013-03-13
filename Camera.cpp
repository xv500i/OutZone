
#include "Camera.h"


const float Camera::Z_NEAR = -1.0f;
const float Camera::Z_FAR = 1.0f;

Camera::Camera(void) {}

Camera::~Camera(void) {}


/* Orthogonal camera */
void Camera::initOrtho(float left, float top, float width, float height)
{
	this->left = left;
	this->top = top;
	this->width = width;
	this->height = height;
	this->orthoVX = 0.0f;
	this->orthoVY = 0.0f;
}

void Camera::updateOrtho(long msec)
{
	this->left += orthoVX*msec;
	this->top += orthoVY*msec;
}	

/*void Camera::updateOrtho(float dX, float dY, Scene *scene)
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
}*/

void Camera::loadOrtho()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(left, left + width, top - height, top, Z_NEAR, Z_FAR);
	glMatrixMode(GL_MODELVIEW);
}

void Camera::setOrthoVX(float newOrthoVX)
{
	this->orthoVX = newOrthoVX;
}

void Camera::setOrthoVY(float newOrthoVY)
{
	this->orthoVY = newOrthoVY;
}
