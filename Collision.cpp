
#include "Collision.h"


Collision::Collision(void)
{
}

Collision::~Collision(void)
{
}

/* Rectangle with rectangle collision */
bool Collision::rectToRect(float left1, float right1, float bottom1, float top1,
						   float left2, float right2, float bottom2, float top2)
{
	if (left1 > right2 || right1 < left2 || bottom1 > top2 || top1 < bottom2) return false;
	else return true;
}
