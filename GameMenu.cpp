#include "GameMenu.h"
#include "OutZone.h"


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
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, OutZone::GAME_WIDTH, 0, OutZone::GAME_HEIGHT, -3.0f, 1.0f);
	glMatrixMode(GL_MODELVIEW);
	// TODO: opts.size() quads with textures
	float xi = 240.0f;
	float yi = 500.0f;
	for (unsigned int i = 0; i < opts.size(); i++) {
		paint(-1, xi, yi, 100, 50);
		yi -= (100.0f + 10.0f);
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