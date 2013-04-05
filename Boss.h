
#pragma once

#include "GameObject.h"
#include "BossTail.h"
#include "Bullet.h"
#include "BossIA.h"
#include "Player.h"

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
	std::vector<Bullet> enemyShots;

public:
	Boss(void);
	Boss(const float x, const float y, const int spriteIndex, const int width, const int height, const bool isWalkable, int life);
	~Boss(void);
	void update(GameData *data, Viewport* viewport, std::vector<GameObject> &collisionObjects, std::vector<bool> &collisionTiles, Player &player);
	void render(GameData *data);
	bool isDead();
};

