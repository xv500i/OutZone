
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

	Player player;
	vector<Bullet> playerShots;
	vector<Bullet> enemyShots;
	vector<GameObject> obstacles;
	vector<Enemy> enemies;
	int currentLevel;
	Boss boss;

public:
	Scene(void);
	~Scene(void);

	bool loadLevel(int level, GameData *data);
	void render(int level, GameData *data, Viewport *viewport);

	void update(GameData *data, Viewport *viewport);

	void resolveInput(InputHandler &input);

	/* Getters */
	void getLevelSizeInPixels(int level, int &w, int &h);
	void getLevelSize(int level, int *width, int *height);
	void getLevelTileSize(int level, int *width, int *height);
	void getCollisioningGameObjects(vector<GameObject> &v);
};

