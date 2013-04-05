#include "DeathWall.h"


const float DeathWall::DEATH_WALL_VX = 0.0f;
const float DeathWall::DEATH_WALL_VY = 2.0f;

DeathWall::DeathWall() {}

DeathWall::DeathWall(int viewportWidth, int viewportHeight)
	: MobileGameObject(viewportWidth/2, -viewportHeight/2, GameData::DEATHWALL_SPRITE_INDEX, viewportWidth, viewportHeight, false, DEATH_WALL_VX, DEATH_WALL_VY)
{
	setDirection(UP);
	setAction(MOVE_UP);

	// TODO: Canviar per a matar a gent!
	setPhantom(true);
}

DeathWall::~DeathWall(void) {}
