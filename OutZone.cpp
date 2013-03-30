
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
#include <iostream>


OutZone::OutZone(void) {}

OutZone::~OutZone(void) {}


void ERRCHECK(FMOD_RESULT result)
{
    if (result != FMOD_OK)
    {
        printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
        exit(-1);
    }
}


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
	//if (!data.loadSounds()) return false;				// TODO: descomentar quan hi hagi sons
	if (!scene.loadLevel(1, &data)) return false;		// TODO: load each level when it has to be loaded

	// Menu loading
	gameState = MAIN_MENU;
	mainMenu.createMain();
	instructionsMenu.createInstructions();
	pauseMenu.createPause();
	gameOverMenu.createGameOver();

	// Camera initialization
	viewport.init(0.0f, GAME_HEIGHT, GAME_WIDTH, GAME_HEIGHT);
	int width, height;
	scene.getLevelSizeInPixels(1, width, height);
	viewport.setLimits(0.0f, height, width, 0.0f);	// TODO: fer update de setLimits al carregar un nivell, no al inici
	
	return true;


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
	result = sound1->release();
    ERRCHECK(result);
    result = system->close();
    ERRCHECK(result);
    result = system->release();
    ERRCHECK(result);
	*/
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
	switch(gameState) {
	case PLAYING:
		// Process input
		if (input.keyIsDown(input.getPauseMenuKey())) gameState = PAUSE_MENU;
		else {
			scene.resolveInput(input);
			scene.update(&data, &viewport);
		}
		break;

	case MAIN_MENU:
		if (input.keyIsDown(input.getMoveDownKey())) mainMenu.downPressed();
		else if (input.keyIsDown(input.getMoveUpKey())) mainMenu.upPressed();
		else if (input.keyIsDown(input.getMenuSelectionKey())) mainMenu.enterPressed();

		m = mainMenu.getSelected();
		if (m == START) {
			gameState = PLAYING;
			//scene.changeLevel(1);	// From the main menu, we start the first level
		}
		else if (m == INSTRUCTIONS) gameState = INSTRUCTIONS_MENU;
		else if (m == QUIT) gameState = EXIT;
		mainMenu.update();
		break;

	case INSTRUCTIONS_MENU:
		if (input.keyIsDown(input.getMoveDownKey())) instructionsMenu.downPressed();
		else if (input.keyIsDown(input.getMoveUpKey())) instructionsMenu.upPressed();
		else if (input.keyIsDown(input.getMenuSelectionKey())) instructionsMenu.enterPressed();

		m = instructionsMenu.getSelected();
		if (m == TO_MAIN_MENU) gameState = MAIN_MENU;
		instructionsMenu.update();
		break;

	case PAUSE_MENU:
		if (input.keyIsDown(input.getMoveDownKey())) pauseMenu.downPressed();
		else if (input.keyIsDown(input.getMoveUpKey())) pauseMenu.upPressed();
		else if (input.keyIsDown(input.getMenuSelectionKey())) pauseMenu.enterPressed();

		m = pauseMenu.getSelected();
		if (m == RESTART) gameState = PLAYING;
		else if (m == TO_MAIN_MENU) gameState = MAIN_MENU;
		else if (m == QUIT) gameState = EXIT;
		pauseMenu.update();
		break;

	case GAMEOVER_MENU:
		if (input.keyIsDown(input.getMoveDownKey())) gameOverMenu.downPressed();
		else if (input.keyIsDown(input.getMoveUpKey())) gameOverMenu.upPressed();
		else if (input.keyIsDown(input.getMenuSelectionKey())) gameOverMenu.enterPressed();
	
		m = gameOverMenu.getSelected();
		if (m == TO_MAIN_MENU) gameState = MAIN_MENU;
		else if (m == QUIT) gameState = EXIT;
		gameOverMenu.update();
		break;
	}

	return gameState != EXIT;
}

void OutZone::render() 
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	switch (gameState) {
	case PLAYING:			scene.render(1, &data, &viewport); break;
	case MAIN_MENU:			mainMenu.render(&data); break;
	case PAUSE_MENU:		pauseMenu.render(&data); break;
	case GAMEOVER_MENU:		gameOverMenu.render(&data); break;
	case INSTRUCTIONS_MENU:	instructionsMenu.render(&data); break;
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

	if (!b) exit(0);
	return b;
}