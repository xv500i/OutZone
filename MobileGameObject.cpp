
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
bool MobileGameObject::update(GameData *data, std::vector<GameObject> &collisionObjects)
{
	bool collision = false;
	GameObject::update(data);

	// Objects collision testing
	float actualX = getX();
	float actualY = getY();
	float tempX = getX() + vx;
	float tempY = getY() + vy;

	if (shouldNotEnterObjects()) {
		// Look for any x or y restriction
		for (std::vector<GameObject>::iterator ito = collisionObjects.begin(); ito != collisionObjects.end(); ito++) {
			// Test intersecting X
			updateBBox(vx, 0);
			if (getId() != ito->getId() && isIntersecting(*ito)) {
				collision = true;
				tempX = actualX;
			}
			// Test intersecting Y
			updateBBox(-vx, vy);
			if (getId() != ito->getId() && isIntersecting(*ito)) {
				collision = true;
				tempY = actualY;
			}
			updateBBox(0, -vy);
		}
	}
	setX(tempX);
	setY(tempY);
	updateBBox(tempX - actualX, tempY - actualY);

	// Change the direction and action of the gameObject
	updateDirectionAndAction();

	return collision;
}

void MobileGameObject::updateDirectionAndAction()
{
	// Object direction
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

	// Object action
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