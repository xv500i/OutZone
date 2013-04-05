
#pragma once

#include "MobileGameObject.h"


class Bullet : public MobileGameObject
{
private:
	int ticksLeft;
	int damage;
	bool collisioned;

public:
	const static float DEFAULT_BULLET_VELOCITY;

	Bullet(void);
	Bullet(const float x, const float y, const int spriteIndex, const int width, const int height, const bool isWalkable, const float vx = 0, const float vy = 0, int damage = 1);
	~Bullet(void);
	
	/* Drawing */
	bool update(GameData *data, std::vector<GameObject> &collisionObjects, std::vector<bool> &collisionTiles, std::vector<GameObject*> &objectives);

	/* Getters */
	virtual float getAngleVelocity() const;
	bool isDead();

	/* Setters */
	void collision();
	void setTicksLeft(int t);
};