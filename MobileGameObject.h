#pragma once
#include "gameobject.h"
class MobileGameObject :
	public GameObject
{
public:
	MobileGameObject();
	MobileGameObject(const float x, const float y, const int idTexture, const int width, const int length, const bool isWalkable, const float vx = 0, const float vy = 0);
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

