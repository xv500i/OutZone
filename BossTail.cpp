#include "BossTail.h"


BossTail::BossTail(void)
{
}

BossTail::BossTail(const float x, const float y, const int spriteIndex, const int width, const int height, const bool isWalkable, int life, int nparts)
	: GameObject(x, y, spriteIndex, width, height, isWalkable), life(life)
{
	float yAux = y - height/2;
	parts = std::vector<BossPart>(nparts);
	for(int i = 0; i < nparts; i++) {
		int idSprite;
		if (i == 0) {
			idSprite = GameData::TENTACLE_BASE_TEX_INDEX;
		} else {
			idSprite = GameData::TENTACLE_TEX_INDEX;
		}
		parts[i] = BossPart(x,yAux,idSprite,20.f,20.f,true,100);
		yAux -= 20.0f;
	}
	bg = BossGun(x, yAux, GameData::TENTACLE_GUN_TEX_INDEX, 30.0f, 30.0f, true, 100);
}

BossTail::~BossTail(void)
{
}

void BossTail::update(GameData *data, std::vector<Bullet> &shots)
{
	GameObject::update(data);
	bg.update(data, shots);
	for(unsigned int j = 0; j < parts.size(); j++) parts[j].update(data);
	float targetX = bg.getX(), targetY = bg.getY();
	float fx = parts[parts.size()-1].getX();
	float fy = parts[parts.size()-1].getY();
	bool end = std::abs(targetX-fx) < 0.01f && std::abs(targetY-fy) < 0.01f;
	parts[parts.size()-1].setLimits(bg.getX() + bg.getWidth(), bg.getY() + bg.getHeight(), bg.getX() - bg.getWidth(), bg.getY() - bg.getHeight());
	for(int i = parts.size()-1; i >= 0 && !end; i--) {
		float movedX = 0.0f, movedY = 0.0f;
		parts[i].moveTo(targetX, targetY, movedX, movedY);
		if ((unsigned)i < parts.size()-1) {
			parts[i+1].setLimits(parts[i].getX() + parts[i].getWidth(), parts[i].getY() + parts[i].getHeight(), parts[i].getX() - parts[i].getWidth(), parts[i].getY() - parts[i].getHeight());
		}
		targetX = parts[i].getX();
		targetY = parts[i].getY();
		end = std::abs(targetX) < 0.01f && std::abs(targetY) < 0.01f;
	}
}

void BossTail::render(GameData *data)
{
	//GameObject::render(data);
	bg.render(data);
	for(int i = parts.size()-1; i >= 0; i--) {
		parts[i].render(data);
	}
	
}

void BossTail::fireTo(std::vector<Bullet> &shots, float x, float y)
{
	float v = 10.0f;
	float LO = -30.0f;
	float HI = 30.0f;
	float ix = x - bg.getX() + LO + (float)rand()/((float)RAND_MAX/(HI-LO));
	float iy = y - bg.getY()-bg.getHeight()/2 + LO + (float)rand()/((float)RAND_MAX/(HI-LO));
	float modul = sqrt(ix*ix + iy*iy);
	float vx = ix/modul*v;
	float vy = iy/modul*v;
	Bullet *b = new Bullet(bg.getX(), bg.getY()-bg.getHeight()/2, GameData::BULLET_SPRITE_INDEX, 8, 8, true, vx, vy);
	b->setTicksLeft(150);
	shots.push_back(*b);
}
