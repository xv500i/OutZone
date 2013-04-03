
#pragma once

#include "StaticTilesLayer.h"
#include "MobileTilesLayer.h"
#include "ObjectsLayer.h"
#include "EnemiesLayer.h"
#include "Player.h"


class Level
{
private:
	const static float PLAYER_INITIAL_X;
	const static float PLAYER_INITIAL_Y;

	int levelNumber;
	StaticTilesLayer staticTilesLayer;
	MobileTilesLayer mobileTilesLayer;
	ObjectsLayer objectsLayer;
	EnemiesLayer enemiesLayer;
	Player player;

	std::vector<GameObject> Level::getCollisionObjects();

public:
	Level();
	Level(int levelNumber);
	~Level(void);

	/* Loading */
	bool load(GameData *data);

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
};