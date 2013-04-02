
#include "Weapon.h"
#include <random>


Weapon::Weapon(WeaponType type)
{
	weaponType = type;
	switch (type) {
	case SINGLE_SHOT:
		this->reloadTime = 20;
		this->bulletWidth = 6;
		this->bulletHeight = 6;
		this->bulletVelocity = 5;
		this->spriteIndex = GameData::BULLET_SPRITE_INDEX;
		this->bulletsPerShot = 1;
		this->separationAngle = 0;
		this->dispersionAngle = 0;
		this->ticksMax = 80;
		break;
	case THREE_SHOTS:
		this->reloadTime = 20;
		this->bulletWidth = 6;
		this->bulletHeight = 6;
		this->bulletVelocity = 5;
		this->spriteIndex = GameData::BULLET_SPRITE_INDEX;
		this->bulletsPerShot = 3;
		this->separationAngle = 15;
		this->dispersionAngle = 0;
		this->ticksMax = 80;
		break;
	case FIVE_SHOTS:
		this->reloadTime = 20;
		this->bulletWidth = 6;
		this->bulletHeight = 6;
		this->bulletVelocity = 5;
		this->spriteIndex = GameData::BULLET_SPRITE_INDEX;
		this->bulletsPerShot = 5;
		this->separationAngle = 10;
		this->dispersionAngle = 0;
		this->ticksMax = 80;
		break;
	case FLAMETHROWER:
		this->reloadTime = 1;
		this->bulletWidth = 15;
		this->bulletHeight = 20;
		this->bulletVelocity = 10;
		this->spriteIndex = GameData::FIRE_SPRITE_INDEX;
		this->bulletsPerShot = 1;
		this->separationAngle = 0;
		this->dispersionAngle = 10;
		this->ticksMax = 20;
		break;
	default: break;
	}

	waitToFire = 0;
}

Weapon::Weapon(long reloadTime, float bulletVelocity, int bulletWidth, int bulletHeight, int spriteIndex, int bulletsPerShot, float separationAngle, float dispersionAngle)
	: reloadTime(reloadTime), bulletVelocity(bulletVelocity), bulletWidth(bulletWidth), bulletHeight(bulletHeight), spriteIndex(spriteIndex), bulletsPerShot(bulletsPerShot), separationAngle(separationAngle), dispersionAngle(dispersionAngle)
{
	waitToFire = 0;
	ticksMax = -1;
}

Weapon::Weapon(void) {}

Weapon::~Weapon(void) {}


/* Fire */
bool Weapon::fire(float x, float y, Direction dir, std::vector<Bullet> &v)
{
	if (waitToFire > 0) return false;

	// Calculate velocity (depending on the direction)
	float vx = 0.0f, vy = 0.0f;
	float catet = bulletVelocity;
	float hipotenusa = sqrt(catet*catet*2);

	switch (dir) {
	case UP:		vy = hipotenusa; break;
	case DOWN:		vy = -hipotenusa; break;
	case LEFT:		vx = -hipotenusa; break;
	case RIGHT:		vx = hipotenusa; break;
	case UP_RIGHT:	vx = catet; vy = catet; break;
	case DOWN_RIGHT:vx = catet; vy = -catet; break;
	case UP_LEFT:	vx = -catet; vy = catet; break;
	case DOWN_LEFT:	vx = -catet; vy = -catet; break;
	}

	// Calculate angle
 	float totalAngle = (bulletsPerShot - 1)*separationAngle;	// Angle between the first and last bullet
	float halfAngle = totalAngle/2;								// Angle between the front player direction and the last (or first) bullet

	for (int i = 0; i < bulletsPerShot; i++) {
		float angle = halfAngle - i*separationAngle;		// Angle of this particular bullet
		
		// Dispersion
		float LO = angle - dispersionAngle;
		float HI = angle + dispersionAngle;
		angle = LO + (float)rand()/((float)RAND_MAX/(HI - LO));

		float fconv = 3.1415926f/180.0f;
		float s = sinf(angle*fconv);
		float c = cosf(angle*fconv);
		float nx = c*vx - s*vy;
		float ny = s*vx + c*vy;

		Bullet* bala = new Bullet(x, y, spriteIndex, bulletWidth, bulletHeight, true, nx, ny);
		bala->setTicksLeft(ticksMax);
		v.push_back(*bala);
	}

	waitToFire = reloadTime;
	return true;
}

/* Updating */
void Weapon::update()
{
	waitToFire = std::max(0L, waitToFire - 1);
}

/* Setters */
void Weapon::setTicksMax(int x)
{
	ticksMax = x;
}
	