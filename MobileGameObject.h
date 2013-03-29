
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

public:
	MobileGameObject();
	MobileGameObject(const float x, const float y, const int idTexture, const int width, const int length, const bool isWalkable, const float vx = 0, const float vy = 0);
	~MobileGameObject(void);
	
	/* Drawing */
	void update(GameData *data, std::vector<GameObject> &collisionableObjects);
	
	/* Getters */
	float getVX() const;
	float getVY() const;
	Direction getDirection() const;
	virtual float getAngleVelocity() const;

	/* Setters */
	void setVX(const float vx);
	void setVY(const float vy);


	void collision(GameObject &g);
};

