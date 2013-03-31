
#include "Player.h"


const float Player::DEFAULT_PLAYER_VELOCITY = 2.0f;

Player::Player(void) {}

Player::Player(const float x, const float y, const int spriteIndex, const int width, const int height, const bool isWalkable, const float vx, const float vy) 
	: MobileGameObject(x, y, spriteIndex, width, height, isWalkable, vx, vy)
{
	mainWeapon = Weapon(3, 10, 30, 30, 1, 0.0f, 0.2f);
	mainWeapon.setTicksMax(30);
	setType('p');
}

Player::~Player(void) {}


/* Input */
void Player::resolveInput(InputHandler *input)
{
	// Velocity change
	bool up = input->keyIsDown(input->getMoveUpKey());
	bool down = input->keyIsDown(input->getMoveDownKey());
	bool left = input->keyIsDown(input->getMoveLeftKey());
	bool right = input->keyIsDown(input->getMoveRightKey());

	Direction dir;
	if (up) {
		if (right) dir = UP_RIGHT;	
		else if (left) dir = UP_LEFT;
		else dir = UP;
	} 
	else if (down) {
		if (right) dir = DOWN_RIGHT;
		else if (left) dir = DOWN_LEFT;
		else dir = DOWN;
	}
	else if (right) dir = RIGHT;
	else if (left) dir = LEFT;
	
	float vx = 0.0f, vy = 0.0f;
	float catet = DEFAULT_PLAYER_VELOCITY;
	float hipotenusa = sqrt(catet*catet*2);
	if (up || down || left || right) {
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
	}
	setVX(vx);
	setVY(vy);

	// Shooting
	if (input->keyIsDown(input->getPrimaryWeaponKey())) {
		shotPrimaryWeapon();
	}
}

void Player::shotPrimaryWeapon() 
{
	float vx = 0.0f, vy = 0.0f;
	float catet = Bullet::DEFAULT_BULLET_VELOCITY;
	float hipotenusa = sqrt(catet*catet*2);

	Direction dir = getDirection();
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

	mainWeapon.fire(getX(), getY(), vx, vy, playerShots);
	setAction(SHOT);
}


/* Updating */
void Player::update(GameData *data, std::vector<GameObject> &collisionableObjects)
{
	MobileGameObject::update(data, collisionableObjects);
	mainWeapon.update();
}


/* Drawing */
void Player::render(GameData *data)
{
	MobileGameObject::render(data);
	for (unsigned int i = 0; i < playerShots.size(); i++) {
		playerShots[i].render(data);
	}
}


void Player::collision(GameObject &g) {}