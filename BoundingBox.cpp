
#include "BoundingBox.h"


BoundingBox::BoundingBox(const float top, const float bottom, const float left, const float right)
{
	this->top = top;
	this->bottom = bottom;
	this->left = left;
	this->right = right;
}

BoundingBox::~BoundingBox(void) {}


bool BoundingBox::isIntersectedBy(const BoundingBox &b) const
{
	if (left > b.right || right < b.left || bottom > b.top || top < b.bottom) return false;
	else return true;
}

void BoundingBox::translate(const float x, const float y)
{
	top += y;
	bottom += y;
	left += x;
	right += x;
}

bool BoundingBox::contains(const float x, const float y) const
{
	return (top > y && bottom < y && left < x && right > x);
}

bool BoundingBox::containsX(const float x) const
{
	return (x > left && x < right);
}

bool BoundingBox::containsY(const float y) const
{
	return (y > bottom && y < top);
}