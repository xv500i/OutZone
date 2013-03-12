
#pragma once

#include <gl/glut.h>
#include "BoundingBox.h"


class GameObject
{
public:
	GameObject(const float x, const float y, const int idTexture, const int width, const bool isWalkable);
	~GameObject(void);

	/* Drawing */
	void render() const;
	void update(long msec);
	bool isIntersecting(const GameObject &go) const;
	void setX(const float x);
	void setY(const float y);
	float getX() const;
	float getY() const;

private:
	float x;
	float y;
	int idTexure;
	BoundingBox *b;
	int width;
	int length;
	bool isWalkable;
};

