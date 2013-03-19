#pragma once
#include <vector>
#include "Bullet.h"

class Weapon
{
public:
	Weapon(void);
	Weapon(long reloadTime, float v, int w, int h, int bulletsPerShot = 1, float separationAngle = 0, float dispersionAngle = 0);
	~Weapon(void);
	bool fire(float x, float y, float dirX, float dirY, std::vector<Bullet> &v);
	void update();
	void setTicksMax(int x);
private:
	long waitToFire;
	long reloadTime;
	int bulletsPerShot;
	float separationAngle;
	int w;
	int h;
	float dispersionAngle;
	float v;
	float ticksMax;
};

