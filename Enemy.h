#pragma once

#ifndef ENEMY_H
#define ENEMY_H

//#include "NPC_AI.h"
#include "mobilegameobject.h"
class Enemy :
	public MobileGameObject
{
public:
	Enemy(void);
	Enemy(const float x, const float y, const int idTexture, const int width, const int length, const bool isWalkable, const float vx = 0, const float vy = 0);
	~Enemy(void);
	void update(std::vector<GameObject> &collisionableObjects);

private:
	//NPC_AI artificial;
};

#endif