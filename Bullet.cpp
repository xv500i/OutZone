
#include "Bullet.h"


const float Bullet::DEFAULT_BULLET_VELOCITY = 10.0f;

Bullet::Bullet(void) {}

Bullet::Bullet(const float x, const float y, const int spriteIndex, const int width, const int height, const bool isWalkable, const float vx, const float vy)
	: MobileGameObject(x, y, spriteIndex, width, height, isWalkable, vx, vy)
{
	ticksLeft = -1;
}

Bullet::~Bullet(void) {}


/* Drawing */
bool Bullet::update(GameData *data, std::vector<GameObject> &collisionObjects, std::vector<GameObject> &objectives)
{
	if (ticksLeft > 0) ticksLeft--;
	bool collision = MobileGameObject::update(data, collisionObjects);

	for (std::vector<GameObject>::iterator iobj = objectives.begin(); iobj != objectives.end();) {
		if (isIntersecting(*iobj)) {
			// Kill enemy
			// TODO ANIMATION
			collision = true;
			iobj = objectives.erase(iobj);
		} 
		else iobj++;
	}
	return collision;
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