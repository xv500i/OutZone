
#include "HUD.h"


HUD::HUD(void) {}

HUD::~HUD(void) {}


/* Loading */
bool HUD::load(Viewport *viewport)
{
	int x = viewport->getLeft() + viewport->getWidth() - MARGIN_WEAPON - WEAPON_ELEMENT_SIZE/2;
	int y = viewport->getTop() - MARGIN_WEAPON - WEAPON_ELEMENT_SIZE/2;
	weaponUsed = GameObject(x, y, GameData::SINGLESHOTWEAPON_SPRITE_INDEX, WEAPON_ELEMENT_SIZE, WEAPON_ELEMENT_SIZE, false);
	x = viewport->getLeft() + viewport->getWidth() - MARGIN_WEAPONHUD - WEAPONHUD_ELEMENT_SIZE/2;
	y = viewport->getTop() - MARGIN_WEAPONHUD - WEAPONHUD_ELEMENT_SIZE/2;
	weaponHUD = GameObject(x, y, GameData::WEAPONHUD_SPRITE_INDEX, WEAPONHUD_ELEMENT_SIZE, WEAPONHUD_ELEMENT_SIZE, false);
	currentType = SINGLE_SHOT;

	x = viewport->getLeft() + MARGIN_LIFE + LIFE_ELEMENT_SIZE/2;
	y = viewport->getTop() - MARGIN_LIFE - LIFE_ELEMENT_SIZE/2;
	for (unsigned i = 0; i < MAX_LIFE; i++) {
		playerLife.push_back(GameObject(x + i*LIFE_ELEMENT_SIZE, y, GameData::LIFEHUD_SPRITE_INDEX, LIFE_ELEMENT_SIZE, LIFE_ELEMENT_SIZE, false));
	}
	return true;
}

/* Updating */
void HUD::update(GameData *data, Viewport *viewport, int life, WeaponType weaponType)
{
	// Player Life
	for (unsigned int i = 0; i < playerLife.size(); i++) {
		playerLife[i].update(data);
		
		// Position
		int x = viewport->getLeft() + MARGIN_LIFE + LIFE_ELEMENT_SIZE/2;
		int y = viewport->getTop() - MARGIN_LIFE - LIFE_ELEMENT_SIZE/2;
		playerLife[i].setX(x + i*LIFE_ELEMENT_SIZE);
		playerLife[i].setY(y);

		// Action
		if (life > (int)i) playerLife[i].setAction(STATIC_UP);	// STATIC_UP = Heart full
		else playerLife[i].setAction(STATIC_DOWN);				// STATIC_DOWN = Heart empty
	}

	// Weapon used
	if (currentType != weaponType) {
		currentType = weaponType;
		int spriteIndex;
		switch (currentType) {
		case SINGLE_SHOT: spriteIndex = GameData::SINGLESHOTWEAPON_SPRITE_INDEX;
		case THREE_SHOTS: spriteIndex = GameData::THREESHOTWEAPON_SPRITE_INDEX;
		case FIVE_SHOTS: spriteIndex = GameData::FIVESHOTWEAPON_SPRITE_INDEX;
		case FLAMETHROWER: spriteIndex = GameData::FLAMETHROWER_SPRITE_INDEX;
		default: break;
		}
		weaponUsed = GameObject(0, 0, spriteIndex, WEAPON_ELEMENT_SIZE, WEAPON_ELEMENT_SIZE, false);
	}
	weaponUsed.update(data);
	weaponHUD.update(data);
	weaponUsed.setAction(STATIC_UP);
	weaponHUD.setAction(STATIC_UP);
	int x = viewport->getLeft() + viewport->getWidth() - MARGIN_WEAPON - WEAPON_ELEMENT_SIZE/2;
	int y = viewport->getTop() - MARGIN_WEAPON - WEAPON_ELEMENT_SIZE/2;
	weaponUsed.setX(x);
	weaponUsed.setY(y);
	x = viewport->getLeft() + viewport->getWidth() - MARGIN_WEAPONHUD - WEAPONHUD_ELEMENT_SIZE/2;
	y = viewport->getTop() - MARGIN_WEAPONHUD - WEAPONHUD_ELEMENT_SIZE/2;
	weaponHUD.setX(x);
	weaponHUD.setY(y);
}

/* Rendering */
void HUD::render(GameData *data, Viewport *viewport)
{
	for (unsigned int i = 0; i < playerLife.size(); i++) {
		playerLife[i].render(data);
	}
	weaponUsed.render(data);
	weaponHUD.render(data);
}