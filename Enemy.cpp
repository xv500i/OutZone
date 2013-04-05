
#include "Enemy.h"


Enemy::Enemy(void) {}

Enemy::Enemy(EnemyType type, const float x, const float y, const int width, const int height, std::vector<GuardPathState> &gps, int spriteIndex)
	: MobileGameObject(x, y, spriteIndex, width, height, false)
{
	guard = gps;
	switch(type) {
	case BAT_1:
		setSpriteIndex(GameData::ALIEN1_SPRITE_INDEX);
		life = 20;
		detectionDistance = 300.0f;
		pursue = false;
		firePermission = false;
		pursueVelocity = 2.0f;
		minDistance = 150.0f;
		minPursueDistance = 250.0f;
		gunVelocity = 4.0f;
		weapon = Weapon(ENEMY_BASIC_WEAPON);
		break;
	case BAT_2:
		setSpriteIndex(GameData::ALIEN2_SPRITE_INDEX);
		life = 30;
		detectionDistance = 200.0f;
		pursue = false;
		firePermission = true;
		pursueVelocity = 2.0f;
		minDistance = 150.0f;
		minPursueDistance = 250.0f;
		gunVelocity = 5.0f;
		weapon = Weapon(FLAMETHROWER);
		break;
	case BAT_3:
		setSpriteIndex(GameData::ALIEN3_SPRITE_INDEX);
		life = 40;
		detectionDistance = 400.0f;
		pursue = true;
		firePermission = true;
		pursueVelocity = 2.0f;
		minDistance = 150.0f;
		minPursueDistance = 350.0f;
		gunVelocity = 4.0f;
		weapon = Weapon(ENEMY_BASIC_WEAPON);
		break;
	case SPIDER_1:
		setSpriteIndex(GameData::SPIDER1_SPRITE_INDEX);
		life = 20;
		detectionDistance = 200.0f;
		pursue = true;
		firePermission = false;
		pursueVelocity = 2.0f;
		minDistance = 10.0f;
		minPursueDistance = 400.0f;
		gunVelocity = 4.0f;
		weapon = Weapon(ENEMY_BASIC_WEAPON);
		break;
	case SPIDER_2:
		setSpriteIndex(GameData::SPIDER2_SPRITE_INDEX);
		life = 30;
		detectionDistance = 600.0f;
		pursue = true;
		firePermission = false;
		pursueVelocity = 4.0f;
		minDistance = 10.0f;
		minPursueDistance = 800.0f;
		gunVelocity = 4.0f;
		weapon = Weapon(ENEMY_BASIC_WEAPON);
		break;
	}
	
	/*
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
	*/
	
	if (guard.size() > 0) {
		guardIndex = 0;
		guard[guardIndex].initialize();
	}
	else guardIndex = -1;
	state = GUARD;
	hasBeenHit = false;
	hasBeenKilled = false;
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

/*Enemy::Enemy(Player &p, const float x, const float y, const int spriteIndex, const int width, const int height, const bool isWalkable, const float vx, const float vy)
	: MobileGameObject(x, y, spriteIndex, width, height, isWalkable, vx, vy)
{
	//ai = new NPC_AI(0,1,0);
	//PursueState *pur = new PursueState(p, 200.0f, 250.f, 50.0f, 2.0f);
	//ai->setTriggerState(0, *pur);
}*/

/*Enemy::Enemy(Player &p, int fireDelay, const float x, const float y, const int spriteIndex, const int width, const int height, const bool isWalkable, const float vx, const float vy)
	: MobileGameObject(x, y, spriteIndex, width, height, isWalkable, vx, vy)
{
	//ai = new NPC_AI(0,1,0);
	//PursueState *pur = new PursueState(p, 200.0f, 250.f, 50.0f, 2.0f, true, fireDelay);
	//ai->setTriggerState(0, *pur);
}*/

Enemy::~Enemy(void) {}


/* Updating */
void Enemy::update(GameData *data, Viewport *viewport, std::vector<GameObject> &collisionObjects, std::vector<bool> &collisionTiles, Player &player)
{
	if (isDead()) {
		if (hasBeenKilled) {
			enemyShots.clear();
			data->playSound(GameData::EXPLOSION_INDEX);
			hasBeenKilled = false;
		}
		GameObject::update(data);
		return;
	}
	if (hasBeenHit) {
		hasBeenHit = false;
		data->playSound(GameData::ENEMY_OUCH_INDEX);
	}

	// If collision with Player, decrement life
	updateBBox(getVX(), getVY());
	if (isIntersecting(player)) {
 		player.decrementLife();
	}
	updateBBox(-getVX(), -getVY());
	MobileGameObject::update(data, collisionObjects, collisionTiles);
	weapon.update();

	float distanceToPlayer = distance(player);
	float auxx = player.getX() - getX();
	float auxy = player.getY() - getY();
	float length = sqrt(auxx*auxx + auxy*auxy);
	/* normalize */
	float nvx = auxx/length;
	float nvy = auxy/length;
	switch(state){
	case GUARD:
		if (guardIndex == -1) {
			setVX(0.0f);
			setVY(0.0f);
		} else {
			if (guard[guardIndex].isFinished()) {
				// Agafar la seguent
				guardIndex = (guardIndex+1)%guard.size();
				guard[guardIndex].initialize();
			}
			// aplicar ruta
			guard[guardIndex].update();
			setVX(guard[guardIndex].getVX());
			setVY(guard[guardIndex].getVY());
		}
		if (distanceToPlayer < detectionDistance) {
			if (pursue) {
				state = ALERTED;
				data->playSound(GameData::ROAR_INDEX);
			}
			// TODO disparar si te permis
			if (firePermission) {
				bool fired = weapon.fire(getX() + nvx*getWidth(), getY() + nvy*getHeight(), nvx*gunVelocity, nvy*gunVelocity , enemyShots);
				if (fired && weapon.getWeaponType() != FLAMETHROWER) data->playSound(GameData::GUN_SOUND_INDEX);
				/*
				Bullet* b = new Bullet(getX(), getY(), GameData::BULLET_SPRITE_INDEX, 6, 6, true, nvx*gunVelocity, nvy*gunVelocity);
				enemyShots.push_back(*b);
				b->setTicksLeft(ticksMax);
				actualReloadTime = reloadTime;
				*/
			}
		}
		break;
	case ALERTED:
		float fvx = 0.0f;
		float fvy = 0.0f;

		if (distanceToPlayer < minPursueDistance) {
			// dins del rang d'accio
			
			// Si cal aproparse
			if (distanceToPlayer > minDistance) {
				/* scale */
				fvx = nvx*pursueVelocity;
				fvy = nvy*pursueVelocity;
			}
			// TODO disparar si te permis
			if (firePermission) {
				bool fired = weapon.fire(getX() + nvx*getWidth(), getY() + nvy*getHeight(), nvx*gunVelocity, nvy*gunVelocity , enemyShots);
				if (fired && weapon.getWeaponType() != FLAMETHROWER) data->playSound(GameData::GUN_SOUND_INDEX);
			}
		}

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
		std::vector<GameObject*> players;
		players.push_back(&player);
		bool collision = it->update(data, collisionObjects, collisionTiles, players);
		if (collision) it->collision();

		// Remove the bullet if it goes off-screen
		float x = it->getX();
		float y = it->getY();	
		if (y > viewport->getTop() || y < (viewport->getTop() - viewport->getHeight()) || 
			x > (viewport->getLeft() + viewport->getWidth()) || x < viewport->getLeft()) {
			it = enemyShots.erase(it);
		} 
		// Remove the bullet if it has collisioned
		else if (it->isDead() || (collision && it->isAnimationFinished())) {
			it = enemyShots.erase(it);
		}
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


/* Getters */
bool Enemy::isDead()
{
	return life <= 0;
}


/* Setters */
void Enemy::decrementLife(int decrement)
{
	if (life > 0) {
		life -= decrement;
		hasBeenHit = true;
		if (life <= 0) {
			hasBeenKilled = true;
  			setSpriteIndex(GameData::EXPLOSION_SPRITE_INDEX);
			setAction(STATIC_UP);
		}
	}
}

void Enemy::kill()
{
	if (life > 0) {
		life = 0;
		hasBeenHit = true;
		hasBeenKilled = true;
		setSpriteIndex(GameData::EXPLOSION_SPRITE_INDEX);
		setAction(STATIC_UP);
	}
}