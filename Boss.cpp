#include "Boss.h"


Boss::Boss(void)
{
}

Boss::Boss(const float x, const float y, const int spriteIndex, const int width, const int height, const bool isWalkable, int life)
	: GameObject(x, y, spriteIndex, width, height, isWalkable), life(life)
{
	centerTail = BossTail(x-2, y+100, -1, width, height, true, 400, 7);
	leftTail = BossTail(x - 100.0f, y+150, -1, width, height, true, 400, 5);
	rightTail = BossTail(x + 100.0f, y+150, -1, width, height, true, 400, 5);
	ia = SWINGING;
	t = 100;
	setAction(STATIC_UP);
}


Boss::~Boss(void)
{
}

void Boss::update(GameData *data, Viewport* viewport, std::vector<GameObject> &collisionObjects, std::vector<bool> &collisionTiles, Player &player)
{
	bool invulnerable = ia == FIRE_TO_PLAYER;
	centerTail.setInvul(invulnerable);
	leftTail.setInvul(invulnerable);
	rightTail.setInvul(invulnerable);
	float x = player.getX();
	float y = player.getY();

	switch(ia) {
	case SWINGING:
		if (t > 0) { 
			if (!centerTail.isDead()) centerTail.update(data, enemyShots);
			if (!leftTail.isDead()) leftTail.update(data, enemyShots);
			if (!rightTail.isDead()) rightTail.update(data, enemyShots);
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
			if(t%9 == 0 && centerTail.getLifes()>0) centerTail.fireTo(enemyShots,x,y);
			else centerTail.update(data, enemyShots);
			if(t%9 == 1 && leftTail.getLifes()>0) leftTail.fireTo(enemyShots,x,y);
			else leftTail.update(data, enemyShots);
			if(t%9 == 2 && rightTail.getLifes()>0) rightTail.fireTo(enemyShots,x,y);
			else rightTail.update(data, enemyShots);
		} else {
			t = 450 + ((int)rand()) % 100;
			ia = SWINGING;
		}
		break;
	}
	t--;
	GameObject::update(data);
	std::vector<GameObject*> players;
	players.push_back(&player);
	// EnemyShots update
	
	for (std::vector<Bullet>::iterator it = enemyShots.begin(); it != enemyShots.end();) {
		std::vector<GameObject*> players;
		players.push_back(&player);
		bool collision = it->update(data, collisionObjects, collisionTiles, players);

		// Remove the bullet if it goes off-screen
		float x = it->getX();
		float y = it->getY();	
		if (y > viewport->getTop() || y < (viewport->getTop() - viewport->getHeight()) || 
			x > (viewport->getLeft() + viewport->getWidth()) || x < viewport->getLeft()) {
			it = enemyShots.erase(it);
		} 
		// Remove the bullet if it has collisioned
		else if (collision || it->isDead()) {
			it = enemyShots.erase(it);
		}
		else it++;
	}
	
}

void Boss::render(GameData *data)
{
	
	if (!centerTail.isDead()) centerTail.render(data);
	if (!leftTail.isDead()) leftTail.render(data);
	if (!rightTail.isDead()) rightTail.render(data);
	GameObject::render(data);
	for(unsigned int i = 0; i < enemyShots.size(); i++) enemyShots[i].render(data);
}

bool Boss::isDead()
{
	return centerTail.isDead() && leftTail.isDead() && rightTail.isDead();	
}

std::vector<BossTail*> Boss::getAliveParts()
{
	std::vector<BossTail*> parts;
	parts.reserve(3);
	if (!centerTail.isDead()) parts.push_back(&centerTail);
	if (!leftTail.isDead()) parts.push_back(&leftTail);
	if (!rightTail.isDead()) parts.push_back(&rightTail);
	return parts;
}