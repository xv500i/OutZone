
#pragma once

#include "GameObject.h"
#include "Bullet.h"


class BossPart : public GameObject
{
public:
	BossPart(void);
	BossPart(const float x, const float y, const int spriteIndex, const int width, const int height, const bool isWalkable, int life);
	~BossPart(void);
	void update(GameData *data);
	void render(GameData *data) const;
	void moveTo(float x, float y, float &ix, float iy);
	void setLimits(float maxX, float maxY, float minX, float minY);
protected:
	float maxX, maxY, minX, minY;
private:
	int life;
	
};

