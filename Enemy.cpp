#include "Enemy.h"


Enemy::Enemy(void)
{
}

Enemy::Enemy(const float x, const float y, const int idTexture, const int width, const int length, const bool isWalkable, const float vx, const float vy)
	: MobileGameObject(x, y, idTexture, width, length, isWalkable, vx, vy)
{

}


Enemy::~Enemy(void)
{
}
