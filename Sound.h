
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

	void errorCheck(FMOD_RESULT result);

public:
	Sound(void);
	~Sound(void);

	/* Loading */
	bool load(const char *filename, const char *ext);

	/* Playing */
	void play();
	void stop();
};

