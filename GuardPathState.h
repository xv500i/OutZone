#pragma once
#include "state.h"
class GuardPathState :
	public State
{
public:
	GuardPathState(void);
	GuardPathState(int nextState, float vx, float vy, int ticksMax);
	~GuardPathState(void);
	void update(Enemy &e);
	bool isFinished();
	void initialize();
	int getNextState();

private:
	int ticksLeft;
	int ticksMax;
	float vx;
	float vy;
	int nextState;
};

