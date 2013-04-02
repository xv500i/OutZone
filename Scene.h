
#pragma once

#include <gl/glut.h>
#include "StaticTilesLayer.h"
#include "MobileTilesLayer.h"
#include "ObjectsLayer.h"
#include "Player.h"
#include "InputHandler.h"
#include <vector>
#include <iterator>
#include "Enemy.h"
#include "Bullet.h"
#include "Viewport.h"
#include "Boss.h"
#include "Level.h"

using namespace std;


class Scene
{
private:
	const static int NUM_LEVELS = 1;
	vector<Level> levels;

	vector<Enemy> enemies;
	int currentLevel;
	Boss boss;

	bool loadLevel(GameData *data);

public:
	Scene(void);
	~Scene(void);

	/* Loading */
	bool changeLevel(int newLevel, GameData *data, Viewport *viewport);

	/* Updating */ 
	void resolveInput(InputHandler &input, GameData *data);
	void update(GameData *data, Viewport *viewport);

	/* Drawing */
	void render(GameData *data, Viewport *viewport);

	/* Getters */
	void getLevelSizeInPixels(int level, int &w, int &h);
	void getLevelSize(int level, int *width, int *height);
	void getLevelTileSize(int level, int *width, int *height);
};

