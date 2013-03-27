#include "BossPart.h"


BossPart::BossPart(void)
{
}

BossPart::BossPart(const float x, const float y, const int idTexture, const int width, const int length, const bool isWalkable, int life)
	: GameObject(x,y,idTexture, width, length, isWalkable), life(life)
{
	maxX = x + width/2;
	minX = x - width/2;
	maxY = y + length/2;
	minY = y - length/2;
}


BossPart::~BossPart(void)
{
}

void BossPart::update()
{
	GameObject::update();
}

void BossPart::render(GameData *data) const
{
	GameObject::render(data);
}

void BossPart::moveTo(float x, float y, float &ix, float iy)
{
	float realx = std::max(std::min(maxX, x), minX);
	float realy = std::max(std::min(maxY, y), minY);
	ix = getX() - realx;
	iy = getY() - realy;
	setX(realx);
	setY(realy);
}

void BossPart::setLimits(float maxX, float maxY, float minX, float minY)
{
	this->maxY = maxY;
	this->minY = minY;
	this->minX = minX;
	this->maxX = maxX;
}