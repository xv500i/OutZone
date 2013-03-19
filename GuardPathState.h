#pragma once
#include "state.h"
class GuardPathState :
	public State
{
public:
	GuardPathState(void);
	GuardPathState(float vx, float vy, int ticksMax);
	~GuardPathState(void);
	void update(Enemy &e);
	bool isFinished();
	void initialize();

private:
	int ticksLeft;
	int ticksMax;
	float vx;
	float vy;
};

