
#include "Viewport.h"


// 0 = background, 1 = objects, 2 = hover, 3 = deathwall&lantern, 4 = hud
const float Viewport::ZNEAR = -5.0f;
const float Viewport::ZFAR = 1.0f;

Viewport::Viewport(void) {}

Viewport::~Viewport(void) {}


/* Viewport lifetime */
void Viewport::init(float left, float top, float width, float height)
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
}

void Viewport::updateWithPosition(int x, int y)
{
	float newLeft = x - width/2;
	float newTop = y + height*2/3;

	// Viewport limit control
	if (newLeft < minLeft) left = minLeft;
	else if (newLeft > maxRight - width) left = maxRight - width;
	else left = newLeft;
	if (newTop > maxTop) top = maxTop;
	else if (newTop < minBottom + height) top = minBottom + height; 
	else top = newTop;

	defineOrthogonalCamera();
}	

void Viewport::defineOrthogonalCamera()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(left, left + width, top - height, top, ZNEAR, ZFAR);
	glMatrixMode(GL_MODELVIEW);
}

/* Getters */
float Viewport::getLeft()
{
	return left;
}

float Viewport::getTop()
{
	return top;
}

float Viewport::getWidth()
{
	return width;
}

float Viewport::getHeight()
{
	return height;
}

/* Setters */
bool Viewport::setLimits(float minLeft, float maxTop, float maxRight, float minBottom)
{
	if (minLeft >= maxRight || maxTop <= minBottom) return false;
	this->minLeft = minLeft;
	this->maxTop = maxTop;
	this->maxRight = maxRight;
	this->minBottom = minBottom;
	return true;
}

