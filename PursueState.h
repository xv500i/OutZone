#pragma once
#ifndef PURSUE_STATE_H
#define PURSUE_STATE_H

#include "Enemy.h"
#include "Player.h"

class Enemy;

class PursueState
{
public:
	PursueState(void);
	PursueState(Player &p, float alertDistance, float maxDist, float minDist, float v, bool firePermission = false, int reloadTime = 15);
	~PursueState(void);
	void update(Enemy &e);
	bool isTriggered(Enemy &e);
private:
	float alertDistance;
	Player *target;
	float maxDist;
	float minDist;
	float v;
	bool firePermission;
	int reloadTime;
	bool isFired;
};

#endif

