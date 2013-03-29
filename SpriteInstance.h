
#pragma once

#include "Sprite.h"


class SpriteInstance
{
private:
	Sprite *sprite;

	SpriteAction currentAction;		/* Contains the current action */
	int currentAnimationIndex;		/* Contains the index in the animation vector of the current keyFrame */
	int currentAnimationDuration;	/* Contains the time used by the current animation */

public:
	SpriteInstance(Sprite *sprite);
	~SpriteInstance(void);

	void getFrameInfo(SpriteAction action, float *s, float *t, int *width, int *height, float *offsetX, float *offsetY);
};

