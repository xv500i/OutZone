
#pragma once

#include <gl/glut.h>
#include "Level.h"


class Scene
{
private:
	const static int NUM_LEVELS = 1;

	Level levels[NUM_LEVELS];

public:
	Scene(void);
	~Scene(void);

	bool loadLevel(int level);
	void render(int level, GameData *data);

	void getLevelSize(int level, int *width, int *height);
};

