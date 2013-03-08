
#pragma once

#include <gl/glut.h>
#include "BoundingBox.h"


class GameObject
{
public:
	GameObject(void);
	GameObject(const float x, const float y, const int idTexture, const int width, const bool isWalkable);
	~GameObject(void);

	/* Drawing */
	void render() const;
	void update(long msec);

private:
	float x;
	float y;
	int idTexure;
	BoundingBox *b;
	int width;
	int length;
	bool isWalkable;
};

