#pragma once
#include "mobilegameobject.h"
#include <iostream>
#include <algorithm>
#include <vector>

class Player :
	public MobileGameObject
{
public:
	Player(void);
	Player(const float x, const float y, const int idTexture, const int width, const int length, const bool isWalkable, const float vx, const float vy);
	~Player(void);
	//void render() const;
	void shotPrimaryWeapon(std::vector<MobileGameObject> &v);
	void update(long msec);

private:
	const static long fireDelayMsec;
	long waitToFire;
};

