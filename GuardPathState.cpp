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

bool GuardPathState::isFinished()
{
	return ticksLeft <= 0;
}

void GuardPathState::initialize()
{
	ticksLeft = ticksMax;
}

int GuardPathState::getTicksLeft()
{
	return ticksLeft;
}

int GuardPathState::getVX()
{
	return vx;
}

int GuardPathState::getVY()
{
	return vy;
}

void GuardPathState::update()
{
	ticksLeft--;
}
