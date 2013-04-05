
#pragma once

#include <gl/glut.h>
#include <vector>
#include <iterator>
#include "InputHandler.h"
#include "Viewport.h"
#include "Level.h"
#include "HUD.h"

using namespace std;


class Scene
{
private:
	const static int NUM_LEVELS = 2;
	
	vector<Level> levels;
	HUD hud;
	int currentLevel;

	bool loadLevel(GameData *data, Viewport *viewport);

public:
	Scene(void);
	~Scene(void);

	/* Loading */
	bool changeToNextLevel(GameData *data, Viewport *viewport);
	bool changeLevel(int newLevel, GameData *data, Viewport *viewport);

	/* Updating */ 
	void resolveInput(InputHandler &input);
	void update(GameData *data, Viewport *viewport);

	/* Drawing */
	void render(GameData *data, Viewport *viewport);

	/* Getters */
	void getLevelSizeInPixels(int level, int &w, int &h);
	void getLevelSize(int level, int *width, int *height);
	void getLevelTileSize(int level, int *width, int *height);
	bool playerHasLost();
	bool playerHasWon();
};

