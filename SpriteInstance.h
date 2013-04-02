
#pragma once

#include "Sprite.h"


class SpriteInstance
{
private:
	Sprite *sprite;

	SpriteAction currentAction;		/* Contains the current action */
	int currentAnimationIndex;		/* Contains the index in the animation vector of the current keyFrame */
	int currentAnimationDuration;	/* Contains the time used by the current animation */
	bool animationHasFinished;		/* If an animation finishes, only an action change can provoke another animation */

public:
	SpriteInstance(Sprite *sprite);
	~SpriteInstance(void);

	/* Getters */
	void getFrameInfo(SpriteAction action, bool *finished, float *s, float *t, float *offsetX, float *offsetY, 
										   int *width, int *height, int *tx, int *ty, float *angle);
	bool isInitialized();
};

