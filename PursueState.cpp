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
	if (isFired && (dist < maxDist || dist > minDist)) {
		/* move between maxDist and minDist */
		float vx, vy;
		vx = target->getX() - e.getX();
		vy = target->getY() - e.getY();
		float length = sqrt(vx*vx + vy*vy);
		/* normalize */
		vx /= length;
		vy /= length;
		/* scale */
		vx *= v;
		vy *= v;
		e.setVX(vx);
		e.setVY(vy);
	} else {
		isFired = (dist <= alertDistance);
	}
}

bool PursueState::isTriggered()
{
	return isFired;
}