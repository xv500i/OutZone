#include "State.h"


State::State(void)
{
}

State::~State(void)
{
}

bool State::isFinished()
{
	return true;
}
void State::initialize()
{
}

int State::getNextState() 
{
	return -1;
}

void State::update(Enemy &e)
{
	
}
