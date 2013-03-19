#include "GuardPathState.h"


GuardPathState::GuardPathState(void)
{
}

GuardPathState::GuardPathState(float vx, float vy , int ticksMax) : vx(vx), vy(vy), ticksMax(ticksMax)
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
