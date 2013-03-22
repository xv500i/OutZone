#include "NPC_AI.h"


NPC_AI::NPC_AI(void)
{
}

NPC_AI::NPC_AI(int numberOfStates)
{
	states = std::vector<GuardPathState>(numberOfStates);
	triggerStates = std::vector<PursueState>(0);
	actualState = 0;
}

NPC_AI::NPC_AI(int numberOfStates, int initialState) : actualState(initialState)
{
	states = std::vector<GuardPathState>(numberOfStates);
	triggerStates = std::vector<PursueState>(0);
}

NPC_AI::NPC_AI(int numberOfStates, int numberOfTriggeredStates, int initialState) : actualState(initialState)
{
	states = std::vector<GuardPathState>(numberOfStates);
	triggerStates = std::vector<PursueState>(numberOfTriggeredStates);
}

NPC_AI::~NPC_AI(void)
{
}

void NPC_AI::update(Enemy &e)
{
	int trigger = getFirstTriggeredState(e);
	if (trigger != -1) {
		triggerStates[trigger].update(e);
	} else if (states.size() > 0) {
		GuardPathState *s = &states[actualState];
		s->update(e);
		if (s->isFinished()) {
			actualState = s->getNextState();
			GuardPathState *next = &states[actualState];
			next->initialize();
		}
	}
}

void NPC_AI::initialize()
{
	if (states.size() > 0) {
		states[actualState].initialize();
	}
}

void NPC_AI::setState(int i, GuardPathState &s)
{
	states[i] = s;
}

void NPC_AI::setTriggerState(int i, PursueState &e)
{
	triggerStates[i] = e;
}

int NPC_AI::getFirstTriggeredState(Enemy &e)
{
	int res = -1;
	for (unsigned int i = 0; i < triggerStates.size() && res == -1; i++){
		if (triggerStates[i].isTriggered(e)) {
			res = i;
		}
	} 
	return res;
}