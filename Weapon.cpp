#include "Weapon.h"
//#include "Vector2D.h"
#include <random>

Weapon::Weapon(long reloadTime, float v, int w, int h, int bulletsPerShot, float separationAngle, float dispersionAngle)
	: waitToFire(waitToFire), reloadTime(reloadTime), v(v), w(w), h(h), bulletsPerShot(bulletsPerShot), separationAngle(separationAngle), dispersionAngle(dispersionAngle)
{
	waitToFire = 0;
	ticksMax = -1;
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

bool Weapon::fire(float x, float y, float dirX, float dirY, std::vector<Bullet> &v)
{
	if (waitToFire > 0) return false;

	/* aply modifiers */
	
	//Vector2D dir(dirX, dirY);
	float LO = -dispersionAngle;
	float HI = dispersionAngle;
	float angle = LO + (float)rand()/((float)RAND_MAX/(HI-LO));
	//dir.Rotate(angle);
	float s = sinf(angle);
    float c = cosf(angle);
    
    float nx = c * dirX - s * dirY;
    float ny = s * dirX + c * dirY;
	Bullet* bala = new Bullet(x, y, GameData::FIRE_SPRITE_INDEX, w, h, true, nx, ny);
	bala->setPlayerAction(STATIC);	//TODO : HARDCODED! Hi ha que veure com fer lu del "PlayerAction" a sprite, ja que no tots els sprites son players!
	bala->setTicksLeft(ticksMax);
	v.push_back(*bala);
	waitToFire = reloadTime;
	return true;
}

void Weapon::setTicksMax(int x)
{
	ticksMax = x;
}
	