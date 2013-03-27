#include "Boss.h"


Boss::Boss(void)
{
}

Boss::Boss(const float x, const float y, const int idTexture, const int width, const int length, const bool isWalkable, int life)
	: GameObject(x,y,idTexture, width, length, isWalkable), life(life)
{
	centerTail = BossTail(x,y,-1,width,length,true,100,10);
}


Boss::~Boss(void)
{
}

void Boss::update()
{
	GameObject::update();
	centerTail.update();
}

void Boss::render(GameData *data) const
{
	GameObject::render(data);
	centerTail.render(data);
}