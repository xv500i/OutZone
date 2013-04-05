
#pragma once

#include <vector>
#include "Viewport.h"
#include "GameObject.h"
#include "Weapon.h"


class HUD
{
private:
	const static int MARGIN_LIFE = 0;
	const static int MARGIN_WEAPONHUD = 0;
	const static int MARGIN_WEAPON = 8;
	const static int MAX_LIFE = 5;
	const static int WEAPONHUD_ELEMENT_SIZE = 48;
	const static int WEAPON_ELEMENT_SIZE = 32;
	const static int LIFE_ELEMENT_SIZE = 32;
	const static int HUD_DEPTH = 4;

	std::vector<GameObject> playerLife;
	GameObject weaponUsed;
	GameObject weaponHUD;
	WeaponType currentType;

public:
	HUD(void);
	~HUD(void);

	/* Loading */
	bool load(Viewport *viewport);

	/* Updating */
	void update(GameData *data, Viewport *viewport, int life, WeaponType weaponType);

	/* Rendering */
	void render(GameData *data, Viewport *viewport);
};

