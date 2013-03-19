#pragma once

#ifndef STATE_H
#define STATE_H

#include "Enemy.h"
class State
{
public:
	State(void);
	~State(void);
	void update(Enemy &e);
	bool isFinished();
	void initialize();
	int getNextState();
private:
	int nextState;
};

#endif