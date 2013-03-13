
#include "OutZone.h"
#include <string>
#include "Directions.h"


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
	camera.initOrtho(0.0f, GAME_HEIGHT, GAME_WIDTH, GAME_HEIGHT);
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
	input.setKeyState(key, down);
}

void OutZone::handleMouse(int button, int state, int x, int y) {}


/* Game phases */
bool OutZone::process() 
{
	// Camera movement
	if (input.keyIsDown(input.getMoveUpKey())) camera.setOrthoVY(0.3f);
	else if (input.keyIsDown(input.getMoveDownKey())) camera.setOrthoVY(-0.3f);
	else camera.setOrthoVY(0.0f);

	// player control
	// HARDCODED
	float vDes = 0.3f;
	// TODO COLISIONS
	if (input.keyIsDown(input.getMoveUpKey())) {
		player.setVY(vDes);
	} else if (input.keyIsDown(input.getMoveDownKey())) {
		player.setVY(-vDes);
	} else {
		player.setVY(0.0f);
	}
	if (input.keyIsDown(input.getMoveRightKey())) {
		player.setVX(vDes);
	} else if (input.keyIsDown(input.getMoveLeftKey())) {
		player.setVX(-vDes);
	} else {
		player.setVX(0.0f);
	}
	//std::cout << player.getY() << std::endl;

	// Update camera
	camera.updateOrtho(100/FRAMERATE);

	// Update player
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

	player.render();

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
