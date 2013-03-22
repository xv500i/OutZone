#include "PursueState.h"
#include <cmath>

PursueState::PursueState(void)
{
}


PursueState::~PursueState(void)
{
}

PursueState::PursueState(Player &p, float alertDistance, float maxDist, float minDist, float v, bool firePermission, int reloadTime)
	: alertDistance(alertDistance), maxDist(maxDist), minDist(minDist), v(v), firePermission(firePermission), reloadTime(reloadTime)
{
	target = &p;
	isFired = false;
}


void PursueState::update(Enemy &e)
{
	float dist = e.distance(*target);
	float vx = 0.0f, vy = 0.0f;
	if (isFired && dist < maxDist && dist > minDist) {
		/* move between maxDist and minDist */
		vx = target->getX() - e.getX();
		vy = target->getY() - e.getY();
		float length = sqrt(vx*vx + vy*vy);
		/* normalize */
		vx /= length;
		vy /= length;
		/* scale */
		vx *= v;
		vy *= v;
	} else {
		vx = vy = 0.0f;
	}
	e.setVX(vx);
	e.setVY(vy);
}

bool PursueState::isTriggered(Enemy &e)
{
	float dist = e.distance(*target);
	isFired = isFired || (dist <= alertDistance);
	return isFired;
}