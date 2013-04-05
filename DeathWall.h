
#pragma once

#include "MobileGameObject.h"


class DeathWall : public MobileGameObject
{
private:
	const static float DEATH_WALL_VX;
	const static float DEATH_WALL_VY;

public:
	DeathWall();
	DeathWall(int viewportWidth, int viewportHeight);
	~DeathWall(void);
};

