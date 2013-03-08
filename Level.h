
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

	int levelWidth;
	int levelHeight;
	std::vector<int> map;

	void renderTile(int tileID, int posX, int posY, GameData *data);

public:
	const static int TILE_SIZE = 32;

	Level(void);
	~Level(void);

	void getSize(int *width, int *height);

	/* Loading */
	bool load(int level);

	/* Rendering */
	void render(GameData *data);
};

