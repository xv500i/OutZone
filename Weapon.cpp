#include "Weapon.h"

Weapon::Weapon(long reloadTime, float v, int w, int h, int bulletsPerShot, int separationAngle, int dispersionAngle)
	: waitToFire(waitToFire), reloadTime(reloadTime), v(v), w(w), h(h), bulletsPerShot(bulletsPerShot), separationAngle(separationAngle), dispersionAngle(dispersionAngle)
{
	waitToFire = 0;
}

Weapon::Weapon(void)
{
}

Weapon::~Weapon(void)
{
}

void Weapon::update()
{
	waitToFire = std::max(0L, waitToFire - 1);
}

bool Weapon::fire(float x, float y, float dirX, float dirY, std::vector<MobileGameObject> &v)
{
	if (waitToFire > 0) return false;
	MobileGameObject* bala = new MobileGameObject(x, y, -1, 5, 5, true, dirX, dirY);
	v.push_back(*bala);
	waitToFire = reloadTime;
	return true;
}
	