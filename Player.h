
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
	bool shooting;
	bool invul;
	bool lanternActivated;
	int ticksMaxInvul;
	int ticksInvul;
	std::vector<Bullet> playerShots;

	void shotPrimaryWeapon();
	void renderLantern(int idTexture);
public:
	Player(void);
	Player(const float x, const float y, const int spriteIndex, const int width, const int height, const bool isWalkable, const float vx, const float vy);
	~Player(void);

	/* Input */
	void resolveInput(InputHandler *input);

	/* Updating */
	void update(GameData *data, Viewport *viewport, std::vector<GameObject> &collisionObjects, std::vector<bool> &collisionTiles, std::vector<Enemy> &enemies);

	/* Drawing */
	void render(GameData *data);

	bool isInvul() const;
	void setInvul();
};