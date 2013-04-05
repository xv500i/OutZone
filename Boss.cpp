#include "Boss.h"


Boss::Boss(void)
{
}

Boss::Boss(const float x, const float y, const int spriteIndex, const int width, const int height, const bool isWalkable, int life)
	: GameObject(x, y, spriteIndex, width, height, isWalkable), life(life)
{
	centerTail = BossTail(x-2, y+100, -1, width, height, true, 100, 7);
	leftTail = BossTail(x - 100.0f, y+150, -1, width, height, true, 100, 5);
	rightTail = BossTail(x + 100.0f, y+150, -1, width, height, true, 100, 5);
	ia = SWINGING;
	t = 100;
	setAction(STATIC_UP);
}


Boss::~Boss(void)
{
}

void Boss::update(GameData *data, Viewport* viewport, std::vector<GameObject> &collisionObjects, std::vector<bool> &collisionTiles, Player &player)
{
	float x = player.getX();
	float y = player.getY();
	switch(ia) {
	case SWINGING:
		if (t > 0) { 
			centerTail.update(data, enemyShots);
			leftTail.update(data, enemyShots);
			rightTail.update(data, enemyShots);
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
			if(t%9 == 0) centerTail.fireTo(enemyShots,x,y);
			else if(t%9 == 1) leftTail.fireTo(enemyShots,x,y);
			else if(t%9 == 2) rightTail.fireTo(enemyShots,x,y);
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
		else if (collision || it->isDead()) it = enemyShots.erase(it);
		else it++;
	}
}

void Boss::render(GameData *data)
{
	
	centerTail.render(data);
	leftTail.render(data);
	rightTail.render(data);
	GameObject::render(data);
	for(unsigned int i = 0; i < enemyShots.size(); i++) enemyShots[i].render(data);
}