#include "Enemy.h"
#include "GuardPathState.h"

Enemy::Enemy(void)
{
}

Enemy::Enemy(const float x, const float y, const int idTexture, const int width, const int length, const bool isWalkable, const float vx, const float vy)
	: MobileGameObject(x, y, idTexture, width, length, isWalkable, vx, vy)
{
	GuardPathState *s1 = new GuardPathState(1, 5.0f, 0.0f, 30);
	GuardPathState *s2 = new GuardPathState(2, 0.0f, 5.0f, 30);
	GuardPathState *s3 = new GuardPathState(3, -5.0f, 0.0f, 30);
	GuardPathState *s4 = new GuardPathState(0, 0.0f, -5.0f, 30);
	ai = new NPC_AI(4,0);
	ai->setState(0, *s1);
	ai->setState(1, *s2);
	ai->setState(2, *s3);
	ai->setState(3, *s4);
	ai->initialize();
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