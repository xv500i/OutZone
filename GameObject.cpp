
#include "GameObject.h"
#include <cmath>


int GameObject::current_id = 0;

GameObject::GameObject(const float x, const float y, const int spriteIndex, const int width, const int height, const bool isWalkable) 
	: x(x), y(y), spriteIndex(spriteIndex), width(width), height(height)
{
	phantom = true;
	this->b = new BoundingBox(y + height/2, y - height/2, x - width/2, x + width/2);
	type = 'u';
	action = STATIC;
	id = current_id++;
	spriteInstanceIndex = -1;
}

GameObject::GameObject() {}

GameObject::~GameObject(void) {}


/* Drawing */
void GameObject::render(GameData *data) const
{	
	if (spriteInstanceIndex >= 0) {
		float angle = getAngleVelocity();

		float offsetX, offsetY, s, t;
		int spriteWidth, spriteHeight;
		bool finished;
		data->getSpriteFrameInfo(spriteInstanceIndex, action, &finished, &s, &t, &spriteWidth, &spriteHeight, &offsetX, &offsetY);
		
		// Change the render size (a sprite can be bigger in pixels than the size that we have to render)
		int width, height;
		if (spriteWidth > spriteHeight) {
			height = STANDARD_SIZE;
			width = spriteWidth*((float)STANDARD_SIZE/(float)spriteHeight);
		}
		else if (spriteHeight > spriteWidth) {
			width = STANDARD_SIZE;
			height = spriteHeight*((float)STANDARD_SIZE/(float)spriteWidth);
		}
		else {
			width = STANDARD_SIZE;
			height = STANDARD_SIZE;
		}

		if (!finished) {
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, data->getSpriteID(spriteIndex));
			glPushMatrix();
			glTranslatef(x, y, 0.0f);
			glRotatef(angle, 0.0f, 0.0f, 1.0f);
			glBegin(GL_QUADS);
				// Bottom-left
				glTexCoord2f(s, t + offsetY);
				glVertex3i(-width/2 , -height/2, 1);
				// Top-left
				glTexCoord2f(s, t);
				glVertex3i(-width/2 , height/2, 1);
				// Top-right
				glTexCoord2f(s + offsetX, t);
				glVertex3i(width/2 , height/2, 1);
				// Bottom-right
				glTexCoord2f(s + offsetX, t + offsetY);
				glVertex3i(width/2 , -height/2, 1);	
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

void GameObject::setType(char type)
{
	this->type = type;
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