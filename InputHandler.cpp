
#include "InputHandler.h"


InputHandler::InputHandler(void)
{
	resetDefaults();
}

InputHandler::~InputHandler(void) {}


/* Reset key defaults */
void InputHandler::resetDefaults()
{
	// Movement keys
	moveUpKey = DEFAULT_MOVEUP_KEY;
	moveDownKey = DEFAULT_MOVEDOWN_KEY; 
	moveLeftKey = DEFAULT_MOVELEFT_KEY;
	moveRightKey = DEFAULT_MOVERIGHT_KEY; 

	// Action keys
	primaryWeaponKey = DEFAULT_PRIMARYWEAPON_KEY;
	secondaryWeaponKey = DEFAULT_SECONDARYWEAPON_KEY;

	// Menu keys
	pauseMenuKey = DEFAULT_PAUSEMENU_KEY;
}

/* Set and retrieve key state */
void InputHandler::setKeyState(unsigned char key, bool down) 
{
	keys[key] = down;
}

bool InputHandler::keyIsDown(unsigned char key)
{
	return keys[key];
}

/* Getters */
unsigned char InputHandler::getMoveUpKey()
{
	return moveUpKey;
}

unsigned char InputHandler::getMoveDownKey()
{
	return moveDownKey;
}

unsigned char InputHandler::getMoveLeftKey()
{
	return moveLeftKey;
}

unsigned char InputHandler::getMoveRightKey()
{
	return moveRightKey;
}

unsigned char InputHandler::getPrimaryWeaponKey()
{
	return primaryWeaponKey;
}

unsigned char InputHandler::getSecondaryWeaponKey()
{
	return secondaryWeaponKey;
}

unsigned char InputHandler::getPauseMenuKey()
{
	return pauseMenuKey;
}

/* Setters */
bool InputHandler::setMoveUpKey(unsigned char newMoveUpKey) 
{
	if (newMoveUpKey >= MIN_KEY && newMoveUpKey <= MAX_KEY) {
		this->moveUpKey = newMoveUpKey;
		return true;
	}
	return false;
}

bool InputHandler::setMoveDownKey(unsigned char newMoveDownKey) 
{
	if (newMoveDownKey >= MIN_KEY && newMoveDownKey <= MAX_KEY) {
		this->moveDownKey = newMoveDownKey;
		return true;
	}
	return false;
}

bool InputHandler::setMoveLeftKey(unsigned char newMoveLeftKey) 
{
	if (newMoveLeftKey >= MIN_KEY && newMoveLeftKey <= MAX_KEY) {
		this->moveLeftKey = newMoveLeftKey;
		return true;
	}
	return false;
}

bool InputHandler::setMoveRightKey(unsigned char newMoveRightKey) 
{
	if (newMoveRightKey >= MIN_KEY && newMoveRightKey <= MAX_KEY) {
		this->moveRightKey = newMoveRightKey;
		return true;
	}
	return false;
}

bool InputHandler::setPrimaryWeaponKey(unsigned char newPrimaryWeaponKey) 
{
	if (newPrimaryWeaponKey >= MIN_KEY && newPrimaryWeaponKey <= MAX_KEY) {
		this->primaryWeaponKey = newPrimaryWeaponKey;
		return true;
	}
	return false;
}

bool InputHandler::setSecondaryWeaponKey(unsigned char newSecondaryWeaponKey) 
{
	if (newSecondaryWeaponKey >= MIN_KEY && newSecondaryWeaponKey <= MAX_KEY) {
		this->secondaryWeaponKey = newSecondaryWeaponKey;
		return true;
	}
	return false;
}

bool InputHandler::setPauseMenuKey(unsigned char newPauseMenuKey) 
{
	if (newPauseMenuKey >= MIN_KEY && newPauseMenuKey <= MAX_KEY) {
		this->pauseMenuKey = newPauseMenuKey;
		return true;
	}
	return false;
}
