#pragma once
#include "mobilegameobject.h"
class Player :
	public MobileGameObject
{
public:
	Player(void);
	Player(const float x, const float y, const int idTexture, const int width, const int length, const bool isWalkable, const float vx, const float vy);
	~Player(void);
	void render() const;

private:

};

