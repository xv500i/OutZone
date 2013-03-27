#include "BossGun.h"


BossGun::BossGun(void)
{
}

BossGun::BossGun(const float x, const float y, const int idTexture, const int width, const int length, const bool isWalkable, int life)
	: BossPart(x,y,idTexture, width, length, isWalkable, life)
{
	minY = y;
	maxX = x+150.0f;
	minX = x-150.0f;
	maxY = y + 100.0f;
	fireRate = 35;
	//float angle = LO + (float)rand()/((float)RAND_MAX/(HI-LO));
	ticksMoving = ( (int)rand() % 60 );
	float LO = -2.5f;
	float HI = +2.5f;
	vx = LO + (float)rand()/((float)RAND_MAX/(HI-LO));
	vy = LO + (float)rand()/((float)RAND_MAX/(HI-LO));
}

BossGun::~BossGun(void)
{
}

void BossGun::update()
{
	if (ticksMoving == 0) {
		ticksMoving = ( (int)rand() % 60 );
		float LO = -2.5f;
		float HI = +2.5f;
		vx = LO + (float)rand()/((float)RAND_MAX/(HI-LO));
		vy = LO + (float)rand()/((float)RAND_MAX/(HI-LO));
	} else {
		float realx = std::max(std::min(maxX, getX() + vx), minX);
		float realy = std::max(std::min(maxY, getY() + vy), minY);
		setX(realx);
		setY(realy);
		ticksMoving = ticksMoving - 1;
	}
	GameObject::update();
}

void BossGun::render(GameData *data) const
{
	GameObject::render(data);
}
