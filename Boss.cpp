#include "Boss.h"


Boss::Boss(void)
{
}

Boss::Boss(const float x, const float y, const int spriteIndex, const int width, const int height, const bool isWalkable, int life)
	: GameObject(x, y, spriteIndex, width, height, isWalkable), life(life)
{
	centerTail = BossTail(x, y, -1, width, height, true, 100, 7);
	leftTail = BossTail(x - 100.0f, y, -1, width, height, true, 100, 5);
	rightTail = BossTail(x + 100.0f, y, -1, width, height, true, 100, 5);
	ia = SWINGING;
	t = 100;
}


Boss::~Boss(void)
{
}

void Boss::update(GameData *data, std::vector<Bullet> &shots, float x, float y)
{
	switch(ia) {
	case SWINGING:
		if (t > 0) { 
			centerTail.update(data, shots);
			leftTail.update(data, shots);
			rightTail.update(data, shots);
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
			else if(t%9 == 1) leftTail.fireTo(shots,x,y);
			else if(t%9 == 2) rightTail.fireTo(shots,x,y);
		} else {
			t = 450 + ((int)rand()) % 100;
			ia = SWINGING;
		}
		break;
	}
	t--;
	GameObject::update(data);
}

void Boss::render(GameData *data) const
{
	GameObject::render(data);
	centerTail.render(data);
	leftTail.render(data);
	rightTail.render(data);
}