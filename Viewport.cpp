
#include "Viewport.h"


// 0 = background, 1 = objects, 2 = hover, 3 = clouds
const float Viewport::ZNEAR = -3.0f;
const float Viewport::ZFAR = 1.0f;

Viewport::Viewport(void) {}

Viewport::~Viewport(void) {}


/* Viewport lifetime */
void Viewport::initViewport(float left, float top, float width, float height)
{
	// Viewport definition parameters
	this->left = left;
	this->top = top;
	this->width = width;
	this->height = height;

	// Viewport limits
	minLeft = left;
	maxTop = top;
	maxRight = left + width;
	minBottom = top - height;

	// Viewport velocity
	vx = 0.0f;
	vy = 0.0f;
}

void Viewport::updateViewport()
{
	float newLeft = left + vx;
	float newTop = top + vy;

	if (newLeft < minLeft) left = minLeft;
	else if (newLeft > maxRight - width) left = maxRight - width;
	else left = newLeft;

	if (newTop > maxTop) top = maxTop;
	else if (newTop < minBottom + height) top = minBottom + height; 
	else top = newTop;
}	

void Viewport::defineOrthogonalCamera()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(left, left + width, top - height, top, ZNEAR, ZFAR);
	glMatrixMode(GL_MODELVIEW);
}

/* Setters */
bool Viewport::setOrthoLimits(float minLeft, float maxTop, float maxRight, float minBottom)
{
	if (minLeft >= maxRight || maxTop <= minBottom) return false;
	this->minLeft = minLeft;
	this->maxTop = maxTop;
	this->maxRight = maxRight;
	this->minBottom = minBottom;
	return true;
}

void Viewport::setOrthoVX(float newVx)
{
	this->vx = newVx;
}

void Viewport::setOrthoVY(float newVy)
{
	this->vy = newVy;
}


