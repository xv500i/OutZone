#include "BoundingBox.h"


BoundingBox::BoundingBox(const float top, const float botom, const float left, const float right)
{
	this->top = top;
	this->bottom = bottom;
	this->left = left;
	this->right = right;
}


BoundingBox::~BoundingBox(void)
{
}

bool BoundingBox::isIntersectedBy(const BoundingBox &b) const
{
	if (left > b.right || right < b.left || bottom > b.top || top < b.bottom) return false;
	else return true;
}

void BoundingBox::translate(const float x, const float y)
{
	this->top += y;
	this->bottom += y;
	this->left += x;
	this->right += x;
}

bool BoundingBox::contains(const float x, const float y)
{
	return ( top > y && bottom < y && left < x && right > x);
}
