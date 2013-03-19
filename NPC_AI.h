#pragma once

#ifndef NPC_AI_H
#define NPC_AI_H

#include <vector>
#include "State.h"
#include "Enemy.h"

class NPC_AI
{
public:
	NPC_AI(void);
	NPC_AI(int numberOfStates, int initialState = 0);
	~NPC_AI(void);
	void update(Enemy &e);
	void setState(int i, State &e);
	void initialize();
private:
	std::vector<State> states;
	int actualState;
};

#endif