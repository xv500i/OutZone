
#include <stdlib.h>
#include <gl/glut.h>
#include "OutZone.h"

//Delete console
#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")


// The Game Instance
OutZone game;


void appRender() {
	game.render();
}

void appKeyboard(unsigned char key, int x, int y) {
	game.handleKeyboard(key, x, y, true);
}

void appKeyboardUp(unsigned char key, int x, int y) {
	game.handleKeyboard(key, x, y, false);
}

void appSpecialKeys(int key, int x, int y) {
	game.handleKeyboard(key, x, y, true);
}

void appSpecialKeysUp(int key, int x, int y) {
	game.handleKeyboard(key, x, y, false);
}

void appMouse(int button, int state, int x, int y) {
	game.handleMouse(button, state, x, y);
}

void appIdle() {
	if(!game.gameLoop()) exit(0);
}

// Main function
void main(int argc, char *argv[])
{
	int res_x, res_y;
	int pos_x, pos_y;

	// GLUT initialization
	glutInit(&argc, argv);

	// RGBA with double buffer
	glutInitDisplayMode(GLUT_RGBA | GLUT_ALPHA | GLUT_DOUBLE);

	// Create centered window
	res_x = glutGet(GLUT_SCREEN_WIDTH);
	res_y = glutGet(GLUT_SCREEN_HEIGHT);
	pos_x = (res_x>>1) - (OutZone::GAME_WIDTH>>1);
	pos_y = (res_y>>1) - (OutZone::GAME_HEIGHT>>1);
	
	glutInitWindowPosition(pos_x, pos_y);
	glutInitWindowSize(OutZone::GAME_WIDTH, OutZone::GAME_HEIGHT);
	glutCreateWindow("OutZone");

	// Full Screen
	/*glutGameModeString("800x600:32");
	glutEnterGameMode();*/

	// Make the default cursor disappear
	//glutSetCursor(GLUT_CURSOR_NONE);

	// Register callback functions
	glutDisplayFunc(appRender);			
	glutKeyboardFunc(appKeyboard);		
	glutKeyboardUpFunc(appKeyboardUp);	
	glutSpecialFunc(appSpecialKeys);	
	glutSpecialUpFunc(appSpecialKeysUp);
	glutMouseFunc(appMouse);
	glutIdleFunc(appIdle);

	// Game initializations
	game.init();

	// GLUT main loop
	glutMainLoop();	
}
