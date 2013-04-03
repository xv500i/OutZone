
#pragma once

#include <vector>
#include "TileSheet.h"
#include "Sprite.h"
#include "SpriteInstance.h"
#include "Sound.h"


class GameData
{
private:
	/* Textures */
	const static int NUM_TEXTURES = 10;		// TOCHANGE: modificar depenent del numero de textures carregades
	const static char* TEXTURE_EXT;
	
	/* TileSheets */
	const static int NUM_TILESHEETS = 1;	// TOCHANGE: modificar depenent del numero de tile sheets carregats
	const static char* TILESHEET_EXT;

	/* Sprites */
	const static int NUM_SPRITES = 6;		// TOCHANGE: modificar depenent del numero de sprites carregats
	const static char* SPRITE_EXT;

	/* Sounds */
	const static int NUM_SOUNDS = 6;		// TOCHANGE: modificar depenent del numero de sons carregats
	const static char* SOUND_EXT;

	std::vector<Texture> textures;					/* All loaded textures */
	std::vector<TileSheet> tileSheets;				/* All loaded tile sheets */
	std::vector<Sprite> sprites;					/* All loaded sprites */
	std::vector<SpriteInstance> spriteInstances;	/* All sprite instances of the loaded sprites */
	std::vector<Sound> sounds;						/* All loaded sounds */

public:
	/* Texture indexes */		// TOCHANGE: afegir indexs de totes les textures carregades
	const static int TITLE_INDEX = 0;
	const static int INSTRUCTIONS_INDEX = 1;
	const static int PAUSE_INDEX = 2;
	const static int GAMEOVER_INDEX = 3;
	const static int QUIT_INDEX = 4;
	const static int START_INDEX = 5;
	const static int HELP_INDEX = 6;
	const static int RESTART_INDEX = 7;
	const static int RETURN_INDEX = 8;
	const static int CURSOR_INDEX = 9;

	/* TileSheet indexes */		// TOCHANGE: afegir indexs de tots els tile sheets carregats
	const static int LEVEL1_TILES_INDEX = 0;
	const static int LEVEL1_MOBILETILES_INDEX = 1;

	/* Sprite indexes */		// TOCHANGE: afegir indexs de tots els sprites carregats
	const static int PLAYER1_SPRITE_INDEX = 0;
	const static int PLAYER2_SPRITE_INDEX = 1;
	const static int FIRE_SPRITE_INDEX = 2;
	const static int FIRE2_SPRITE_INDEX = 3;
	const static int ALIEN1_SPRITE_INDEX = 4;
	const static int BULLET_SPRITE_INDEX = 5;
	
	/* Sounds indexes */		// TOCHANGE: afegir indexs de tots els sounds carregats
	const static int JUNGLE_THEME_INDEX = 0;
	const static int BOSS_THEME_INDEX = 1;
	const static int INTRO_THEME_INDEX = 2;
	const static int GAME_OVER_INDEX = 3;
	const static int GUN_SOUND_INDEX = 4;
	const static int FLAMETHROWER_SOUND_INDEX = 5;

	GameData(void);
	~GameData(void);

	/* Tile Sheets */
	bool loadTileSheets();
	int getTileSheetID(int tileSheetIndex);
	void getTileSheetSizeInPixels(int tileSheetIndex, int *width, int *height);
	void getTileSheetTilePosition(int tileSheetIndex, int tileIndex, int *x, int *y);
	void getTileSheetTileSizeInPixels(int tileSheetIndex, int *width, int *height);
	void getTileSheetTileOffset(int tileSheetIndex, float *offsetX, float *offsetY);

	/* Sprites */
	bool loadSprites();
	int getSpriteID(int spriteIndex);
	void getSpriteSizeInPixels(int spriteIndex, int *width, int *height);

	/* Sprite instances */
	int createSpriteInstance(int spriteIndex);
	void removeSpriteInstance(int spriteInstanceIndex);
	void getSpriteFrameInfo(int spriteInstanceIndex, SpriteAction action, bool *finished, float *s, float *t, float *offsetX, float *offsetY, 
																		  int *width, int *height, int *tx, int *ty, float *angle);
	
	/* Sounds */
	bool loadSounds();
	bool isPlaying(int soundIndex);
	void playSound(int soundIndex);
	void stopSound(int soundIndex);

	/* Textures */
	bool loadTextures();
	int getTextureID(int textureIndex);
};