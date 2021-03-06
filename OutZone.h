
#pragma once

#include <gl/glut.h>
#include "InputHandler.h"
#include "GameData.h"
#include "Viewport.h"
#include "Scene.h"
#include "GameState.h"
#include "GameMenu.h"


class OutZone
{
private:
	InputHandler input;		/* Game input handler */
	GameData data;			/* Game data */
	Viewport viewport;		/* Game viewport */
	Scene scene;			/* Game scene */
	GameState gameState;	/* Game state */

	/* Game menus */
	GameMenu mainMenu;
	GameMenu instructionsMenu;
	GameMenu pauseMenu;
	GameMenu gameOverMenu;
	GameMenu congratsMenu;
	GameMenu nextLevelMenu;

public:
	const static int GAME_WIDTH = 480;
	const static int GAME_HEIGHT = 720;
	const static int FRAMERATE = 50;

	OutZone(void);
	~OutZone(void);

	/* Initialization & Finalization */
	bool init();
	void finalize();

	/* Input */
	void handleKeyboard(unsigned char key, int x, int y, bool down);
	void handleMouse(int button, int state, int x, int y);

	/* Game phases */
	bool process();
	void render();
	bool gameLoop();
};

