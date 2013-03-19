#include "Bullet.h"


Bullet::Bullet(void)
{
}

Bullet::Bullet(const float x, const float y, const int idTexture, const int width, const int length, const bool isWalkable, const float vx, const float vy)
	: MobileGameObject(x,y,idTexture,width, length, isWalkable, vx, vy)
{
	ticksLeft = -1;
}

Bullet::~Bullet(void)
{
}

bool Bullet::isDead()
{
	return ticksLeft == 0;
}

void Bullet::setTicksLeft(int t)
{
	ticksLeft = t;
}

void Bullet::update(std::vector<GameObject> &collisionableObjects)
{
	MobileGameObject::update(collisionableObjects);
	if (ticksLeft > 0) ticksLeft--;
}
