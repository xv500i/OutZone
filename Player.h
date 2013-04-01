
#pragma once

#include <vector>
#include "MobileGameObject.h"
#include "Weapon.h"
#include "Bullet.h"
#include "InputHandler.h"
#include "Viewport.h"
#include "Enemy.h"

class Enemy;


class Player : public MobileGameObject
{
private:
	const static float DEFAULT_PLAYER_VELOCITY;

	Weapon mainWeapon;
	std::vector<Bullet> playerShots;

	void shotPrimaryWeapon();

public:
	Player(void);
	Player(const float x, const float y, const int spriteIndex, const int width, const int height, const bool isWalkable, const float vx, const float vy);
	~Player(void);

	/* Input */
	void resolveInput(InputHandler *input);

	/* Updating */
	void update(GameData *data, Viewport *viewport, std::vector<GameObject> &collisionObjects, std::vector<Enemy> &enemies);

	/* Drawing */
	void render(GameData *data);

	void collision(GameObject &g);
};