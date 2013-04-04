
#pragma once

#include <vector>
#include "Viewport.h"
#include "GameObject.h"


class HUD
{
private:
	const static int MARGIN = 16;
	const static int MAX_LIFE = 5;
	const static int LIFE_ELEMENT_SIZE = 32;

	std::vector<GameObject> playerLife;

public:
	HUD(void);
	~HUD(void);

	/* Loading */
	bool load(Viewport *viewport);

	/* Updating */
	void update(GameData *data, Viewport *viewport, int life);

	/* Rendering */
	void render(GameData *data, Viewport *viewport);
};

