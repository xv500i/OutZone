
#pragma once

#include <vector>
#include "Layer.h"
#include "Enemy.h"


class EnemiesLayer : public Layer
{
private:
	/***** File structure *****

	***************************/

	/* File constants */
	const static char* FILE_NAME_PREFIX;
	const static char* FILE_NAME_SUFIX;
	const static char* FILE_EXT;

	/* Tile size constants */
	const static int TILE_WIDTH_IN_PIXELS = 32;
	const static int TILE_HEIGHT_IN_PIXELS = 32;

	std::vector<Enemy> enemies;

public:
	EnemiesLayer(void);
	~EnemiesLayer(void);

	/* Loading */
	virtual bool load(int level, GameData *data);

	/* Updating */
	virtual void update(GameData *data, Viewport *viewport, std::vector<GameObject> &collisionObjects, std::vector<bool> &collisionTiles, Player *player);

	/* Rendering */
	virtual void render(GameData *data, Viewport *viewport);

	/* Getters */
	std::vector<Enemy> getEnemies();
};

