
#pragma once
#pragma comment(lib, "fmodex_vc")

#include "fmod.hpp"
#include "fmod_errors.h"


class Sound
{
private:
	FMOD::System *system;
	FMOD::Sound *sound;
	FMOD::Channel *channel;
	float volume;

	void errorCheck(FMOD_RESULT result);

public:
	Sound(void);
	~Sound(void);

	/* Loading */
	bool load(const char *filename, const char *ext, bool loop = false, float volume = 1.0f);

	/* Playing */
	void play();
	void stop();

	/* Getters */
	bool isPlaying();
};

