
#include "OutZone.h"
#include <string>


OutZone::OutZone(void)
{
}

OutZone::~OutZone(void)
{
}

/* Initialization & Finalization */
bool OutZone::init() 
{
	// Graphics initialization
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	// Camera initialization
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0f, GAME_WIDTH, 0.0f, GAME_HEIGHT, 0.0f, 1.0f);
	glMatrixMode(GL_MODELVIEW);

	// Data loading
	bool b = data.loadTexture(GameData::TILES_TEX_ID, GameData::TILES_TEX_FILENAME, GameData::TEX_EXT);
	if (!b) return false;
	b = scene.loadLevel(1);
	if (!b) return false;
	return true;
}

void OutZone::finalize() {}


/* Input */
void OutZone::handleKeyboard(unsigned char key, int x, int y, bool down) 
{
	keys[key] = down;
}

void OutZone::handleMouse(int button, int state, int x, int y) {}


/* Game phases */
bool OutZone::process() 
{
	return true;
}

void OutZone::render() 
{
	glClear(GL_COLOR_BUFFER_BIT);

	glLoadIdentity();

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
	} while (t2 - t1 < 100/FRAMERATE);

	return true;
}
