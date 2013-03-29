#include "SpriteInstance.h"


SpriteInstance::SpriteInstance(Sprite *sprite)
{
	this->sprite = sprite;
	currentAnimationIndex = -1;
	currentAnimationDuration = 0;
	currentAction = (SpriteAction)-1;
}

SpriteInstance::~SpriteInstance(void) {}


/* Getters */
void SpriteInstance::getFrameInfo(SpriteAction action, float *s, float *t, int *width, int *height, float *offsetX, float *offsetY)
{
	// Case: continue with the same action
	if (currentAction == action) {

		// Increment the animation duration
		currentAnimationDuration++;

		// If we have reached the end of the frame, change it
		if (currentAnimationDuration == sprite->getFrameDuration(currentAction, currentAnimationIndex)) {
			currentAnimationDuration = 0;
			currentAnimationIndex++;
			// Case: the animation has finished
			if (currentAnimationIndex == sprite->getAnimationNumFrames(currentAction)) {
				if (sprite->isAnimationLoop(currentAction)) currentAnimationIndex = 0;
				else currentAction = (SpriteAction)-1;
			}
		}
	}
	// Case: the action has changed
	else {
		currentAction = action;
		currentAnimationIndex = 0;
		currentAnimationDuration = 0;
	}

	// Obtain the info of the frame that we have to render
	int sSprite, tSprite;
	sprite->getFrameInfo(currentAction,currentAnimationIndex,&sSprite,&tSprite,width,height);
	int textureWidth, textureHeight;
	sprite->getSizeInPixels(&textureWidth, &textureHeight);

	*s = (float)sSprite/(float)textureWidth;
	*t = (float)tSprite/(float)textureHeight;
	*offsetX = (float)*width/(float)textureWidth;
	*offsetY = (float)*height/(float)textureHeight;
}