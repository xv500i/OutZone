#pragma once
#include <vector>
#include "MobileGameObject.h"

class Weapon
{
public:
	Weapon(void);
	Weapon(long reloadTime, float v, int w, int h, int bulletsPerShot = 1, int separationAngle = 0, int dispersionAngle = 0);
	~Weapon(void);
	bool fire(float x, float y,float dirX, float dirY, std::vector<MobileGameObject> &v);
	void update();
private:
	long waitToFire;
	long reloadTime;
	int bulletsPerShot;
	int separationAngle;
	int w;
	int h;
	int dispersionAngle;
	float v;
};

