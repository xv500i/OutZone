
#include "MobileGameObject.h"
#include <cmath>


MobileGameObject::MobileGameObject(const float x, const float y, const int spriteIndex, const int width, const int height, const bool isWalkable, const float vx, const float vy) 
	: GameObject(x, y, spriteIndex, width, height, isWalkable), vx(vx), vy(vy)
{
	direction = DOWN;
	setType('m');
}

MobileGameObject::MobileGameObject() : GameObject() {}

MobileGameObject::~MobileGameObject(void) {}


/* Drawing */
void MobileGameObject::update(GameData *data, std::vector<GameObject> &collisionableObjects)
{
	GameObject::update(data);

	// COLLISION
	float actualX = getX();
	float actualY = getY();
	float tempX = getX() + vx;
	float tempY = getY() + vy;

	if (shouldNotEnterObjects()) {
		updateBBox(vx, vy);
		// Look for any x or y restriction
		for (std::vector<GameObject>::iterator ito = collisionableObjects.begin(); ito != collisionableObjects.end(); ito++) {
			if (getId() != ito->getId() && isIntersecting(*ito)) {
				// Test X
				updateBBox(0, -vy);
				if (isIntersecting(*ito)) tempX = actualX;	
				// Test Y
				updateBBox(-vx, vy);
				if (isIntersecting(*ito)) tempY = actualY;	
				updateBBox(vx, 0);
			}
		}
		updateBBox(-vx, -vy);
	}
	
	// Change the object position
	setX(tempX);
	setY(tempY);
	updateBBox(tempX - actualX, tempY - actualY);

	// Set the object direction
	if (vy > 0) {
		if (vx < 0) direction = UP_LEFT;
		else if (vx > 0) direction = UP_RIGHT;
		else direction = UP;
	}
	else if (vy < 0) {
		if (vx < 0) direction = DOWN_LEFT;
		else if (vx > 0) direction = DOWN_RIGHT;
		else direction = DOWN;
	} 
	else {
		if (vx < 0) direction = LEFT;
		else if (vx > 0) direction = RIGHT;
	}

	// Set the object action
	if (abs(vx) > 0.0f || abs(vy) > 0.0f) setAction(MOVE);
	else setAction(STATIC);
}


/* Getters */
float MobileGameObject::getVX() const
{
	return vx;
}

float MobileGameObject::getVY() const
{
	return vy;
}

Direction MobileGameObject::getDirection() const
{
	return direction;
}

float MobileGameObject::getAngleVelocity() const
{
	float angle;
	switch(direction){
	case UP:		angle = 0.0f; break;
	case UP_RIGHT:	angle = -45.0f; break;
	case RIGHT:		angle = -90.0f; break;
	case DOWN_RIGHT:angle = -135.0f; break;
	case DOWN:		angle = -180.0f; break;
	case DOWN_LEFT: angle = -225.0f; break;
	case LEFT:		angle = -270.0f; break;
	case UP_LEFT:	angle = -315.0f; break;
	}
	return angle;
}


/* Setters */
void MobileGameObject::setVX(const float vx)
{
	this->vx = vx;
}

void MobileGameObject::setVY(const float vy)
{
	this->vy = vy;
}




void MobileGameObject::collision(GameObject &g) {}