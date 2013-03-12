#include "MobileGameObject.h"


MobileGameObject::MobileGameObject(void)
{
}


MobileGameObject::~MobileGameObject(void)
{
}

void MobileGameObject::setVX(const float v)
{
	this->vx = vx;
}

void MobileGameObject::setVX(const float v)
{
	this->vx = vx;
}

float MobileGameObject::getVX() const
{
	return vx;
}

float MobileGameObject::getVY() const
{
	return vy;
}

void MobileGameObject::update(long msec)
{
	GameObject::update(msec);
	setX(getX() + vx*msec);
	setY(getY() + vy*msec);
}
