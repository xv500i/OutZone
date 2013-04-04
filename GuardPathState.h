#pragma once

#ifndef STATE_G_H
#define STATE_G_H

class GuardPathState
{
public:
	GuardPathState(void);
	GuardPathState(float vx, float vy, int ticksMax);
	~GuardPathState(void);
	bool isFinished();
	void update();
	void initialize();
	int getTicksLeft();
	float getVX();
	float getVY();

private:
	int ticksLeft;
	int ticksMax;
	float vx;
	float vy;
};

#endif