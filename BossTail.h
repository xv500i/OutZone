#pragma once
#include "gameobject.h"
#include "BossPart.h"
#include "BossGun.h"
class BossTail :
	public GameObject
{
public:
	BossTail(void);
	BossTail(const float x, const float y, const int idTexture, const int width, const int length, const bool isWalkable, int life, int nparts);
	~BossTail(void);
	void update(std::vector<Bullet> &shots);
	void render(GameData *data) const;
private:
	int life;
	std::vector<BossPart> parts;
	BossGun bg;
};

