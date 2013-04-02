
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


/* Updating */
bool MobileGameObject::update(GameData *data, std::vector<GameObject> &collisionObjects, std::vector<bool> &collisionTiles)
{
	bool collision = false;
	GameObject::update(data);

	// Collisions
	float actualX = getX();
	float actualY = getY();
	float tempX = getX() + vx;
	float tempY = getY() + vy;

	if (shouldNotEnterObjects()) {
		// Object collision
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
		// Tile collision
		int minX, maxX, minY, maxY;
		int tileWidthInPixels = 32;						// TODO: Canviar hardcoded
		int tileHeightInPixels = 32;					// TODO: Canviar hardcoded
		int widthInTiles = 15;							// TODO: Canviar hardcoded
		int heightInTiles = collisionTiles.size()/15;	// TODO: Canviar hardcoded
		// Test X collision
		minX = (tempX - getWidth()/2)/tileWidthInPixels;
		minY = heightInTiles - (actualY + getHeight()/2)/tileHeightInPixels;
		maxX = (tempX + getWidth()/2)/tileWidthInPixels;
		maxY = heightInTiles - (actualY - getHeight()/2)/tileHeightInPixels;
		for (int y = minY; y <= maxY; y++) {
			for (int x = minX; x <= maxX; x++) {
				if (collisionTiles[y*widthInTiles + x]) {
					collision = true;
					tempX = actualX;
				}
			}
		}
		// Test Y collision
		minX = (actualX - getWidth()/2)/tileWidthInPixels;
		minY = heightInTiles - (tempY + getHeight()/2)/tileHeightInPixels;
		maxX = (actualX + getWidth()/2)/tileWidthInPixels;
		maxY = heightInTiles - (tempY - getHeight()/2)/tileHeightInPixels;
		for (int y = minY; y <= maxY; y++) {
			for (int x = minX; x <= maxX; x++) {
				if (collisionTiles[y*widthInTiles + x]) {
					collision = true;
					tempY = actualY;
				}
			}
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
	// Moving
	if (vy > 0) {
		if (vx < 0) {
			direction = UP_LEFT;
			setAction(MOVE_UP_LEFT);
		}
		else if (vx > 0) {
			direction = UP_RIGHT;
			setAction(MOVE_UP_RIGHT);
		}
		else {
			direction = UP;
			setAction(MOVE_UP);
		}
	}
	else if (vy < 0) {
		if (vx < 0) {
			direction = DOWN_LEFT;
			setAction(MOVE_DOWN_LEFT);
		}
		else if (vx > 0) {
			direction = DOWN_RIGHT;
			setAction(MOVE_DOWN_RIGHT);
		}
		else {
			direction = DOWN;
			setAction(MOVE_DOWN);
		}
	} 
	else {
		if (vx < 0) {
			direction = LEFT;
			setAction(MOVE_LEFT);
		}
		else if (vx > 0) {
			direction = RIGHT;
			setAction(MOVE_RIGHT);
		}
	}

	// Static
	if (abs(vx) == 0.0f && abs(vy) == 0.0f) {
		switch (direction) {
		case UP:			setAction(STATIC_UP); break;
		case DOWN:			setAction(STATIC_DOWN); break;
		case LEFT:			setAction(STATIC_LEFT); break;
		case RIGHT:			setAction(STATIC_RIGHT); break;
		case UP_LEFT:		setAction(STATIC_UP_LEFT); break;
		case DOWN_LEFT:		setAction(STATIC_DOWN_LEFT); break;
		case DOWN_RIGHT:	setAction(STATIC_DOWN_RIGHT); break;
		case UP_RIGHT:		setAction(STATIC_UP_RIGHT); break;
		default: break;
		}
	}
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

void MobileGameObject::setDirection(Direction direction)
{
	this->direction = direction;
}