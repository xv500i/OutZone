
#pragma once

#include <gl/glut.h>
#include "BoundingBox.h"
#include "GameData.h"
#include "SpriteAction.h"


class GameObject
{
private:
	const static int STANDARD_SIZE = 32;

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
	const static char PLAYER_TYPE = 'P';

	GameObject(const float x, const float y, const int spriteIndex, const int width, const int height, const bool isWalkable);
	GameObject();
	~GameObject(void);

	/* Updating */
	void update(GameData *data);

	/* Drawing */
	void render(GameData *data) const;

	/* Getters */
	float getX() const;
	float getY() const;
	int getWidth() const;
	int getHeight() const;
	SpriteAction getAction() const;
	virtual float getAngleVelocity() const;
	BoundingBox* getBoundingBox() const;
	bool shouldNotEnterObjects() const;
	char getType() const;
	int getId();

	/* Setters */
	void setX(const float x);
	void setY(const float y);
	void setWidth(int width);
	void setHeight(int height);
	void setAction(SpriteAction action);
	void setPhantom(bool phantom);
	void setType(char type);
	void setSpriteIndex(int spriteIndex);


	bool isIntersecting(const GameObject &go) const;
	void updateBBox(const float x, const float y);
	float distance(GameObject &g);
};