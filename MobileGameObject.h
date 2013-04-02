
#pragma once

#include <vector>
#include "GameObject.h"
#include "Direction.h"


class MobileGameObject : public GameObject
{
private:
	float vx;				/* X axis component of the MobileGameObject velocity */ 
	float vy;				/* Y axis component of the MobileGameObject velocity */
	Direction direction;	/* MobileGameObject direction (8 possible directions) */

	void updateDirectionAndAction();

public:
	MobileGameObject();
	MobileGameObject(const float x, const float y, const int spriteIndex, const int width, const int height, const bool isWalkable, const float vx = 0, const float vy = 0);
	~MobileGameObject(void);
	
	/* Updating */
	bool update(GameData *data, std::vector<GameObject> &collisionObjects, std::vector<bool> &collisionTiles);
	
	/* Getters */
	float getVX() const;
	float getVY() const;
	Direction getDirection() const;
	virtual float getAngleVelocity() const;

	/* Setters */
	void setVX(const float vx);
	void setVY(const float vy);
};