#include "GameMenu.h"


GameMenu::GameMenu(void)
{
	currentOption = 0;
	selected = NONE_SELECTED;
	maxTicks = 100;
	currentTicks = maxTicks;
}

GameMenu::~GameMenu(void)
{
}

void GameMenu::createGameOver()
{
	opts = std::vector<MenuOption>(2);
	opts[0] = TO_MAIN_MENU;
	opts[1] = QUIT;
}

void GameMenu::createMain()
{
	opts = std::vector<MenuOption>(3);
	opts[0] = START;
	opts[1] = INSTRUCTIONS;
	opts[2] = QUIT;
}

void GameMenu::createPause()
{
	opts = std::vector<MenuOption>(4);
	opts[0] = RESTART;
	opts[1] = TO_MAIN_MENU;
	opts[2] = INSTRUCTIONS;
	opts[3] = QUIT;
}

void GameMenu::createInstructions()
{
	opts = std::vector<MenuOption>(1);
	opts[0] = TO_MAIN_MENU;
}

void GameMenu::render(GameData *data)
{
	// TODO: opts.size() quads with textures
	// TODO: one quad if cursor is visible with the cursor texture between the location of the selected option
}

void GameMenu::update()
{
	currentTicks--;
	if (currentTicks == 0) {
		showCursor = !showCursor;
		currentTicks = maxTicks;
	}
}

void GameMenu::upPressed()
{
	currentOption++;
	if (currentOption >= (signed)opts.size()) currentOption = 0;
}

void GameMenu::downPressed()
{
	currentOption--;
	if (currentOption < 0) currentOption = opts.size() - 1;
}

void GameMenu::enterPressed()
{
	selected = opts[currentOption];
}

MenuOption GameMenu::getSelected()
{
	return selected;
}