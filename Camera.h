
#pragma once

#include <gl/glut.h>


class Camera
{
private:
	/* Orthogonal camera */
	const static float ORTHO_ZNEAR;	// = -1.0f;
	const static float ORTHO_ZFAR;	// = 1.0f;

	float orthoLeft;		/* Orthogonal camera left parameter */
	float orthoTop;			/* Orthogonal camera top parameter */
	float orthoWidth;		/* Orthogonal camera width */
	float orthoHeight;		/* Orthogonal camera height */

	float orthoVX;			/* Orthogonal camera X velocity */
	float orthoVY;			/* Orthogonal camera Y velocity */

	float orthoMaxTop;		/* Orthogonal camera max top */
	float orthoMinBottom;	/* Orthogonal camera min bottom */
	float orthoMinLeft;		/* Orthogonal camera min left */
	float orthoMaxRight;	/* Orthogonal camera max right */ 

public:
	Camera(void);
	~Camera(void);

	/* Orthogonal camera */
	void initOrtho(float left, float top, float width, float height);
	void updateOrtho();
	void loadOrtho();
	void setOrthoVX(float newOrthoVX);
	void setOrthoVY(float newOrthoVY);
	bool setOrthoLimits(float minLeft, float maxTop, float maxRight, float minBottom);
};

