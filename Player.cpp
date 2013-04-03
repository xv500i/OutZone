
#include "Player.h"

const float Player::DEFAULT_PLAYER_VELOCITY = 2.0f;

Player::Player(void) {}

Player::Player(const float x, const float y, const int spriteIndex, const int width, const int height, const bool isWalkable, const float vx, const float vy) 
	: MobileGameObject(x, y, spriteIndex, width, height, isWalkable, vx, vy)
{
	mainWeapon = Weapon(FLAMETHROWER);
	setDirection(UP);
	setAction(STATIC_UP);
	setType('p');
	shooting = false;
	invul = false;
	ticksMaxInvul = 150;
	ticksInvul = 0;
	//FIXME:
	lanternActivated = true;
}

Player::~Player(void) {}


/* Input */
void Player::resolveInput(InputHandler *input)
{
	// Velocity change
	bool up = input->keyIsDown(input->getMoveUpKey());
	bool down = input->keyIsDown(input->getMoveDownKey());
	bool left = input->keyIsDown(input->getMoveLeftKey());
	bool right = input->keyIsDown(input->getMoveRightKey());

	Direction dir;
	if (up) {
		if (right) dir = UP_RIGHT;	
		else if (left) dir = UP_LEFT;
		else dir = UP;
	} 
	else if (down) {
		if (right) dir = DOWN_RIGHT;
		else if (left) dir = DOWN_LEFT;
		else dir = DOWN;
	}
	else if (right) dir = RIGHT;
	else if (left) dir = LEFT;
	
	float vx = 0.0f, vy = 0.0f;
	float catet = DEFAULT_PLAYER_VELOCITY;
	float hipotenusa = sqrt(catet*catet*2);
	if (up || down || left || right) {
		switch (dir) {
		case UP:		vy = hipotenusa; break;
		case DOWN:		vy = -hipotenusa; break;
		case LEFT:		vx = -hipotenusa; break;
		case RIGHT:		vx = hipotenusa; break;
		case UP_RIGHT:	vx = catet; vy = catet; break;
		case DOWN_RIGHT:vx = catet; vy = -catet; break;
		case UP_LEFT:	vx = -catet; vy = catet; break;
		case DOWN_LEFT:	vx = -catet; vy = -catet; break;
		}
	}
	setVX(vx);
	setVY(vy);

	// Shooting
	if (input->keyIsDown(input->getPrimaryWeaponKey())) {
		shotPrimaryWeapon();
	}
}

void Player::shotPrimaryWeapon() 
{
	// test setInvul();
	// Arma del jugador respecte el seu punt mig
	float vecx = 0;
	float vecy = getHeight();
	if (getDirection() == RIGHT) vecx -=6.0f;
	else if (getDirection() == LEFT) vecx += 6.0f;
	float angle = getAngleVelocity();
	float fconv = 3.1415f / 180.0f;
	
	float s = sinf(angle*fconv);
    float c = cosf(angle*fconv);
    
    float nx = c*vecx - s*vecy;
    float ny = s*vecx + c*vecy;
	float fx = getX() + nx;
	float fy = getY() + ny;

	if (mainWeapon.fire(fx, fy, getDirection(), playerShots)) shooting = true;
}


/* Updating */
void Player::update(GameData *data, Viewport *viewport, std::vector<GameObject> &collisionObjects, std::vector<bool> &collisionTiles, std::vector<Enemy> &enemies)
{
	MobileGameObject::update(data, collisionObjects, collisionTiles);
	mainWeapon.update();
	if (invul) {
		if (ticksInvul > 0) ticksInvul--;
		invul = (ticksInvul > 0);
	}
	// Update action if shooting
	if (shooting) {
		if (mainWeapon.getWeaponType() != FLAMETHROWER) {
			// Action
			Direction direction = getDirection();
			switch (direction) {
			case UP:			setAction(SHOT_UP); break;
			case DOWN:			setAction(SHOT_DOWN); break;
			case LEFT:			setAction(SHOT_LEFT); break;
			case RIGHT:			setAction(SHOT_RIGHT); break;
			case UP_LEFT:		setAction(SHOT_UP_LEFT); break;
			case DOWN_LEFT:		setAction(SHOT_DOWN_LEFT); break;
			case DOWN_RIGHT:	setAction(SHOT_DOWN_RIGHT); break;
			case UP_RIGHT:		setAction(SHOT_UP_RIGHT); break;
			default: break;
			}
			// Sound
			data->playSound(GameData::GUN_SOUND_INDEX);
		}
		else {
			if (!data->isSoundPlaying(GameData::FLAMETHROWER_SOUND_INDEX)) data->playSound(GameData::FLAMETHROWER_SOUND_INDEX);
		}

		shooting = false;
	}

	// Screen collision testing. TODO: la colisio s'ha de fer amb el nivell (en aquest cas, es indiferent, amb el player funciona)
	int minX = viewport->getLeft();
	int maxX = viewport->getLeft() + viewport->getWidth();
	int minY = viewport->getTop() - viewport->getHeight();
	int maxY = viewport->getTop();
	if (getX() + getWidth()/2 > maxX) {
		float inc = maxX - getWidth()/2 - getX();
		updateBBox(inc, 0.0f);
		setX(maxX - getWidth()/2);
	}
	else if (getX() - getWidth()/2 < minX) {
		float inc = minX + getWidth()/2 - getX();
		updateBBox(inc, 0.0f);
		setX(minX + getWidth()/2);
	}
	if (getY() + getHeight()/2 > maxY) {
		float inc = maxY - getHeight()/2 - getY();
		updateBBox(0.0f, inc);
		setY(maxY - getHeight()/2);
	}
	else if (getY() - getHeight()/2 < minY) {
		float inc = minY + getHeight()/2 - getY();
		updateBBox(0.0f, inc);
		setY(minY + getHeight()/2);
	}

	// PlayerShots update
	for (std::vector<Bullet>::iterator it = playerShots.begin(); it != playerShots.end();) {
		std::vector<GameObject> objectEnemies;
		objectEnemies.assign(enemies.begin(), enemies.end());
		bool collision = it->update(data, collisionObjects, collisionTiles, objectEnemies);

		// Remove the bullet if it goes off-screen
		float x = it->getX();
		float y = it->getY();	
		if (y > viewport->getTop() || y < (viewport->getTop() - viewport->getHeight()) || 
			x > (viewport->getLeft() + viewport->getWidth()) || x < viewport->getLeft()) {
			it = playerShots.erase(it);
		} 
		// Remove the bullet if it has collisioned
		else if (collision || it->isDead()) it = playerShots.erase(it);
		else it++;
	}
}


/* Drawing */
void Player::render(GameData *data)
{
	if (!(invul && (ticksInvul % 8) > 3)) MobileGameObject::render(data);
	if (lanternActivated) renderLantern(data->getTextureID(GameData::LANTERN_INDEX));
	for (int i = playerShots.size() - 1; i >= 0; i--) {
		playerShots[i].render(data);
	}
}

bool Player::isInvul() const
{
	return invul;
}

void Player::setInvul()
{
	invul = true;
	ticksInvul = ticksMaxInvul;
}

void Player::renderLantern(int idTexture)
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, idTexture);
	glPushMatrix();
	glTranslatef(getX(), getY(), 0.0f);
	glRotatef(getAngleVelocity(), 0.0f, 0.0f, 1.0f);
	glBegin(GL_QUADS);
		// Bottom-left
		glTexCoord2f(0, 1);
		glVertex3i(- 4000/2 , - 4000/2, 1.5);
		// Top-left
		glTexCoord2f(0, 0);
		glVertex3i(- 4000/2 , + 4000/2, 1.5);
		// Top-right
		glTexCoord2f(1, 0);
		glVertex3i(+ 4000/2 , + 4000/2, 1.5);
		// Bottom-right
		glTexCoord2f(1, 1);
		glVertex3i(+ 4000/2 , - 4000/2, 1.5);	
	glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}