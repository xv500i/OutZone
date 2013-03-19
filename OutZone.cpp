
#include "OutZone.h"
#include <string>
#include "Directions.h"
#include <time.h>
#include <random>


OutZone::OutZone(void)
{
	srand((unsigned)time(0));
}

OutZone::~OutZone(void)
{
}

/* Initialization & Finalization */
bool OutZone::init() 
{
	// Graphics initialization
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glAlphaFunc(GL_GREATER, 0.05f);
	glEnable(GL_ALPHA_TEST);

	// Data loading
	bool b = data.loadTileSheets();
	if (!b) return false;
	b = scene.loadLevel(1, &data);
	if (!b) return false;

	// Camera initialization
	camera.initOrtho(0.0f, GAME_HEIGHT, GAME_WIDTH, GAME_HEIGHT);
	int width, height;
	scene.getLevelSizeInPixels(1, width, height);
	camera.setOrthoLimits(0.0f, height, width, 0.0f);
	camera.loadOrtho();

	return true;
}

void OutZone::finalize() {}


/* Input */
void OutZone::handleKeyboard(unsigned char key, int x, int y, bool down) 
{
	input.setKeyState(key, down);
}

void OutZone::handleMouse(int button, int state, int x, int y) {}


/* Game phases */
bool OutZone::process() 
{
	// Camera movement. TODO: Canviar Hardcoded!
	if (input.keyIsDown(input.getMoveUpKey())) camera.setOrthoVY(5.0f);
	else if (input.keyIsDown(input.getMoveDownKey())) camera.setOrthoVY(-5.0f);
	else camera.setOrthoVY(0.0f);

	// Input
	scene.resolveInput(input);

	// Update camera
	camera.updateOrtho();

	// Update player
	scene.update();

	return true;
}

void OutZone::render() 
{
	glClear(GL_COLOR_BUFFER_BIT);

	glLoadIdentity();

	/* Camera updating */
	camera.loadOrtho();

	/* Scene drawing */
	scene.render(1, &data);

	glutSwapBuffers();
}

bool OutZone::gameLoop() 
{
	int t1, t2;

	t1 = glutGet(GLUT_ELAPSED_TIME);

	bool b = process();
	if (b) render();

	do {
		t2 = glutGet(GLUT_ELAPSED_TIME);
	} while (t2 - t1 < 20);

	return true;
}
