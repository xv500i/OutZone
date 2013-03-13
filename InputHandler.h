
#pragma once

#include <gl/glut.h>


class InputHandler
{
private:
	/* Min and max keys */
	const static unsigned char MIN_KEY = 0;
	const static unsigned char MAX_KEY = 255;

	/* Default keys */
	const static unsigned char DEFAULT_MOVEUP_KEY = 'w';
	const static unsigned char DEFAULT_MOVEDOWN_KEY = 's';
	const static unsigned char DEFAULT_MOVELEFT_KEY = 'a';
	const static unsigned char DEFAULT_MOVERIGHT_KEY = 'd';
	const static unsigned char DEFAULT_PRIMARYWEAPON_KEY = ' ';
	const static unsigned char DEFAULT_SECONDARYWEAPON_KEY = 'm';
	const static unsigned char DEFAULT_PAUSEMENU_KEY = '\n';

	/* Movement keys */
	unsigned char moveUpKey;
	unsigned char moveDownKey;
	unsigned char moveLeftKey;
	unsigned char moveRightKey;

	/* Action keys */
	unsigned char primaryWeaponKey;
	unsigned char secondaryWeaponKey;

	/* Menu keys */
	unsigned char pauseMenuKey;

	bool keys[256];		/* Keyboard keys array */

public:
	InputHandler(void);
	~InputHandler(void);

	/* Reset key defaults */
	void resetDefaults();

	/* Set and retrieve key state */
	void setKeyState(unsigned char key, bool down);
	bool keyIsDown(unsigned char key);

	/* Getters */
	unsigned char getMoveUpKey();
	unsigned char getMoveDownKey();
	unsigned char getMoveLeftKey();
	unsigned char getMoveRightKey();
	unsigned char getPrimaryWeaponKey();
	unsigned char getSecondaryWeaponKey();
	unsigned char getPauseMenuKey();

	/* Setters */
	bool setMoveUpKey(unsigned char newMoveUpKey);
	bool setMoveDownKey(unsigned char newMoveDownKey);
	bool setMoveLeftKey(unsigned char newMoveLeftKey);
	bool setMoveRightKey(unsigned char newMoveRightKey);
	bool setPrimaryWeaponKey(unsigned char newPrimaryWeaponKey);
	bool setSecondaryWeaponKey(unsigned char newSecondaryWeaponKey);
	bool setPauseMenuKey(unsigned char newPauseMenuKey);
};