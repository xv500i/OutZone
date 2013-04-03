
#pragma once

#ifndef ENEMY_H
#define ENEMY_H

#include "MobileGameObject.h"
#include "NPC_AI.h"
#include "Player.h"

class Player;
class NPC_AI;


enum EnemyType {
	GUARD_NOSHOT,
	GUARD_SHOT,
	PURSUE_NOSHOT,
	PURSUE_SHOT,
	GUARD_PURSUE_NOSHOT,
	GUARD_PURSUE_SHOT
};

class Enemy :
	public MobileGameObject
{
private:
	NPC_AI *ai;
	std::vector<Bullet> enemyShots;

public:
	Enemy(void);
	Enemy(EnemyType type, const float x, const float y, const int spriteIndex, const int width, const int height);
	//Enemy(const float x, const float y, const int spriteIndex, const int width, const int height, const bool isWalkable, const float vx = 0, const float vy = 0);
	Enemy(Player &p, const float x, const float y, const int spriteIndex, const int width, const int height, const bool isWalkable, const float vx = 0, const float vy = 0);
	Enemy(Player &p, int fireDelay, const float x, const float y, const int spriteIndex, const int width, const int height, const bool isWalkable, const float vx = 0, const float vy = 0);
	~Enemy(void);
	
	/* Updating */
	void update(GameData *data, Viewport *viewport, std::vector<GameObject> &collisionObjects, std::vector<bool> &collisionTiles, Player &player);
	
	/* Drawing */
	void render(GameData *data);

	/* Setters */
	void setAI(NPC_AI *art);
};

#endif