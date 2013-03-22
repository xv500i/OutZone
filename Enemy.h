#pragma once

#ifndef ENEMY_H
#define ENEMY_H

#include "mobilegameobject.h"
#include "NPC_AI.h"
#include "Player.h"

class NPC_AI;

class Enemy :
	public MobileGameObject
{
public:
	Enemy(void);
	Enemy(const float x, const float y, const int idTexture, const int width, const int length, const bool isWalkable, const float vx = 0, const float vy = 0);
	Enemy(Player &p, const float x, const float y, const int idTexture, const int width, const int length, const bool isWalkable, const float vx = 0, const float vy = 0);
	~Enemy(void);
	void update(std::vector<GameObject> &collisionableObjects);
	void setAI(NPC_AI *art);

private:
	NPC_AI *ai;
};

#endif