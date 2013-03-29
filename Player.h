
#pragma once

#include <vector>
#include "MobileGameObject.h"
#include "Weapon.h"
#include "Bullet.h"


class Player : public MobileGameObject
{
private:
	Weapon mainWeapon;

public:
	Player(void);
	Player(const float x, const float y, const int idTexture, const int width, const int length, const bool isWalkable, const float vx, const float vy);
	~Player(void);

	/* Drawing */
	void update(GameData *data, std::vector<GameObject> &collisionableObjects);

	void shotPrimaryWeapon(std::vector<Bullet> &v);
	void collision(GameObject &g);
};