#pragma once

#ifndef STATE_G_H
#define STATE_G_H

#include "Enemy.h"

class Enemy;

class GuardPathState
{
public:
	GuardPathState(void);
	GuardPathState(float vx, float vy, int ticksMax);
	~GuardPathState(void);
	bool isFinished();
	void update();
	void initialize();
	int getTicksLeft();
	int getVX();
	int getVY();

private:
	int ticksLeft;
	int ticksMax;
	float vx;
	float vy;
};

#endif