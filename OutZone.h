
#pragma once

#include <gl/glut.h>
#include "InputHandler.h"
#include "Scene.h"
#include "GameData.h"
#include "Camera.h"
#include "Player.h"


class OutZone
{
private:
	InputHandler input;	/* Game Input Handler */
	Scene scene;		/* Game scene */
	GameData data;		/* Game data */
	Camera camera;		/* Game camera */
	Player player;

public:
	const static int GAME_WIDTH = 640;
	const static int GAME_HEIGHT = 480;
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

