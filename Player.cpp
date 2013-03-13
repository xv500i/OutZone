#include "Player.h"


Player::Player(void)
{
}

Player::Player(const float x, const float y, const int idTexture, const int width, const int length, const bool isWalkable, const float vx, const float vy) : MobileGameObject(x, y, idTexture, width, length, isWalkable, vx, vy)
{
	waitToFire = 0;
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
MobileGameObject* Player::shotPrimaryWeapon() const 
{
	if (waitToFire > 0) return NULL;
	float vx, vy;
	if (dir)
	MobileGameObject* bala = new MobileGameObject(getX(), getY(), -1, 5, 5, true, 0.0f, 0.0f);
	std::cout << "Beam" << std::endl;
	return bala;
}
