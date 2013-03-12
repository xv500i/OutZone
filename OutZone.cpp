
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
	camera.initOrtho(0.0f, GAME_WIDTH, 0.0f, GAME_HEIGHT);
	camera.loadOrtho();

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
	if (keys[GLUT_KEY_UP]) camera.updateOrtho(0.0f, 5.0f, &scene);	//TODO: modificar depenent del jugador
	else if (keys[GLUT_KEY_DOWN]) camera.updateOrtho(0.0f, -5.0f, &scene);	//TODO: modificar depenent del jugador

	// player control
	if (keys['w']) {
		std::cout << "alho" << std::endl;
	}

	// update player
	player.update(100/FRAMERATE);

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
	} while (t2 - t1 < 100/FRAMERATE);

	return true;
}
