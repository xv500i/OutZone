
#pragma once


class Collision
{
public:
	Collision(void);
	~Collision(void);

	/* Rectangle with rectangle collision */
	static bool rectToRect(float left1, float right1, float bottom1, float top1,
						   float left2, float right2, float bottom2, float top2);
};

