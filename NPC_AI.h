#pragma once

#ifndef NPC_AI_H
#define NPC_AI_H

#include <vector>
#include "GuardPathState.h"
#include "PursueState.h"
#include "Enemy.h"
#include "Bullet.h"

class Enemy;
class GuardPathState;
class PursueState;

class NPC_AI
{
public:
	NPC_AI(void);
	NPC_AI(int numberOfStates);
	NPC_AI(int numberOfStates, int initialState);
	NPC_AI(int numberOfStates, int numberOfTriggeredStates, int initialState);
	~NPC_AI(void);
	void update(std::vector<Bullet> &bullets, Enemy &e);
	void setState(int i, GuardPathState &e);
	void setTriggerState(int i, PursueState &e);
	void initialize();
private:
	int getFirstTriggeredState(Enemy &e);

	std::vector<PursueState> triggerStates;
	std::vector<GuardPathState> states;
	int actualState;
};

#endif