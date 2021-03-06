
#pragma once

#include "GameObject.h"
#include "BossPart.h"
#include "BossGun.h"


class BossTail : public GameObject
{
private:
	int life;
	std::vector<BossPart> parts;
	BossGun bg;
	bool invul;

public:
	BossTail(void);
	BossTail(const float x, const float y, const int spriteIndex, const int width, const int height, const bool isWalkable, int life, int nparts);
	~BossTail(void);
	void update(GameData *data, std::vector<Bullet> &shots);
	void render(GameData *data);
	void fireTo(std::vector<Bullet> &shots, float x, float y);
	bool isDead();
	void decrementLife(int life = 1);
	int getLifes();
	void setInvul(bool b);
};

