#include "BossGun.h"

BossGun::BossGun(void)
{
}

BossGun::BossGun(const float x, const float y, const int idTexture, const int width, const int length, const bool isWalkable, int life)
	: BossPart(x,y,idTexture, width, length, isWalkable, life)
{
	minY = y;
	maxX = x+50.0f;
	minX = x-50.0f;
	maxY = y + 50.0f;
	fireRate = 200;
	//float angle = LO + (float)rand()/((float)RAND_MAX/(HI-LO));
	ticksMoving = ( (int)rand() % 60 );
	float LO = -2.5f;
	float HI = +2.5f;
	vx = LO + (float)rand()/((float)RAND_MAX/(HI-LO));
	vy = LO + (float)rand()/((float)RAND_MAX/(HI-LO));
	fireDelay = 0;
}

BossGun::~BossGun(void)
{
}

void BossGun::update(std::vector<Bullet> &shots)
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
	if (fireDelay <= 0) {
		float bulletV = 5.0f;
		Bullet *b = new Bullet(getX(), getY()-5.0f, -1, 3, 3, true, 0.0f, -5.0f);
		Bullet *b1 = new Bullet(getX()+5.0f, getY()-2.0f, -1, 3, 3, true, 0.5f, -5.0f);
		Bullet *b2 = new Bullet(getX()-5.0f, getY()-2.0f, -1, 3, 3, true, -0.5f, -5.0f);
		// FIXME de moment escena no retira les bales
		b->setTicksLeft(100);
		b1->setTicksLeft(100);
		b2->setTicksLeft(100);
		shots.push_back(*b);
		shots.push_back(*b1);
		shots.push_back(*b2);
		fireDelay = ((int)rand())%fireRate;
	} else {
		fireDelay--;
	}
	GameObject::update();
}

void BossGun::render(GameData *data) const
{
	GameObject::render(data);
}