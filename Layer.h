
#pragma once

#include "GameData.h"
#include "Viewport.h"


class Layer
{
private:
	unsigned int level;		/* The level to which the layer belongs */

public:
	virtual ~Layer(void) {}

	/* Loading */
	virtual bool load(int level, GameData *data) = 0;

	/* Rendering */
	virtual void render(GameData *data, Viewport *viewport) = 0;

	/* Getters & Setters */
	virtual void setLevel(unsigned int newLevel) {level = newLevel;};
	virtual unsigned int getLevel() {return level;};
};

