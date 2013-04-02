
#include "Sound.h"
#include <iostream>
#include <sstream>


Sound::Sound(void) {}

Sound::~Sound(void) {}


void Sound::errorCheck(FMOD_RESULT result)
{
    if (result != FMOD_OK) {
        std::cout << "FMOD error! (" << result << ") " << FMOD_ErrorString(result) << std::endl;
        exit(-1);
    }
}

/* Loading */
bool Sound::load(const char *filename, const char *ext, bool loop, float volume)
{
	std::stringstream ss;
	ss << filename << ext;
	this->volume = volume;

	FMOD_RESULT result;
	channel = NULL;
	result = FMOD::System_Create(&system);
	errorCheck(result);
	result = system->init(32, FMOD_INIT_NORMAL, 0);
	errorCheck(result);
	if (loop) result = system->createSound(ss.str().c_str(), FMOD_HARDWARE | FMOD_LOOP_NORMAL, 0, &sound);
	else result = system->createSound(ss.str().c_str(), FMOD_HARDWARE, 0, &sound);
	errorCheck(result);

	return true;
}

/* Playing */
void Sound::play()
{
	FMOD_RESULT result;
	result = system->playSound(FMOD_CHANNEL_FREE, sound, false, &channel);
	channel->setVolume(volume);
	errorCheck(result);
}

void Sound::stop()
{
	FMOD_RESULT result;
	result = system->playSound(FMOD_CHANNEL_FREE, sound, true, &channel);
	errorCheck(result);
}