#pragma once

#ifndef NPC_AI_H
#define NPC_AI_H

#include <vector>
#include "GuardPathState.h"
#include "Enemy.h"

class Enemy;
class GuardPathState;

class NPC_AI
{
public:
	NPC_AI(void);
	NPC_AI(int numberOfStates, int initialState = 0);
	~NPC_AI(void);
	void update(Enemy &e);
	void setState(int i, GuardPathState &e);
	void initialize();
private:
	std::vector<GuardPathState> states;
	int actualState;
};

#endif