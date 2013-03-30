
#include "OutZone.h"
#include <string>
#include <time.h>
#include <random>
#include "gl\glut.h"

// FMOD FIXME

#pragma comment(lib,"fmodex_vc")
#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include "fmod.hpp"
#include "fmod_errors.h"
#include <iostream>


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
	MenuOption m;
	switch(gs) {
	case PLAYING:
		// Process input
		if (input.keyIsDown(27)) {
			gs = PAUSE_MENU;
		} else {
			scene.resolveInput(input);
			// Scene update
			scene.update(&data, &viewport);
		}
		break;
	case MAIN_MENU:
		if (input.keyIsDown(input.getMoveDownKey())) {
			mainMenu.downPressed();
		} else if (input.keyIsDown(input.getMoveUpKey())) {
			mainMenu.upPressed();
		}
		if (input.keyIsDown(input.getPrimaryWeaponKey())) {
			mainMenu.enterPressed();
		}
		m = mainMenu.getSelected();
		if (m == START) gs = PLAYING;
		else if (m == INSTRUCTIONS) gs = INSTRUCTIONS_MENU;
		else if (m == QUIT) gs = EXIT;
		mainMenu.update();
		break;
	case INSTRUCTIONS_MENU:
		if (input.keyIsDown(input.getMoveDownKey())) {
			instructionsMenu.downPressed();
		} else if (input.keyIsDown(input.getMoveUpKey())) {
			instructionsMenu.upPressed();
		}
		if (input.keyIsDown(input.getPrimaryWeaponKey())) {
			instructionsMenu.enterPressed();
		}
		m = instructionsMenu.getSelected();
		if (m == TO_MAIN_MENU) gs = MAIN_MENU;
		instructionsMenu.update();
		break;
	case PAUSE_MENU:
		if (input.keyIsDown(input.getMoveDownKey())) {
			pauseMenu.downPressed();
		} else if (input.keyIsDown(input.getMoveUpKey())) {
			pauseMenu.upPressed();
		}
		if (input.keyIsDown(input.getPrimaryWeaponKey())) {
			pauseMenu.enterPressed();
		}
		m = pauseMenu.getSelected();
		if (m == RESTART) gs = PLAYING;
		else if (m == TO_MAIN_MENU) gs = MAIN_MENU;
		else if (m == QUIT) gs = EXIT;
		pauseMenu.update();
		break;
	case GAMEOVER_MENU:
		if (input.keyIsDown(input.getMoveDownKey())) {
			gameOverMenu.downPressed();
		} else if (input.keyIsDown(input.getMoveUpKey())) {
			gameOverMenu.upPressed();
		}
		if (input.keyIsDown(input.getPrimaryWeaponKey())) {
			gameOverMenu.enterPressed();
		}
		m = gameOverMenu.getSelected();
		if (m == TO_MAIN_MENU) gs = MAIN_MENU;
		else if (m == QUIT) gs = EXIT;
		gameOverMenu.update();
		break;
	}

	return gs != EXIT;
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
		break;
	case PAUSE_MENU:
		pauseMenu.render(&data);
		break;
	case GAMEOVER_MENU:
		gameOverMenu.render(&data);
		break;
	case INSTRUCTIONS_MENU:
		instructionsMenu.render(&data);
		break;
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

	if (!b) {
		exit(0);
	}
	return b;
}