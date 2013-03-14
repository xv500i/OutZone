#include "MobileGameObject.h"


MobileGameObject::MobileGameObject(const float x, const float y, const int idTexture, const int width, const int length, const bool isWalkable, const float vx, const float vy) : GameObject(x, y, idTexture, width, length, isWalkable), vx(vx), vy(vy)
{
	dir = DOWN;
}

MobileGameObject::MobileGameObject() : GameObject()
{
	
}


MobileGameObject::~MobileGameObject(void)
{
}

void MobileGameObject::setVX(const float v)
{
	this->vx = v;
}

void MobileGameObject::setVY(const float v)
{
	this->vy = v;
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
	if (vy > 0) {
		if (vx < 0) {
			dir = UP_LEFT;
		} else if (vx > 0){
			dir = UP_RIGHT;
		} else {
			dir = UP;
		}
	} else if( vy < 0){
		if (vx < 0) {
			dir = DOWN_LEFT;
		} else if (vx > 0){
			dir = DOWN_RIGHT;
		} else {
			dir = DOWN;
		}
	} else {
		if (vx < 0) {
			dir = LEFT;
		} else if (vx > 0){
			dir = RIGHT;
		} 
	}
}

Directions MobileGameObject::getDirection() const
{
	return dir;
}
