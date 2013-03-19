#include "Enemy.h"


Enemy::Enemy(void)
{
}

Enemy::Enemy(const float x, const float y, const int idTexture, const int width, const int length, const bool isWalkable, const float vx, const float vy)
	: MobileGameObject(x, y, idTexture, width, length, isWalkable, vx, vy)
{
	//ai = NPC_AI(2,0);
}


Enemy::~Enemy(void)
{
}

void Enemy::update(std::vector<GameObject> &collisionableObjects)
{
	MobileGameObject::update(collisionableObjects);
	
}
