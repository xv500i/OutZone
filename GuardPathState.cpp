#include "GuardPathState.h"


GuardPathState::GuardPathState(void)
{
}

GuardPathState::GuardPathState(int nextState, float vx, float vy , int ticksMax) : nextState(nextState), vx(vx), vy(vy), ticksMax(ticksMax)
{
}


GuardPathState::~GuardPathState(void)
{
}

void GuardPathState::update(Enemy &e)
{
	if (ticksLeft > 0) ticksLeft--;
	e.setVX(vx);
	e.setVY(vy);
}

bool GuardPathState::isFinished()
{
	return ticksLeft <= 0;
}

void GuardPathState::initialize()
{
	ticksLeft = ticksMax;
}

int GuardPathState::getNextState()
{
	return nextState;
}
