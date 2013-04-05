#pragma once

#include "GameData.h"
#include "MenuOption.h"
#include <vector>

class GameMenu
{
public:
	GameMenu(void);
	~GameMenu(void);
	void createGameOver();
	void createCongrats();
	void createLevelCompleted();
	void createMain();
	void createPause();
	void createInstructions();
	void render(GameData *data);
	void update();
	void upPressed();
	void downPressed();
	void enterPressed();
	MenuOption getSelected();
private:
	int currentInteractionTicks;
	int interactionTicksMax;
	int currentTicks;
	bool showCursor;
	int maxTicks;
	std::vector<MenuOption> opts;
	int currentOption;
	MenuOption selected;
	void paint(int idTexture, float x, float y, float w, float h);
	char type;
};

