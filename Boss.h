#pragma once
#include "gameobject.h"
#include "BossTail.h"
#include "Bullet.h"
class Boss :
	public GameObject
{
public:
	Boss(void);
	Boss(const float x, const float y, const int idTexture, const int width, const int length, const bool isWalkable, int life);
	~Boss(void);
	void update(std::vector<Bullet> &shots);
	void render(GameData *data) const;
private:
	int life;
	bool invul;
	BossTail centerTail;
	BossTail leftTail;
	BossTail rightTail;
};

