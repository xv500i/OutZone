#include "NPC_AI.h"


NPC_AI::NPC_AI(void)
{
}

NPC_AI::NPC_AI(int numberOfStates, int initialState) : actualState(initialState)
{
	states = std::vector<State>(numberOfStates);
}

NPC_AI::~NPC_AI(void)
{
}

void NPC_AI::update(Enemy &e)
{
	State *s = &states[actualState];
	s->update(e);
	if (s->isFinished()) {
		actualState = s->getNextState();
	}
}
