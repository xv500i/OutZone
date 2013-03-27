#pragma once
#include "bosspart.h"
class BossGun :
	public BossPart
{
public:
	BossGun(void);
	BossGun(const float x, const float y, const int idTexture, const int width, const int length, const bool isWalkable, int life);
	~BossGun(void);
	void update();
	void render(GameData *data) const;
private:
	int fireRate;
	int ticksMoving;
	float vx, vy;
};

