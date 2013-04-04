
#pragma once

#ifndef ENEMY_H
#define ENEMY_H

#include "MobileGameObject.h"
#include "GuardPathState.h"
#include "PursueState.h"
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

enum EnemyState {
	GUARD,
	ALERTED
};

class Enemy :
	public MobileGameObject
{
private:
	std::vector<GuardPathState> guard;
	std::vector<Bullet> enemyShots;
	int guardIndex;
	EnemyState state;

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
	//void setAI(NPC_AI *art);
};

#endif