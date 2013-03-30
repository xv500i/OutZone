
#include "Bullet.h"


Bullet::Bullet(void) {}

Bullet::Bullet(const float x, const float y, const int spriteIndex, const int width, const int height, const bool isWalkable, const float vx, const float vy)
	: MobileGameObject(x, y, spriteIndex, width, height, isWalkable, vx, vy)
{
	ticksLeft = -1;
}

Bullet::~Bullet(void) {}


/* Drawing */
void Bullet::update(GameData *data, std::vector<GameObject> &collisionableObjects)
{
	MobileGameObject::update(data, collisionableObjects);
	if (ticksLeft > 0) ticksLeft--;
}


/* Getters */
float Bullet::getAngleVelocity() const
{
	float angle = (atan2(getVY(), getVX()) * 180 / 3.1415926f) - 90.0f;
	return angle;
}

bool Bullet::isDead()
{
	return ticksLeft == 0;
}


/* Setters */
void Bullet::setTicksLeft(int t)
{
	ticksLeft = t;
}