#pragma once
#include <vector>
#include "Bullet.h"


enum WeaponType {
	SINGLE_SHOT,
	THREE_SHOTS,
	FIVE_SHOTS,
	FLAMETHROWER
};

class Weapon
{
private:
	long waitToFire;
	long reloadTime;
	int bulletsPerShot;
	float separationAngle;
	int width;
	int height;
	float dispersionAngle;
	float v;
	float ticksMax;
	int spriteIndex;

public:
	Weapon(void);
	Weapon(WeaponType type);
	Weapon(long reloadTime, float v, int width, int height, int spriteIndex, int bulletsPerShot = 1, float separationAngle = 0, float dispersionAngle = 0);
	~Weapon(void);
	bool fire(float x, float y, float dirX, float dirY, std::vector<Bullet> &v);
	void update();
	void setTicksMax(int x);
};

