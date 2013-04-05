
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
	const static int NUM_TEXTURES = 15;		// TOCHANGE: modificar depenent del numero de textures carregades
	const static char* TEXTURE_EXT;
	
	/* TileSheets */
	const static int NUM_TILESHEETS = 3;
	const static char* TILESHEET_EXT;

	/* Sprites */
	const static int NUM_SPRITES = 25;		// TOCHANGE: modificar depenent del numero de sprites carregats
	const static char* SPRITE_EXT;

	/* Sounds */
	const static int NUM_SOUNDS = 14;		// TOCHANGE: modificar depenent del numero de sons carregats
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
	const static int LANTERN_INDEX = 10;
	const static int MANUAL_INDEX = 11;
	const static int CONGRATS_INDEX = 12;
	const static int NEXT_LEVEL_INDEX = 13;
	const static int LEVEL_COMPLETED_INDEX = 14;
	

	/* TileSheet indexes */		// TOCHANGE: afegir indexs de tots els tile sheets carregats
	const static int LEVEL1_TILES_INDEX = 0;
	const static int LEVEL2_TILES_INDEX = 1;
	const static int LEVEL3_TILES_INDEX = 2;

	/* Sprite indexes */		// TOCHANGE: afegir indexs de tots els sprites carregats
	const static int PLAYER1_SPRITE_INDEX = 0;
	const static int PLAYER2_SPRITE_INDEX = 1;
	const static int FIRE_SPRITE_INDEX = 2;
	const static int FIRE2_SPRITE_INDEX = 3;
	const static int ALIEN1_SPRITE_INDEX = 4;
	const static int BULLET_SPRITE_INDEX = 5;
	const static int LIFEHUD_SPRITE_INDEX = 6;
	const static int SINGLESHOTWEAPON_SPRITE_INDEX = 7;
	const static int THREESHOTWEAPON_SPRITE_INDEX = 8;
	const static int FIVESHOTWEAPON_SPRITE_INDEX = 9;
	const static int FLAMETHROWER_SPRITE_INDEX = 10;
	const static int FIRSTAIDKIT_SPRITE_INDEX = 11;
	const static int WEAPONHUD_SPRITE_INDEX = 12;
	const static int ALIEN2_SPRITE_INDEX = 13;
	const static int ALIEN3_SPRITE_INDEX = 14;
	const static int SPIDER1_SPRITE_INDEX = 15;
	const static int SPIDER2_SPRITE_INDEX = 16;
	const static int EXPLOSION_SPRITE_INDEX = 17;
	const static int BOSS_TEX_INDEX = 18;
	const static int TENTACLE_TEX_INDEX = 19;
	const static int TENTACLE_BASE_TEX_INDEX = 20;
	const static int TENTACLE_GUN_TEX_INDEX = 21;
	const static int VICTORY_SPRITE_INDEX = 22;
	const static int DEATHWALL_SPRITE_INDEX = 23;
	const static int BULLETEXPLOSION_SPRITE_INDEX = 24;
	
	/* Sounds indexes */		// TOCHANGE: afegir indexs de tots els sounds carregats
	const static int JUNGLE_THEME_INDEX = 0;
	const static int BOSS_THEME_INDEX = 1;
	const static int INTRO_THEME_INDEX = 2;
	const static int GAME_OVER_INDEX = 3;
	const static int GUN_SOUND_INDEX = 4;
	const static int FLAMETHROWER_SOUND_INDEX = 5;
	const static int STAGE_CLEAR_INDEX = 6;
	const static int ENDING_THEME_INDEX = 7;
	const static int ROAR_INDEX = 8;
	const static int ENEMY_OUCH_INDEX = 9;
	const static int PLAYER_OUCH_INDEX = 10;
	const static int PLAYER_SCREAM_INDEX = 11;
	const static int EXPLOSION_INDEX = 12;
	const static int CLANK_INDEX = 13;

	GameData(void);
	~GameData(void);

	/* Textures */
	bool loadTextures();
	int getTextureID(int textureIndex);

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
	void playSound(int soundIndex);
	void stopSound(int soundIndex);
	bool isSoundPlaying(int soundIndex);
};