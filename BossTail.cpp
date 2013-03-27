#include "BossTail.h"


BossTail::BossTail(void)
{
}

BossTail::BossTail(const float x, const float y, const int idTexture, const int width, const int length, const bool isWalkable, int life, int nparts)
	: GameObject(x,y,idTexture, width, length, isWalkable), life(life)
{
	float yAux = y-length/2;
	parts = std::vector<BossPart>(nparts);
	for(int i = 0; i < nparts; i++) {
		parts[i] = BossPart(x,yAux,-1,20.f,20.f,true,100);
		yAux -= 20.0f;
	}
	bg = BossGun(x, yAux, -1, 30.0f, 30.0f, true, 100);
}

BossTail::~BossTail(void)
{
}

void BossTail::update()
{
	//GameObject::update();
	bg.update();
	float targetX = bg.getX(), targetY = bg.getY();
	float fx = parts[parts.size()-1].getX();
	float fy = parts[parts.size()-1].getY();
	bool end = std::abs(targetX-fx) < 0.01f && std::abs(targetY-fy) < 0.01f;
	parts[parts.size()-1].setLimits(bg.getX() + bg.getWidth(), bg.getY() + bg.getLength(), bg.getX() - bg.getWidth(), bg.getY() - bg.getLength());
	for(int i = parts.size()-1; i >= 0 && !end; i--) {
		float movedX = 0.0f, movedY = 0.0f;
		parts[i].moveTo(targetX, targetY, movedX, movedY);
		if ((unsigned)i < parts.size()-1) {
			parts[i+1].setLimits(parts[i].getX() + parts[i].getWidth(), parts[i].getY() + parts[i].getLength(), parts[i].getX() - parts[i].getWidth(), parts[i].getY() - parts[i].getLength());
		}
		targetX = parts[i].getX();
		targetY = parts[i].getY();
		end = std::abs(targetX) < 0.01f && std::abs(targetY) < 0.01f;
	}
}

void BossTail::render(GameData *data) const
{
	//GameObject::render(data);
	for(unsigned i = 0; i < parts.size(); i++) {
		parts[i].render(data);
	}
	bg.render(data);
}
