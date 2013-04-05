
#pragma once

#include "MobileGameObject.h"
#include "GuardPathState.h"
#include "Player.h"
#include "Weapon.h"

class Player;


enum EnemyType {
	BAT_1,
	BAT_2,
	BAT_3,
	SPIDER_1,
	SPIDER_2
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
	float pursueVelocity;
	bool firePermission;
	float gunVelocity;
	bool pursue;
	float detectionDistance;
	float minDistance;
	float minPursueDistance;
	EnemyState state;
	Weapon weapon;
	int life;
	bool hasBeenHit;
	bool hasBeenKilled;

public:
	Enemy(void);
	Enemy(EnemyType type, const float x, const float y, const int width, const int height, std::vector<GuardPathState> &gps, int spriteIndex = -1);
	//Enemy(const float x, const float y, const int spriteIndex, const int width, const int height, const bool isWalkable, const float vx = 0, const float vy = 0);
	//Enemy(Player &p, const float x, const float y, const int spriteIndex, const int width, const int height, const bool isWalkable, const float vx = 0, const float vy = 0);
	//Enemy(Player &p, int fireDelay, const float x, const float y, const int spriteIndex, const int width, const int height, const bool isWalkable, const float vx = 0, const float vy = 0);
	~Enemy(void);
	
	/* Updating */
	void update(GameData *data, Viewport *viewport, std::vector<GameObject> &collisionObjects, std::vector<bool> &collisionTiles, Player &player);
	
	/* Drawing */
	void render(GameData *data);
	
	/* Getters */
	bool isDead();

	/* Setters */
	void decrementLife(int decrement);
	void kill();
};