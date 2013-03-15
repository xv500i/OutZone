
#pragma once

#include <gl/glut.h>
#include "Level.h"
#include "Player.h"
#include "InputHandler.h"
#include <vector>
#include <iterator>

using namespace std;


class Scene
{
private:
	const static int NUM_LEVELS = 1;
	Level levels[NUM_LEVELS];
	Player player;
	vector<MobileGameObject> bales;


public:
	Scene(void);
	~Scene(void);

	bool loadLevel(int level);
	void render(int level, GameData *data);

	void update(long msec);
	void getLevelSizeInPixels(int level, int &w, int &h);
	void getLevelSize(int level, int *width, int *height);
	void getLevelTileSize(int level, int *width, int *height);
	void resolveInput(InputHandler &input);
};

