#include "GameMenu.h"
#include "OutZone.h"


GameMenu::GameMenu(void)
{
	currentOption = 0;
	selected = NONE_SELECTED;
	maxTicks = 25;
	currentTicks = maxTicks;
	interactionTicksMax = 18;
	currentInteractionTicks = interactionTicksMax;
}

GameMenu::~GameMenu(void)
{
}

void GameMenu::createGameOver()
{
	opts = std::vector<MenuOption>(2);
	opts[0] = TO_MAIN_MENU;
	opts[1] = QUIT;
	type = 'g';
}

void GameMenu::createMain()
{
	opts = std::vector<MenuOption>(3);
	opts[0] = START;
	opts[1] = INSTRUCTIONS;
	opts[2] = QUIT;
	type = 'm';
}

void GameMenu::createPause()
{
	opts = std::vector<MenuOption>(3);
	opts[0] = RESTART;
	opts[1] = TO_MAIN_MENU;
	opts[2] = QUIT;
	type = 'p';
}

void GameMenu::createInstructions()
{
	opts = std::vector<MenuOption>(1);
	opts[0] = TO_MAIN_MENU;
	type = 'i';
}

void GameMenu::render(GameData *data)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, OutZone::GAME_WIDTH, 0, OutZone::GAME_HEIGHT, -3.0f, 1.0f);
	glMatrixMode(GL_MODELVIEW);
	// TODO: opts.size() quads with textures
	float xi = 240.0f;
	float yi = 500.0f;
	float w = 100;
	float h = 50;
	float margin = 30.f;
	for (unsigned int i = 0; i < opts.size(); i++) {
		paint(-1, xi, yi, w, h);
		yi -= (h + margin);
	}
	if (showCursor) {
		float cx = xi - w;
		float cy = 500.0f - currentOption*(h+margin);
		float cw = 50;
		float ch = 50;
		paint(-1, cx, cy, cw, ch);
	}
	// TODO: one quad if cursor is visible with the cursor texture between the location of the selected option
}

void GameMenu::update()
{
	currentTicks--;
	if (currentTicks == 0) {
		showCursor = !showCursor;
		currentTicks = maxTicks;
	}
	selected = NONE_SELECTED;
	if (currentInteractionTicks > 0) currentInteractionTicks--;
}

void GameMenu::upPressed()
{
	if (currentInteractionTicks > 0) return;
	currentOption--;
	if (currentOption < 0) currentOption = opts.size() - 1;
	currentInteractionTicks = interactionTicksMax;
}

void GameMenu::downPressed()
{
	if (currentInteractionTicks > 0) return;
	currentOption++;
	if (currentOption >= (signed)opts.size()) currentOption = 0;
	currentInteractionTicks = interactionTicksMax;
}

void GameMenu::enterPressed()
{
	if (currentInteractionTicks > 0) return;
	selected = opts[currentOption];
	currentInteractionTicks = interactionTicksMax;
}

MenuOption GameMenu::getSelected()
{
	return selected;
}

void GameMenu::paint(int idTexture, float x, float y, float w, float h)
{
	//float offsetX, offsetY, s,t;
	//int w,h;
	//data->getSpriteFrameInfo(idTexture,pa,&s,&t,&w,&h,&offsetX,&offsetY);
	//glEnable(GL_TEXTURE_2D);
	//glBindTexture(GL_TEXTURE_2D, data->getSpriteID(idTexture));
	glPushMatrix();
	glTranslatef(x, y, 0.0f);
	glBegin(GL_QUADS);
		// Bottom-left
		//glTexCoord2f(s, t+offsetY);
		glVertex3i(- w/2 , - h/2, 1);
		// Top-left
		//glTexCoord2f(s, t);
		glVertex3i(- w/2 , + h/2, 1);
		// Top-right
		//glTexCoord2f(s+offsetX, t);
		glVertex3i(+ w/2 , + h/2, 1);
		// Bottom-right
		//glTexCoord2f(s+offsetX, t+offsetY);
		glVertex3i(+ w/2 , - h/2, 1);	
	glEnd();
	glPopMatrix();
	//glDisable(GL_TEXTURE_2D);
}