
#pragma once

#include "GameObject.h"
#include "BossTail.h"
#include "Bullet.h"
#include "BossIA.h"


class Boss : public GameObject
{
private:
	int life;
	bool invul;
	BossTail centerTail;
	BossTail leftTail;
	BossTail rightTail;
	BossIA ia;
	int t;

public:
	Boss(void);
	Boss(const float x, const float y, const int spriteIndex, const int width, const int height, const bool isWalkable, int life);
	~Boss(void);
	void update(GameData *data, std::vector<Bullet> &shots, float x, float y);
	void render(GameData *data) const;
};

