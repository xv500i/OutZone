#include "Player.h"

//const long Player::fireDelayMsec = 20;

Player::Player(void)
{
}

Player::Player(const float x, const float y, const int idTexture, const int width, const int length, const bool isWalkable, const float vx, const float vy) : MobileGameObject(x, y, idTexture, width, length, isWalkable, vx, vy)
{
	//waitToFire = 0;
	mainWeapon = Weapon(10, 20, 3, 3);
}

Player::~Player(void)
{
}
/*
void Player::render() const
{
	// HARDCODED s'ha de fer amb la width i heigth
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_QUADS);
		glVertex2i(getX() - 8 , getY() - 8);
		glVertex2i(getX() - 8 , getY() + 8);
		glVertex2i(getX() + 8 , getY() + 8);
		glVertex2i(getX() + 8 , getY() - 8);
	glEnd();
}
*/
void Player::shotPrimaryWeapon(std::vector<MobileGameObject> &v) 
{

	
	//if (waitToFire > 0) return;
	float vx = 0.0f, vy = 0.0f;
	float catet = 10.0f;
	float absv = sqrt(catet*catet*2);
	Directions d = getDirection();
	switch (d) {
		case UP:
			vy = absv;
			break;
		case DOWN:
			vy = -absv;
			break;
		case LEFT:
			vx = -absv;
			break;
		case RIGHT:
			vx = absv;
			break;
		case UP_RIGHT:
			vx = catet;
			vy = catet;
			break;
		case DOWN_RIGHT:
			vx = catet;
			vy = -catet;
			break;
		case UP_LEFT:
			vx = -catet;
			vy = catet;
			break;
		case DOWN_LEFT:
			vx = -catet;
			vy = -catet;
			break;
	}
	//MobileGameObject* bala = new MobileGameObject(getX(), getY(), -1, 5, 5, true, vx, vy);
	//v.push_back(*bala);
	//waitToFire = fireDelayMsec;
	
	//std::pair<float, float> p(1.0f, 1.0f);
	mainWeapon.fire(getX(), getY(), vx, vy, v);
	
}

void Player::update()
{
	MobileGameObject::update();
	mainWeapon.update();
	//waitToFire = std::max(0L,waitToFire - 1);
}
