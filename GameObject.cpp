
#include "GameObject.h"
#include <cmath>


int GameObject::current_id = 0;

GameObject::GameObject(const float x, const float y, const int spriteIndex, const int width, const int height, const bool isWalkable, int depth) 
	: x(x), y(y), spriteIndex(spriteIndex), width(width), height(height), depth(depth)
{
	phantom = false;
	interactive = false;
	this->b = new BoundingBox(y + height/2, y - height/2, x - width/2, x + width/2);
	type = 'u';
	action = STATIC_DOWN;
	id = current_id++;
	spriteInstanceIndex = -1;
}

GameObject::GameObject() {}

GameObject::~GameObject(void) {}


/* Drawing */
void GameObject::render(GameData *data)
{	
	if (spriteInstanceIndex >= 0) {
		//float angle = getAngleVelocity();

		float s, t, offsetX, offsetY, angle;
		int width, height, tx, ty;
		data->getSpriteFrameInfo(spriteInstanceIndex, action, &animationFinished, &s, &t, &offsetX, &offsetY, &width, &height, &tx, &ty, &angle);

		if (!animationFinished) {
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, data->getSpriteID(spriteIndex));
			glPushMatrix();
			glTranslatef(x, y, 0.0f);			// Move the game object to his position
			glRotatef(angle, 0.0f, 0.0f, 1.0f);	// Rotate the object as needed by the sprite
			glTranslatef(tx, ty, 0.0f);			// Move the object as needed by the sprite
			glBegin(GL_QUADS);
				// Bottom-left
				glTexCoord2f(s, t + offsetY);
				glVertex3i(-width/2 , -height/2, depth);
				// Top-left
				glTexCoord2f(s, t);
				glVertex3i(-width/2 , height/2, depth);
				// Top-right
				glTexCoord2f(s + offsetX, t);
				glVertex3i(width/2 , height/2, depth);
				// Bottom-right
				glTexCoord2f(s + offsetX, t + offsetY);
				glVertex3i(width/2 , -height/2, depth);
			glEnd();
			glPopMatrix();
			glDisable(GL_TEXTURE_2D);
		}
	}
}

void GameObject::update(GameData *data) 
{
	if (spriteInstanceIndex < 0) spriteInstanceIndex = data->createSpriteInstance(spriteIndex);
}


/* Getters */
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

int GameObject::getHeight() const
{
	return height;
}

SpriteAction GameObject::getAction() const
{
	return action;
}

BoundingBox* GameObject::getBoundingBox() const
{
	return b;
}

bool GameObject::shouldNotEnterObjects() const
{
	return !phantom;
}

bool GameObject::isInteractive() const
{
	return interactive;
}

bool GameObject::isAnimationFinished() const
{
	return animationFinished;
}

char GameObject::getType() const
{
	return type;
}

int GameObject::getId()
{
	return id;
}


/* Setters */
void GameObject::setX(const float x)
{
	this->x = x;
}

void GameObject::setY(const float y)
{
	this->y = y;
}

void GameObject::setWidth(int width)
{
	this->width = width;
}

void GameObject::setHeight(int height)
{
	this->height = height;
}

void GameObject::setAction(SpriteAction action)
{
	this->action = action;
}

void GameObject::setPhantom(bool phantom)
{
	this->phantom = phantom;
}

void GameObject::setInteractive(bool interactive)
{
	this->interactive = interactive;
}

void GameObject::setType(char type)
{
	this->type = type;
}

void GameObject::setSpriteIndex(int spriteIndex)
{
	this->spriteIndex = spriteIndex;
	this->spriteInstanceIndex = -1;
}

bool GameObject::isIntersecting(const GameObject &go) const 
{
	return b->isIntersectedBy(*(go.b));
}

void GameObject::updateBBox(const float x, const float y)
{
	b->translate(x,y);
}

float GameObject::distance(GameObject &g)
{
	return sqrt(pow(x-g.x,2) + pow(y-g.y,2));
}

float GameObject::getAngleVelocity() const
{
	return 0.0f;
}