#include "DeathWall.h"


const float DeathWall::DEATH_WALL_VX = 0.0f;
const float DeathWall::DEATH_WALL_VY = 2.0f;

DeathWall::DeathWall() {}

DeathWall::DeathWall(int viewportWidth, int viewportHeight)
	: MobileGameObject(viewportWidth/2, -viewportHeight/2, GameData::DEATHWALL_SPRITE_INDEX, viewportWidth, viewportHeight - 64, false, DEATH_WALL_VX, DEATH_WALL_VY)
{
	setDirection(UP);
	setAction(MOVE_UP);

	setPhantom(true);
}

DeathWall::~DeathWall(void) {}


/* Updating */
bool DeathWall::update(GameData *data, std::vector<Enemy> &enemies, Player &player) {
	GameObject::update(data);

	// Collision with enemy and player
	setX(getX() + getVX());
	setY(getY() + getVY());
	updateBBox(getVX(), getVY());

	for (std::vector<Enemy>::iterator ito = enemies.begin(); ito != enemies.end(); ito++) {
		if (getId() != ito->getId() && isIntersecting(*ito)) {
			ito->kill();
		}
	}
	if (getId() != player.getId() && isIntersecting(player)) {
		player.kill();
	}

	return true;
}
