#include "MobileGameObject.h"
#include <cmath>

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

	if (shouldNotEnterObjects()) {
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
		}
		updateBBox(-vx, -vy);
	}
	
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
	if (g.getType() == 'm') {
	
	}
}

void MobileGameObject::render() const
{
	float angle = getAngleVelocity();
	
	/*glColor3f(1.0f, 1.0f, 1.0f);
	glPushMatrix();
	glTranslatef(getX(), getY(), 0.0f);
	glRotatef(angle, 0.0f, 0.0f, 1.0f);
	glBegin(GL_QUADS);
		glVertex3i(- getWidth()/2 , - getLength()/2, 1);
		glVertex3i(- getWidth()/2 , + getLength()/2, 1);
		glVertex3i(+ getWidth()/2 , + getLength()/2, 1);
		glVertex3i(+ getWidth()/2 , - getLength()/2, 1);
	glEnd();
	glPopMatrix();*/

	float offset = 16.0f/128.0f;

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 2);
	glPushMatrix();
	glTranslatef(getX(), getY(), 0.0f);
	glRotatef(angle, 0.0f, 0.0f, 1.0f);
	glBegin(GL_QUADS);
		// Bottom-left
		glTexCoord2f(0.0f, offset*3);
		glVertex3i(- 32/2 , - 32/2, 1);
		// Top-left
		glTexCoord2f(0.0f, offset);
		glVertex3i(- 32/2 , + 32/2, 1);
		// Top-right
		glTexCoord2f(offset*2, offset);
		glVertex3i(+ 32/2 , + 32/2, 1);
		// Bottom-right
		glTexCoord2f(offset*2, offset*3);
		glVertex3i(+ 32/2 , - 32/2, 1);	
	glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}

float MobileGameObject::getAngleVelocity() const
{
	float angle;
	
	switch(dir){
	case UP:
		angle = 0.0f;
		break;
	case UP_RIGHT:
		angle = -45.0f;
		break;
	case RIGHT:
		angle = -90.0f;
		break;
	case DOWN_RIGHT:
		angle = -135.0f;
		break;
	case DOWN:
		angle = -180.0f;
		break;
	case DOWN_LEFT:
		angle = -225.0f;
		break;
	case LEFT:
		angle = -270.0f;
		break;
	case UP_LEFT:
		angle = -315.0f;
		break;
	}
	
	
	return angle;
}
