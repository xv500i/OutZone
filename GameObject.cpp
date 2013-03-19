
#include "GameObject.h"

GameObject::GameObject(const float x, const float y, const int idTexture, const int width, const int length, const bool isWalkable) : x(x), y(y), idTexture(idTexture), width(width), length(length)
{
	phantom = true;
	this->b = new BoundingBox(y+length/2, y-length/2, x-width/2, x+width/2);
	type = 'u';
}

GameObject::GameObject()
{

}

GameObject::~GameObject(void)
{
}

/* Drawing */
void GameObject::render() const
{
	glColor3f(1.0f, 1.0f, 1.0f);
	glPushMatrix();
	glTranslatef(getX(), getY(), 0.0f);
	glBegin(GL_QUADS);
		glVertex3i(- width/2 , - length/2, 1);
		glVertex3i(- width/2 , + length/2, 1);
		glVertex3i(+ width/2 , + length/2, 1);
		glVertex3i(+ width/2 , - length/2, 1);
	glEnd();
	glPopMatrix();
}

void GameObject::update()
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

int GameObject::getWidth() const
{
	return width;
}

int GameObject::getLength() const
{
	return length;
}
void GameObject::setWidth(int x)
{
	width = x;
}
void GameObject::setLength(int x)
{
	length = x;
}

void GameObject::updateBBox(const float x, const float y)
{
	b->translate(x,y);
}

BoundingBox* GameObject::getBoundingBox() const
{
	return b;
}

void GameObject::collision(GameObject &g)
{
	
}

char GameObject::getType() const
{
	return type;
}

bool GameObject::shouldNotEnterObjects() const
{
	return !phantom;
}

void GameObject::setPhantom(bool b)
{
	phantom = b;
}
