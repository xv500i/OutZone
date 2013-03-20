#pragma once
#include "mobilegameobject.h"
class Bullet :
	public MobileGameObject
{
public:
	Bullet(void);
	Bullet(const float x, const float y, const int idTexture, const int width, const int length, const bool isWalkable, const float vx = 0, const float vy = 0);
	~Bullet(void);
	bool isDead();
	void setTicksLeft(int t);
	void update(std::vector<GameObject> &collisionableObjects);
	virtual float getAngleVelocity() const;
private:
	int ticksLeft;
};

