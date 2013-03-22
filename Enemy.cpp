#include "Enemy.h"
#include "GuardPathState.h"

Enemy::Enemy(void)
{
}

Enemy::Enemy(const float x, const float y, const int idTexture, const int width, const int length, const bool isWalkable, const float vx, const float vy)
	: MobileGameObject(x, y, idTexture, width, length, isWalkable, vx, vy)
{
	float v = 3.0f;
	int ticks = 60;
	GuardPathState *s1 = new GuardPathState(1, v, 0.0f, ticks);
	GuardPathState *s2 = new GuardPathState(2, 0.0f, v, ticks);
	GuardPathState *s3 = new GuardPathState(3, -v, 0.0f, ticks);
	GuardPathState *s4 = new GuardPathState(0, 0.0f, -v, ticks);
	ai = new NPC_AI(4,0);
	ai->setState(0, *s1);
	ai->setState(1, *s2);
	ai->setState(2, *s3);
	ai->setState(3, *s4);
	ai->initialize();
}

Enemy::Enemy(Player &p, const float x, const float y, const int idTexture, const int width, const int length, const bool isWalkable, const float vx, const float vy)
	: MobileGameObject(x, y, idTexture, width, length, isWalkable, vx, vy)
{
	ai = new NPC_AI(0,1,0);
	PursueState *pur = new PursueState(p, 200.0f, 250.f, 50.0f, 2.0f);
	ai->setTriggerState(0, *pur);
}


Enemy::~Enemy(void)
{
}

void Enemy::update(std::vector<GameObject> &collisionableObjects)
{
	MobileGameObject::update(collisionableObjects);
	ai->update(*this);
}

void Enemy::setAI(NPC_AI *art)
{
	ai = art;
}