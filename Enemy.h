#pragma once
#include "mobilegameobject.h"
class Enemy :
	public MobileGameObject
{
public:
	Enemy(void);
	Enemy(const float x, const float y, const int idTexture, const int width, const int length, const bool isWalkable, const float vx = 0, const float vy = 0);
	~Enemy(void);
};

