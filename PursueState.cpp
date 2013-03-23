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
	reloadLeft = 0;
}


void PursueState::update(std::vector<Bullet> &bullets, Enemy &e)
{
	reloadLeft = (reloadLeft <= 0 ? 0 : reloadLeft - 1);
	float dist = e.distance(*target);
	float vx = 0.0f, vy = 0.0f;
	if (isFired && dist < maxDist && dist > minDist) {
		/* move between maxDist and minDist */
		vx = target->getX() - e.getX();
		vy = target->getY() - e.getY();
		float length = sqrt(vx*vx + vy*vy);
		/* normalize */
		float nvx = vx/length;
		float nvy = vy/length;
		/* scale */
		vx = nvx*v;
		vy = nvy*v;
		if (firePermission && reloadLeft == 0) {
			//fireForward
			// HARDCODED
			float bulletV = 5.0f;
			Bullet *b = new Bullet(e.getX(), e.getY(), -1, 3, 3, true, nvx*bulletV, nvy*bulletV);
			// FIXME de moment escena no retira les bales
			b->setTicksLeft(50);
			bullets.push_back(*b);
			reloadLeft = reloadTime;
		}
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