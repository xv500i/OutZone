
#include "GameData.h"


const char* GameData::TEXTURE_EXT = ".png";
const char* GameData::TILESHEET_EXT = ".png";
const char* GameData::SPRITE_EXT = ".png";
const char* GameData::SOUND_EXT = ".mp3";

GameData::GameData(void) 
{
	textures = std::vector<Texture>(NUM_TEXTURES);
	tileSheets = std::vector<TileSheet>(NUM_TILESHEETS);
	sprites = std::vector<Sprite>(NUM_SPRITES);
	sounds = std::vector<Sound>(NUM_SOUNDS);
}

GameData::~GameData(void) {}


/* Textures */
bool GameData::loadTextures()
{
	const char* filenames[NUM_TEXTURES] = {"title", "instructions", "pause", "gameover", "button_quit", "button_start","button_help", "button_restart", "button_mainmenu", "cursor", "lantern", "manual", "congrats", "button_next_level", "level_completed"};
	for (unsigned int i = 0; i < textures.size(); i++) {
		bool b = textures[i].load(filenames[i], TEXTURE_EXT);
		if (!b) return false;
	}
	return true;
}


/* Tile Sheets */
bool GameData::loadTileSheets()
{
	const char* filenames[NUM_TILESHEETS] = {"Level1Tileset", "Level2Tileset", "Level3Tileset"};
	for (unsigned int i = 0; i < tileSheets.size(); i++) {
		bool b = tileSheets[i].load(filenames[i], TILESHEET_EXT);
		if (!b) return false;
	}
	return true;
}

int GameData::getTileSheetID(int tileSheetIndex)
{
	return tileSheets[tileSheetIndex].getID();
}

int GameData::getTextureID(int textureIndex)
{
	return textures[textureIndex].getID();
}

void GameData::getTileSheetSizeInPixels(int tileSheetIndex, int *width, int *height)
{
	tileSheets[tileSheetIndex].getSizeInPixels(width, height);
}

void GameData::getTileSheetTilePosition(int tileSheetIndex, int tileIndex, int *x, int *y)
{
	tileSheets[tileSheetIndex].getTilePosition(tileIndex, x, y);
}

void GameData::getTileSheetTileSizeInPixels(int tileSheetIndex, int *width, int *height)
{
	tileSheets[tileSheetIndex].getTileSizeInPixels(width, height);
}

void GameData::getTileSheetTileOffset(int tileSheetIndex, float *offsetX, float *offsetY)
{
	tileSheets[tileSheetIndex].getTileOffset(offsetX, offsetY);
}


/* Sprites */
bool GameData::loadSprites()
{
	const char* filenames[NUM_SPRITES] = {"Player1", "Player2", "Fire", "Fire2", "Alien1", "Bullet", "LifeHUD", "SingleShotWeapon", "ThreeShotWeapon", "FiveShotWeapon", "Flamethrower", "FirstAidKit", "WeaponHUD", "Alien2", "Alien3", "Spider1", "Spider2", "Explosion", "boss", "tentacle_piece", "tentacle_base", "tentacle_weapon", "Victory", "DeathWall", "BulletExplosion"};
	for (unsigned int i = 0; i < sprites.size(); i++) {
		bool b = sprites[i].load(filenames[i], SPRITE_EXT);
		if (!b) return false;
	}
	return true;
}

int GameData::getSpriteID(int spriteIndex)
{
	return sprites[spriteIndex].getID();
}

void GameData::getSpriteSizeInPixels(int spriteIndex, int *width, int *height)
{
	sprites[spriteIndex].getSizeInPixels(width, height);
}


/* Sprite instances */
int GameData::createSpriteInstance(int spriteIndex)
{
	if (spriteIndex >= 0) {
		SpriteInstance spriteInstance(&sprites[spriteIndex]);
		// Look for empty spaces in the spriteInstances vector
		for (unsigned int i = 0; i < spriteInstances.size(); i++) {
			if (!spriteInstances[i].isInitialized()) {
				spriteInstances[i] = spriteInstance;
				return i;
			}
		}
		// If we haven't found any empty space, push back the new sprite instance 
		spriteInstances.push_back(spriteInstance);
		return spriteInstances.size() - 1;
	}
	else return -1;
}

void GameData::removeSpriteInstance(int spriteInstanceIndex)
{
	if (spriteInstanceIndex == spriteInstances.size() - 1) spriteInstances.pop_back();
	else {
		SpriteInstance spriteInstance(NULL);
		spriteInstances[spriteInstanceIndex] = spriteInstance;
	}
}

void GameData::getSpriteFrameInfo(int spriteInstanceIndex, SpriteAction action, bool *finished, float *s, float *t, float *offsetX, float *offsetY, 
																		        int *width, int *height, int *tx, int *ty, float *angle)
{
	spriteInstances[spriteInstanceIndex].getFrameInfo(action, finished, s, t, offsetX, offsetY, width, height, tx, ty, angle);
}


/* Sounds */
bool GameData::loadSounds()
{
	const char* filenames[NUM_SOUNDS] = {"Jungle_Theme", "Boss_Battle", "Title_Theme", "Game_Over", "gun", "flamer", "Stage_Clear", "Ending_Theme", "roar", "enemy_hit", "player_hit", "scream", "explosion", "clank"};
	const bool loop[NUM_SOUNDS] = {true, true, false, false, false, false, false, false, false, false, false, false, false, false};
	const float volumes[NUM_SOUNDS] = {1.0f, 1.0f, 1.0f, 1.0f, 0.3f, 0.8f, 1.0f, 1.0f, 0.8f, 1.5f, 1.0f, 1.0f, 2.8f, 1.4f};
	for (unsigned int i = 0; i < sounds.size(); i++) {
		bool b = sounds[i].load(filenames[i], SOUND_EXT, loop[i], volumes[i]);
		if (!b) return false;
	}
	return true;
}

void GameData::playSound(int soundIndex)
{
	sounds[soundIndex].play();
}

void GameData::stopSound(int soundIndex)
{
	if (sounds[soundIndex].isPlaying()) sounds[soundIndex].stop();
}

bool GameData::isSoundPlaying(int soundIndex)
{
	return sounds[soundIndex].isPlaying();
}