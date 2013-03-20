#pragma once
#include "gameobject.h"
#include "Directions.h"
#include <vector>

class MobileGameObject :
	public GameObject
{
public:
	MobileGameObject();
	MobileGameObject(const float x, const float y, const int idTexture, const int width, const int length, const bool isWalkable, const float vx = 0, const float vy = 0);
	~MobileGameObject(void);
	float getVX() const;
	float getVY() const;
	void setVX(const float v);
	void setVY(const float v);
	void update(std::vector<GameObject> &collisionableObjects);
	Directions getDirection() const;
	void collision(GameObject &g);
	void render() const;
	float getAngleVelocity() const;

private:
	float vx;
	float vy;
	Directions dir;
};

