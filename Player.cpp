
#include "Player.h"


Player::Player(void) {}

Player::Player(const float x, const float y, const int spriteIndex, const int width, const int height, const bool isWalkable, const float vx, const float vy) 
	: MobileGameObject(x, y, spriteIndex, width, height, isWalkable, vx, vy)
{
	mainWeapon = Weapon(3, 10, 30, 30, 1, 0.0f, 0.2f);
	mainWeapon.setTicksMax(15);
	setType('p');
}

Player::~Player(void) {}


/* Drawing */
void Player::update(GameData *data, std::vector<GameObject> &collisionableObjects)
{
	MobileGameObject::update(data, collisionableObjects);
	mainWeapon.update();
}

void Player::shotPrimaryWeapon(std::vector<Bullet> &v) 
{
	float vx = 0.0f, vy = 0.0f;
	float catet = 10.0f;
	float absv = sqrt(catet*catet*2);

	Direction d = getDirection();
	switch (d) {
	case UP:		vy = absv; break;
	case DOWN:		vy = -absv; break;
	case LEFT:		vx = -absv; break;
	case RIGHT:		vx = absv; break;
	case UP_RIGHT:	vx = catet; vy = catet; break;
	case DOWN_RIGHT:vx = catet; vy = -catet; break;
	case UP_LEFT:	vx = -catet; vy = catet; break;
	case DOWN_LEFT:	vx = -catet; vy = -catet; break;
	}

	mainWeapon.fire(getX(), getY(), vx, vy, v);
	setAction(SHOT);
}




void Player::collision(GameObject &g) {}