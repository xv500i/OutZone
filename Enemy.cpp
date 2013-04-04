
#include "Enemy.h"


Enemy::Enemy(void) {}

Enemy::Enemy(EnemyType type, const float x, const float y, const int spriteIndex, const int width, const int height)
	: MobileGameObject(x, y, spriteIndex, width, height, false)
{
	float v = 3.0f;
	int ticks = 60;
	GuardPathState *s1 = new GuardPathState(v, 0.0f, ticks);
	GuardPathState *s2 = new GuardPathState(0.0f, v, ticks);
	GuardPathState *s3 = new GuardPathState(-v, 0.0f, ticks);
	GuardPathState *s4 = new GuardPathState(0.0f, -v, ticks);
	guard.reserve(4);
	guard.push_back(*s1);
	guard.push_back(*s2);
	guard.push_back(*s3);
	guard.push_back(*s4);
	guardIndex = 0;
	guard[guardIndex].initialize();
	state = GUARD;
	detectionDistance = 300.0f;
	pursueVelocity = 2.0f;
	minDistance = 80.0f;
	minPursueDistance = 250.0f;

	/*
	ai = new NPC_AI(4,0);
	ai->setState(0, *s1);
	ai->setState(1, *s2);
	ai->setState(2, *s3);
	ai->setState(3, *s4);
	ai->initialize();
	*/
}

/*Enemy::Enemy(const float x, const float y, const int spriteIndex, const int width, const int height, const bool isWalkable, const float vx, const float vy)
	: MobileGameObject(x, y, spriteIndex, width, height, isWalkable, vx, vy)
{
	float v = 3.0f;
	int ticks = 60;
	GuardPathState *s1 = new GuardPathState(1, v, 0.0f, ticks);
	GuardPathState *s2 = new GuardPathState(2, 0.0f, v, ticks);
	GuardPathState *s3 = new GuardPathState(3, -v, 0.0f, ticks);
	GuardPathState *s4 = new GuardPathState(0, 0.0f, -v, ticks);
	ai = new NPC_AI(4,0);
	ai->setState(0, *s1);
	ai->setState(1, *s2);
	ai->setState(2, *s3);
	ai->setState(3, *s4);
	ai->initialize();
}*/

Enemy::Enemy(Player &p, const float x, const float y, const int spriteIndex, const int width, const int height, const bool isWalkable, const float vx, const float vy)
	: MobileGameObject(x, y, spriteIndex, width, height, isWalkable, vx, vy)
{
	//ai = new NPC_AI(0,1,0);
	PursueState *pur = new PursueState(p, 200.0f, 250.f, 50.0f, 2.0f);
	//ai->setTriggerState(0, *pur);
}

Enemy::Enemy(Player &p, int fireDelay, const float x, const float y, const int spriteIndex, const int width, const int height, const bool isWalkable, const float vx, const float vy)
	: MobileGameObject(x, y, spriteIndex, width, height, isWalkable, vx, vy)
{
	//ai = new NPC_AI(0,1,0);
	PursueState *pur = new PursueState(p, 200.0f, 250.f, 50.0f, 2.0f, true, fireDelay);
	//ai->setTriggerState(0, *pur);
}

Enemy::~Enemy(void) {}


/* Updating */
void Enemy::update(GameData *data, Viewport *viewport, std::vector<GameObject> &collisionObjects, std::vector<bool> &collisionTiles, Player &player)
{
	MobileGameObject::update(data, collisionObjects, collisionTiles);
	//ai->update(enemyShots, *this);
	float distanceToPlayer = distance(player);
	switch(state){
	case GUARD:
		if (guard[guardIndex].isFinished()) {
			// Agafar la seguent
			guardIndex = (guardIndex+1)%guard.size();
			guard[guardIndex].initialize();
		}
		// aplicar ruta
		guard[guardIndex].update();
		setVX(guard[guardIndex].getVX());
		setVY(guard[guardIndex].getVY());
		
		if (distanceToPlayer < detectionDistance) {
			state = ALERTED;
		}
		break;
	case ALERTED:
		float fvx = 0.0f;
		float fvy = 0.0f;


		if (distanceToPlayer < minPursueDistance) {
			// dins del rang d'accio
			float auxx = player.getX() - getX();
			float auxy = player.getY() - getY();
			float length = sqrt(auxx*auxx + auxy*auxy);
			/* normalize */
			float nvx = auxx/length;
			float nvy = auxy/length;
			// Si cal aproparse
			if (distanceToPlayer > minDistance) {
				/* scale */
				fvx = nvx*pursueVelocity;
				fvy = nvy*pursueVelocity;
			}
		}

		// TODO disparar si te permis
		setVX(fvx);
		setVY(fvy);
		break;
	}

	// TODO: No s'ha de fer collision amb el viewport, sino amb el nivell!
	int minX = viewport->getLeft();
	int maxX = viewport->getLeft() + viewport->getWidth();
	int minY = viewport->getTop() - viewport->getHeight();
	int maxY = viewport->getTop();
	if (getX() + getWidth()/2 > maxX) {
		float inc = maxX - getWidth()/2 - getX();
		updateBBox(inc, 0.0f);
		setX(maxX - getWidth()/2);
	}
	else if (getX() - getWidth()/2 < minX) {
		float inc = minX + getWidth()/2 - getX();
		updateBBox(inc, 0.0f);
		setX(minX + getWidth()/2);
	}
	/*if (getY() + getHeight()/2 > maxY) {
		float inc = maxY - getHeight()/2 - getY();
		updateBBox(0.0f, inc);
		setY(maxY - getHeight()/2);
	}
	else if (getY() - getHeight()/2 < minY) {
		float inc = minY + getHeight()/2 - getY();
		updateBBox(0.0f, inc);
		setY(minY + getHeight()/2);
	}*/

	// EnemyShots update
	for (std::vector<Bullet>::iterator it = enemyShots.begin(); it != enemyShots.end();) {
		std::vector<Player> players;
		players.push_back(player);
		bool collision = it->update(data, collisionObjects, collisionTiles, (std::vector<GameObject>&)players);

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


/* Drawing */
void Enemy::render(GameData *data)
{
	MobileGameObject::render(data);
	for (unsigned int i = 0; i < enemyShots.size(); i++) {
		enemyShots[i].render(data);
	}
}


/* Setters */
/*
void Enemy::setAI(NPC_AI *art)
{
	ai = art;
}
*/