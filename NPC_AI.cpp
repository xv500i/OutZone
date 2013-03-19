#include "NPC_AI.h"


NPC_AI::NPC_AI(void)
{
}

NPC_AI::NPC_AI(int numberOfStates)
{
	states = std::vector<State>(numberOfStates);
}

NPC_AI::~NPC_AI(void)
{
}

void NPC_AI::update(Enemy &e)
{
	
}
