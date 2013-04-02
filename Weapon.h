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
	long reloadTime;		/* Time between bullet shots */
	int bulletsPerShot;		/* Bullets shot in one shot */
	float separationAngle;	/* Separation angle between bullets (in case bulletsPerShot > 1) */
	float dispersionAngle;	/* Max angle separation between bullets */
	int bulletWidth;		/* Bullet width */
	int bulletHeight;		/* Bullet height */
	float bulletVelocity;	/* Bullet velocity */
	float ticksMax;			/* Time that a bullet lasts without dying */
	int spriteIndex;		/* Index of the sprite used by the weapon */
	WeaponType wt;
public:
	Weapon(void);
	Weapon(WeaponType type);
	Weapon(long reloadTime, float bulletVelocity, int bulletWidth, int bulletHeight, int spriteIndex, int bulletsPerShot = 1, float separationAngle = 0, float dispersionAngle = 0);
	~Weapon(void);

	/* Fire */
	bool fire(float x, float y, Direction dir, std::vector<Bullet> &v, GameData* data);

	/* Updating */
	void update();

	/* Setters */
	void setTicksMax(int x);
};