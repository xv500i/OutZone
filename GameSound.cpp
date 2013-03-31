
#include "GameSound.h"
#include <iostream>
#include <sstream>


GameSound::GameSound(void) {}

GameSound::~GameSound(void) {}


void GameSound::errorCheck(FMOD_RESULT result)
{
    if (result != FMOD_OK) {
        std::cout << "FMOD error! (" << result << ") " << FMOD_ErrorString(result) << std::endl;
        exit(-1);
    }
}

/* Loading */
bool GameSound::load(const char *filename, const char *ext)
{
	std::stringstream ss;
	ss << filename << ext;

	FMOD_RESULT result;
	channel = NULL;
	result = FMOD::System_Create(&system);
	errorCheck(result);
	result = system->init(32, FMOD_INIT_NORMAL, 0);
	errorCheck(result);
	result = system->createSound(ss.str().c_str(), FMOD_HARDWARE, 0, &sound);
	errorCheck(result);

	return true;
}

/* Playing */
void GameSound::play()
{
	FMOD_RESULT result;
	result = system->playSound(FMOD_CHANNEL_FREE, sound, false, &channel);
	errorCheck(result);
}

void GameSound::stop()
{
	FMOD_RESULT result;
	result = system->playSound(FMOD_CHANNEL_FREE, sound, true, &channel);
	errorCheck(result);
}