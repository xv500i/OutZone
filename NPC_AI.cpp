#include "NPC_AI.h"


NPC_AI::NPC_AI(void)
{
}

NPC_AI::NPC_AI(int numberOfStates, int initialState) : actualState(initialState)
{
	states = std::vector<GuardPathState>(numberOfStates);
}

NPC_AI::~NPC_AI(void)
{
}

void NPC_AI::update(Enemy &e)
{
	GuardPathState *s = &states[actualState];
	s->update(e);
	if (s->isFinished()) {
		actualState = s->getNextState();
		GuardPathState *next = &states[actualState];
		next->initialize();
	}
}

void NPC_AI::initialize()
{
	states[actualState].initialize();
}

void NPC_AI::setState(int i, GuardPathState &s)
{
	states[i] = s;
}
