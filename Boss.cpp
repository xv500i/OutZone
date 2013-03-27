#include "Boss.h"


Boss::Boss(void)
{
}

Boss::Boss(const float x, const float y, const int idTexture, const int width, const int length, const bool isWalkable, int life)
	: GameObject(x,y,idTexture, width, length, isWalkable), life(life)
{
	centerTail = BossTail(x,y,-1,width,length,true,100,7);
	leftTail = BossTail(x-100.0f,y,-1,width,length,true,100,5);
	rightTail = BossTail(x+100.0f,y,-1,width,length,true,100,5);
}


Boss::~Boss(void)
{
}

void Boss::update()
{
	GameObject::update();
	centerTail.update();
	leftTail.update();
	rightTail.update();
}

void Boss::render(GameData *data) const
{
	GameObject::render(data);
	centerTail.render(data);
	leftTail.render(data);
	rightTail.render(data);
}