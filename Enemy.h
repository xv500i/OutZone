
#pragma once

#ifndef ENEMY_H
#define ENEMY_H

#include "MobileGameObject.h"
#include "NPC_AI.h"
#include "Player.h"

class NPC_AI;


class Enemy :
	public MobileGameObject
{
private:
	NPC_AI *ai;

public:
	Enemy(void);
	Enemy(const float x, const float y, const int spriteIndex, const int width, const int height, const bool isWalkable, const float vx = 0, const float vy = 0);
	Enemy(Player &p, const float x, const float y, const int spriteIndex, const int width, const int height, const bool isWalkable, const float vx = 0, const float vy = 0);
	Enemy(Player &p, int fireDelay, const float x, const float y, const int spriteIndex, const int width, const int height, const bool isWalkable, const float vx = 0, const float vy = 0);
	~Enemy(void);
	
	/* Drawing */
	void update(GameData *data, std::vector<GameObject> &collisionableObjects, std::vector<Bullet> &bullets);
	
	/* Setters */
	void setAI(NPC_AI *art);
};

#endif