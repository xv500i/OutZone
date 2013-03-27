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
	ia = SWINGING;
	t = 100;
}


Boss::~Boss(void)
{
}

void Boss::update(std::vector<Bullet> &shots, float x, float y)
{
	switch(ia) {
	case SWINGING:
		if (t > 0) { 
			centerTail.update(shots);
			leftTail.update(shots);
			rightTail.update(shots);
		} else {
			t = 100 + ((int)rand())%25;
			ia = IDLE;
		}
		break;
	case IDLE:
		if (t <= 0) { 
			t = 100 + ((int)rand()) % 100;
			ia = FIRE_TO_PLAYER;
		}
		break;
	case FIRE_TO_PLAYER:
		if (t > 0) {
			if(t%9 == 0) centerTail.fireTo(shots,x,y);
			else if(t%9 == 3) leftTail.fireTo(shots,x,y);
			else if(t%9 == 6) rightTail.fireTo(shots,x,y);
		} else {
			t = 450 + ((int)rand()) % 100;
			ia = SWINGING;
		}
		break;
	}
	t--;
	GameObject::update();
}

void Boss::render(GameData *data) const
{
	GameObject::render(data);
	centerTail.render(data);
	leftTail.render(data);
	rightTail.render(data);
}