
#include "Bullet.h"
#include "Enemy.h"
#include "Player.h"
#include "BossTail.h"


const float Bullet::DEFAULT_BULLET_VELOCITY = 10.0f;

Bullet::Bullet(void) {}

Bullet::Bullet(const float x, const float y, const int spriteIndex, const int width, const int height, const bool isWalkable, const float vx, const float vy, int damage)
	: MobileGameObject(x, y, spriteIndex, width, height, isWalkable, vx, vy), damage(damage)
{
	ticksLeft = -1;
	setPhantom(true);
	collisioned = false;
}

Bullet::~Bullet(void) {}


/* Drawing */
bool Bullet::update(GameData *data, std::vector<GameObject> &collisionObjects, std::vector<bool> &collisionTiles, std::vector<GameObject*> &objectives)
{
	if (collisioned) {
		GameObject::update(data);
		return true;
	}
	if (ticksLeft > 0) ticksLeft--; 
	bool collision = MobileGameObject::update(data, collisionObjects, collisionTiles);

	if (!objectives.empty()) {
		// Matem enemics
		if (objectives[0]->getType() == PLAYER_TYPE) {
			Player *player = (Player*)objectives[0];
			if (isIntersecting(*player)) {
				// Hit player
 				player->decrementLife();
			}
		}
		else {
			for (std::vector<GameObject*>::iterator iobj = objectives.begin(); iobj != objectives.end();) {
				if ((*iobj)->getType() == BOSS_TYPE) {
					BossTail *boss = (BossTail*)*iobj;
					if (isIntersecting(*boss)) {
						// Hit enemy
						boss->decrementLife(damage);
						data->playSound(GameData::CLANK_INDEX);
						collision = true;
					} 
					iobj++;
				} else {
					Enemy *enemy = (Enemy*)*iobj;
					if (isIntersecting(*enemy)) {
						// Hit enemy
						enemy->decrementLife(damage);
					} 
					iobj++;
				}
			}
		}
	}

	return collision;
}


/* Getters */
float Bullet::getAngleVelocity() const
{
	float angle = (atan2(getVY(), getVX()) * 180 / 3.1415926f) - 90.0f;
	return angle;
}

bool Bullet::isDead()
{
	return ticksLeft == 0;
}


/* Setters */
void Bullet::setTicksLeft(int t)
{
	ticksLeft = t;
}

void Bullet::collision()
{
	if (!collisioned) {
		collisioned = true;
		ticksLeft--;
		setSpriteIndex(GameData::BULLETEXPLOSION_SPRITE_INDEX);
	}
}