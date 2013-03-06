
#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "GameData.h"


class Level
{
private:
	const static char* FILE_NAME;
	const static char* FILE_EXT;
	const static char EMPTY_SPACE = '0';
	const static int TILE_SIZE = 32;

	int levelWidth;
	int levelHeight;
	std::vector<int> map;

	void renderTile(int tileID, int posX, int posY, GameData *data);

public:
	Level(void);
	~Level(void);

	/* Loading */
	bool load(int level);

	/* Rendering */
	void render(GameData *data);
};

