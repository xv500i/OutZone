
#pragma once

#include <gl/glut.h>
#include "BoundingBox.h"


class GameObject
{
public:
	GameObject(const float x, const float y, const int idTexture, const int width, const int length, const bool isWalkable);
	GameObject();
	~GameObject(void);

	/* Drawing */
	void render() const;
	void update();
	bool isIntersecting(const GameObject &go) const;
	void setX(const float x);
	void setY(const float y);
	float getX() const;
	float getY() const;
	int getWidth() const;
	int getLength() const;
	void setWidth(int x);
	void setLength(int x);

private:
	float x;
	float y;
	int idTexture;
	BoundingBox *b;
	int width;
	int length;
	bool isWalkable;
};

