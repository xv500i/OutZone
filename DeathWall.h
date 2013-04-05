
#pragma once

#include "MobileGameObject.h"
#include "Enemy.h"
#include "Player.h"


class DeathWall : public MobileGameObject
{
private:
	const static float DEATH_WALL_VX;
	const static float DEATH_WALL_VY;

	int xCenter;

public:
	DeathWall();
	DeathWall(int viewportWidth, int viewportHeight);
	~DeathWall(void);

	bool update(GameData *data, std::vector<Enemy> &enemies, Player &player);
};

