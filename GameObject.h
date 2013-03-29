
#pragma once

#include <gl/glut.h>
#include "BoundingBox.h"
#include "GameData.h"
#include "SpriteAction.h"


class GameObject
{
private:
	float x;					/* X axis component of the GameObject position */
	float y;					/* Y axis component of the GameObject position */
	int width;					/* GameObject width */
	int height;					/* GameObject height */
	SpriteAction action;		/* The action performed by the GameObject */
	int spriteIndex;			/* Index of the sprite used by this GameObject */
	int spriteInstanceIndex;	/* Index of the sprite instanciated by this GameObject */


	bool phantom;

	BoundingBox *b;
	
	bool isWalkable;
	static int current_id;
	int id;
	char type;

public:
	GameObject(const float x, const float y, const int spriteIndex, const int width, const int height, const bool isWalkable);
	GameObject();
	~GameObject(void);

	/* Drawing */
	void render(GameData *data) const;
	void update(GameData *data);

	/* Getters */
	float getX() const;
	float getY() const;
	int getWidth() const;
	int getHeight() const;
	SpriteAction getAction() const;
	BoundingBox* getBoundingBox() const;
	char getType()const;
	int getId();

	/* Setters */
	void setX(const float x);
	void setY(const float y);
	void setWidth(int width);
	void setHeight(int height);
	void setAction(SpriteAction action);
	void setPhantom(bool phantom);


	bool isIntersecting(const GameObject &go) const;
	void updateBBox(const float x, const float y);
	void collision(GameObject &g);
	bool shouldNotEnterObjects() const;
	float distance(GameObject &g);
	virtual float getAngleVelocity() const;
};

