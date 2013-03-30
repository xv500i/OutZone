
#pragma once

#include "MobileGameObject.h"


class Bullet : public MobileGameObject
{
private:
	int ticksLeft;

public:
	Bullet(void);
	Bullet(const float x, const float y, const int spriteIndex, const int width, const int height, const bool isWalkable, const float vx = 0, const float vy = 0);
	~Bullet(void);
	
	/* Drawing */
	void update(GameData *data, std::vector<GameObject> &collisionableObjects);

	/* Getters */
	virtual float getAngleVelocity() const;
	bool isDead();

	/* Setters */
	void setTicksLeft(int t);
};