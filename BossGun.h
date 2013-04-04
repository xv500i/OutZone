
#pragma once

#include "BossPart.h"


class BossGun : public BossPart
{
public:
	BossGun(void);
	BossGun(const float x, const float y, const int spriteIndex, const int width, const int height, const bool isWalkable, int life);
	~BossGun(void);
	void update(GameData *data, std::vector<Bullet> &shots);
	void render(GameData *data);
private:
	int fireRate;
	int fireDelay;
	int ticksMoving;
	float vx, vy;
};

