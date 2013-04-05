
#pragma once

#include "StaticTilesLayer.h"
#include "MobileTilesLayer.h"
#include "ObjectsLayer.h"
#include "EnemiesLayer.h"
#include "Player.h"
#include "Boss.h"
#include "DeathWall.h"


class Level
{
private:
	const static float PLAYER_INITIAL_X;
	const static float PLAYER_INITIAL_Y;
	const static float BOSS_INITIAL_X;
	const static float BOSS_INITIAL_Y;
	const static int BOSS_LEVEL = 2;
	const static int DEATH_WALL_LEVEL = 1;

	int levelNumber;
	StaticTilesLayer staticTilesLayer;
	ObjectsLayer objectsLayer;
	EnemiesLayer enemiesLayer;
	DeathWall deathWall;
	Player player;
	Boss boss;
	bool bossTriggered;

	std::vector<GameObject> Level::getCollisionObjects();

public:
	Level();
	Level(int levelNumber);
	~Level(void);

	/* Loading */
	bool load(GameData *data, Viewport *viewport);

	/* Input */
	void resolveInput(InputHandler *input);

	/* Updating */
	void update(GameData *data, Viewport *viewport);

	/* Rendering */
	void render(GameData *data, Viewport *viewport);

	/* Getters */
	void getSizeInPixels(int *width, int *height);
	void getSizeInTiles(int *width, int *height);
	void getTileSizeInPixels(int *width, int *height);
	int getPlayerLife();
	bool playerHasLost();
	bool playerHasWon();
	WeaponType getPlayerWeaponType();
};