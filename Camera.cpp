
#include "Camera.h"


const float Camera::Z_NEAR = -1.0f;
const float Camera::Z_FAR = 1.0f;

Camera::Camera(void) {}

Camera::~Camera(void) {}


/* Orthogonal camera */
void Camera::initOrtho(float left, float top, float width, float height)
{
	// Orthogonal camera definition parameters
	orthoLeft = left;
	orthoTop = top;
	orthoWidth = width;
	orthoHeight = height;

	// Orthogonal camera limits
	orthoMinLeft = left;
	orthoMaxTop = top;
	orthoMaxRight = left + width;
	orthoMinBottom = top - height;

	// Orthogonal camera velocity
	orthoVX = 0.0f;
	orthoVY = 0.0f;
}

void Camera::updateOrtho(long msec)
{
	float newLeft = orthoLeft + orthoVX*msec;
	float newTop = orthoTop + orthoVY*msec;

	if (newLeft < orthoMinLeft) orthoLeft = orthoMinLeft;
	else if (newLeft > orthoMaxRight - orthoWidth) orthoLeft = orthoMaxRight - orthoWidth;
	else orthoLeft = newLeft;

	if (newTop > orthoMaxTop) orthoTop = orthoMaxTop;
	else if (newTop < orthoMinBottom + orthoHeight) orthoTop = orthoMinBottom + orthoHeight; 
	else orthoTop = newTop;
}	

void Camera::loadOrtho()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(orthoLeft, orthoLeft + orthoWidth, orthoTop - orthoHeight, orthoTop, Z_NEAR, Z_FAR);
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

bool Camera::setOrthoLimits(float minLeft, float maxTop, float maxRight, float minBottom)
{
	if (minLeft >= maxRight || maxTop <= minBottom) return false;
	this->orthoMinLeft = minLeft;
	this->orthoMaxTop = maxTop;
	this->orthoMaxRight = maxRight;
	this->orthoMinBottom = minBottom;
	return true;
}
