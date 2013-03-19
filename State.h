#pragma once
#include "Enemy.h"
class State
{
public:
	State(void);
	~State(void);
	void update(Enemy &e);
	bool isFinished();
	void initialize();
};

