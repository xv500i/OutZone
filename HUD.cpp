
#include "HUD.h"


HUD::HUD(void) {}

HUD::~HUD(void) {}


/* Loading */
bool HUD::load(Viewport *viewport)
{
	int x = viewport->getLeft() + MARGIN;
	int y = viewport->getTop() - MARGIN;

	for (unsigned i = 0; i < MAX_LIFE; i++) {
		playerLife.push_back(GameObject(x + i*LIFE_ELEMENT_SIZE, y, GameData::LIFEHUD_SPRITE_INDEX, LIFE_ELEMENT_SIZE, LIFE_ELEMENT_SIZE, false));
	}
	return true;
}

/* Updating */
void HUD::update(GameData *data, Viewport *viewport, int life)
{
	for (unsigned int i = 0; i < playerLife.size(); i++) {
		playerLife[i].update(data);
		
		// Position
		playerLife[i].setX(viewport->getLeft() + MARGIN + i*LIFE_ELEMENT_SIZE);
		playerLife[i].setY(viewport->getTop() - MARGIN);

		// Action
		if (life > (int)i) playerLife[i].setAction(STATIC_UP);	// STATIC_UP = Heart full
		else playerLife[i].setAction(STATIC_DOWN);				// STATIC_DOWN = Heart empty
	}
}

/* Rendering */
void HUD::render(GameData *data, Viewport *viewport)
{
	for (unsigned int i = 0; i < playerLife.size(); i++) {
		playerLife[i].render(data);
	}
}