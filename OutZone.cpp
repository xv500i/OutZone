
#include "OutZone.h"
#include <string>
#include <time.h>
#include <random>

// FMOD FIXME

#pragma comment(lib,"fmodex_vc")
#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include "fmod.hpp"
#include "fmod_errors.h"


OutZone::OutZone(void) {}

OutZone::~OutZone(void) {}

/*
void ERRCHECK(FMOD_RESULT result)
{
    if (result != FMOD_OK)
    {
        printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
        exit(-1);
    }
}
*/


/* Initialization & Finalization */
bool OutZone::init() 
{
	// Random seed
	srand((unsigned)time(0));

	// Graphics initialization
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glAlphaFunc(GL_GREATER, 0.05f);
	glEnable(GL_ALPHA_TEST);
	glEnable(GL_DEPTH_TEST);	// Z-Buffer

	// Data loading
	if (!data.loadTileSheets()) return false;
	if (!data.loadSprites()) return false;
	if (!scene.loadLevel(1, &data)) return false;

	// Music FIXME
	/*
	FMOD::System     *system;
    FMOD::Sound      *sound1;
    FMOD::Channel    *channel = 0;
    FMOD_RESULT       result;

	result = FMOD::System_Create(&system);
    ERRCHECK(result);

	result = system->init(32, FMOD_INIT_NORMAL, 0);
    ERRCHECK(result);

	result = system->createSound("Jungle_Theme.mp3", FMOD_HARDWARE, 0, &sound1);
    ERRCHECK(result);

	result = system->playSound(FMOD_CHANNEL_FREE, sound1, false, &channel);
    ERRCHECK(result);
	*/

	// FMOD FIXME
	/*
	result = sound3->release();
    ERRCHECK(result);
    result = system->close();
    ERRCHECK(result);
    result = system->release();
    ERRCHECK(result);
	*/

	// Menus init
	gs = MAIN_MENU;
	mainMenu.createMain();
	instructionsMenu.createInstructions();
	pauseMenu.createPause();
	gameOverMenu.createGameOver();

	// Camera initialization
	viewport.init(0.0f, GAME_HEIGHT, GAME_WIDTH, GAME_HEIGHT);
	int width, height;
	scene.getLevelSizeInPixels(1, width, height);	// TODO: marcar els limits de la main screen 
	viewport.setLimits(0.0f, height, width, 0.0f);	// TODO: fer update de setLimits al carregar un nivell

	return true;
}

void OutZone::finalize()
{
	
}


/* Input */
void OutZone::handleKeyboard(unsigned char key, int x, int y, bool down) 
{
	input.setKeyState(key, down);
}

void OutZone::handleMouse(int button, int state, int x, int y) {}	// No mouse


/* Game phases */
bool OutZone::process() 
{
	switch(gs) {
	case PLAYING:
		// Process input
		scene.resolveInput(input);
		// Scene update
		scene.update(&viewport);
		break;
	case MAIN_MENU:
		mainMenu.update();
		if (input.keyIsDown(input.getPrimaryWeaponKey())) {
			gs = PLAYING;
		}
		break;
	}


	// FIXME: return gs != QUIT;

	return true;
}

void OutZone::render() 
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	switch(gs){
	case PLAYING:
		/* Scene drawing */
		scene.render(1, &data, &viewport);
		break;
	case MAIN_MENU:
		mainMenu.render(&data);
	}
	

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