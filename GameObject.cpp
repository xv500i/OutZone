
#include "GameObject.h"

GameObject::GameObject(const float x, const float y, const int idTexture, const int width, const bool isWalkable)
{
	this->x = x;
	this->y = y;
	this->idTexure = idTexture;
	this->b = new BoundingBox(y+length/2, y-length/2, x-width/2, x+width/2);
}

GameObject::~GameObject(void)
{
}

/* Drawing */
void GameObject::render() const
{
}

void GameObject::update(long msec)
{

}

bool GameObject::isIntersecting(const GameObject &go) const 
{
	return b->isIntersectedBy(*(go.b));
}

void GameObject::setX(const float x)
{
	this->x = x;
}

void GameObject::setY(const float y)
{
	this->y = y;
}

float GameObject::getX() const
{
	return x;
}

float GameObject::getY() const
{
	return y;
}

