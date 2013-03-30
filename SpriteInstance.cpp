#include "SpriteInstance.h"


SpriteInstance::SpriteInstance(Sprite *sprite)
{
	this->sprite = sprite;
	currentAnimationIndex = -1;
	currentAnimationDuration = 0;
	currentAction = (SpriteAction)-1;
	animationHasFinished = false;
}

SpriteInstance::~SpriteInstance(void) {}


/* Getters */
void SpriteInstance::getFrameInfo(SpriteAction action, bool *finished, float *s, float *t, int *width, int *height, float *offsetX, float *offsetY)
{
	// Case: the action has changed
	if (currentAction != action) {
		currentAction = action;
		currentAnimationIndex = 0;
		currentAnimationDuration = 0;
		animationHasFinished = false;
	}
	// Case: continue with the same action
	else {
		if (!animationHasFinished) {
			// Increment the animation duration
			currentAnimationDuration++;

			// If we have reached the end of the frame, change it
			if (currentAnimationDuration == sprite->getFrameDuration(currentAction, currentAnimationIndex)) {
				currentAnimationDuration = 0;
				currentAnimationIndex++;
				// Case: the animation has finished
				if (currentAnimationIndex == sprite->getAnimationNumFrames(currentAction)) {
					if (sprite->isAnimationLoop(currentAction)) currentAnimationIndex = 0;
					else {
						animationHasFinished = true;
						currentAnimationIndex = -1;
					}
				}
			}
		}
	}

	*finished = animationHasFinished;
	if (!animationHasFinished) {
		// Obtain the info of the frame that we have to render
		int sSprite, tSprite;
		sprite->getFrameInfo(currentAction, currentAnimationIndex, &sSprite, &tSprite, width, height);
		int textureWidth, textureHeight;
		sprite->getSizeInPixels(&textureWidth, &textureHeight);

		*s = (float)sSprite/(float)textureWidth;
		*t = (float)tSprite/(float)textureHeight;
		*offsetX = (float)*width/(float)textureWidth;
		*offsetY = (float)*height/(float)textureHeight;
	}
}

bool SpriteInstance::isInitialized()
{
	return sprite != NULL;
}