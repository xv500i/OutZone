
#include "Weapon.h"
#include <random>


Weapon::Weapon(WeaponType type)
{
	switch (type) {
	case SINGLE_SHOT:
		this->reloadTime = 6;
		this->width = 6;
		this->height = 6;
		this->spriteIndex = GameData::BULLET_SPRITE_INDEX;
		this->bulletsPerShot = 1;
		this->separationAngle = 0;
		this->dispersionAngle = 0;
		this->ticksMax = 40;
		break;
	case THREE_SHOTS:
		this->reloadTime = 6;
		this->width = 6;
		this->height = 6;
		this->spriteIndex = GameData::BULLET_SPRITE_INDEX;
		this->bulletsPerShot = 3;
		this->separationAngle = 20;
		this->dispersionAngle = 0;
		this->ticksMax = 40;
		break;
	case FIVE_SHOTS:
		this->reloadTime = 6;
		this->width = 6;
		this->height = 6;
		this->spriteIndex = GameData::BULLET_SPRITE_INDEX;
		this->bulletsPerShot = 5;
		this->separationAngle = 15;
		this->dispersionAngle = 0;
		this->ticksMax = 40;
	case FLAMETHROWER:
		this->reloadTime = 1;
		this->width = 15;
		this->height = 20;
		this->spriteIndex = GameData::FIRE_SPRITE_INDEX;
		this->bulletsPerShot = 1;
		this->separationAngle = 0;
		this->dispersionAngle = 0.15f;
		this->ticksMax = 25;
		break;
	default: break;
	}

	waitToFire = 0;
	ticksMax = -1;
}

Weapon::Weapon(long reloadTime, float v, int width, int height, int spriteIndex, int bulletsPerShot, float separationAngle, float dispersionAngle)
	: reloadTime(reloadTime), v(v), width(width), height(height), spriteIndex(spriteIndex), bulletsPerShot(bulletsPerShot), separationAngle(separationAngle), dispersionAngle(dispersionAngle)
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
	Bullet* bala = new Bullet(x, y, spriteIndex, width, height, true, nx, ny);
	bala->setAction(MOVE);
	bala->setTicksLeft(ticksMax);
	v.push_back(*bala);
	waitToFire = reloadTime;
	return true;
}

void Weapon::setTicksMax(int x)
{
	ticksMax = x;
}
	