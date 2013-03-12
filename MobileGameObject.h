#pragma once
#include "gameobject.h"
class MobileGameObject :
	public GameObject
{
public:
	MobileGameObject(void);
	~MobileGameObject(void);
	float getVX() const;
	float getVY() const;
	void setVX(const float v);
	void setVY(const float v);
	void update(long msec);

private:
	float vx;
	float vy;
};

