#include "MobileGameObject.h"


MobileGameObject::MobileGameObject(const float x, const float y, const int idTexture, const int width, const int length, const bool isWalkable, const float vx, const float vy) : GameObject(x, y, idTexture, width, length, isWalkable), vx(vx), vy(vy)
{
	dir = DOWN;
	type = 'm';
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

void MobileGameObject::update(std::vector<GameObject> &collisionableObjects)
{
	GameObject::update();

	/* COLLISION */
	float actualX = getX();
	float actualY = getY();
	float tempX = getX() + vx;
	float tempY = getY() + vy;
	updateBBox(vx, vy);
	// look for any x or y restriction
	for(std::vector<GameObject>::iterator ito = collisionableObjects.begin(); ito != collisionableObjects.end(); ito++) {
		if (isIntersecting(*ito)) {
			// test X
			updateBBox(0, -vy);
			if (isIntersecting(*ito)) {
				tempX = actualX;	
			}
			updateBBox(-vx, vy);
			// test Y
			if (isIntersecting(*ito)) {
				tempY = actualY;	
			}
			updateBBox(vx, 0);
			
		}
		/*
		// x check
			// rigth border
		if (ito->getBoundingBox()->containsX(tempX+getWidth()/2)) {
			tempX = actualX;
		}
		*/
	}
	updateBBox(-vx, -vy);
	
	
	setX(tempX);
	setY(tempY);
	updateBBox(tempX - actualX, tempY - actualY);
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

void MobileGameObject::collision(GameObject &g)
{
	
}
