
#pragma once

#include <vector>
#include "MobileGameObject.h"
#include "Weapon.h"
#include "Bullet.h"
#include "InputHandler.h"
#include "Viewport.h"
#include "Enemy.h"
#include "BossTail.h"

class Enemy;


class Player : public MobileGameObject
{
private:
	const static float DEFAULT_PLAYER_VELOCITY;
	const static int MAX_LIFE = 5;
	const static int LANTERN_DEPTH = 3;

	Weapon mainWeapon;
	bool shooting;
	bool invul;
	bool lanternActivated;
	int ticksMaxInvul;
	int ticksInvul;
	int life;
	bool hasBeenHit;
	bool hasBeenKilled;
	bool winner;
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
	int update(GameData *data, Viewport *viewport, std::vector<GameObject> &collisionObjects, std::vector<GameObject> &interactiveObjects, std::vector<bool> &collisionTiles, std::vector<Enemy> &enemies, std::vector<BossTail*> &parts);

	/* Drawing */
	void render(GameData *data);

	/* Getters */
	bool isInvul() const;
	bool isDead() const;
	bool hasWon() const;
	int getLife() const;
	WeaponType getWeaponType();

	/* Setters */
	void setInvul();
	void incrementLife();
	void decrementLife();
	void kill();
	void changeWeapon(WeaponType type);
	void victory();
	void setLanternActivated(bool lantern);
};