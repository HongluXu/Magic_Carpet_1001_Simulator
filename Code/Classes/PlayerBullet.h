#ifndef __PLAYER_BULLET_H__
#define __PLAYER_BULLET_H__

#include "Bullet.h"

//Resources and vars.
#define PLAYER_BULLET_FILENAME "/resources/player_bullet_60_5.png"
#define PLAYER_BULLET_TAG 20
#define PLAYER_BULLET_PHYS_TAG 25
#define PLAYER_BULLET_PHYS_WIDTH 60
#define PLAYER_BULLET_PHYS_HEIGHT 5
#define PLAYER_BULLET_PHYS_CATEGORY 0x00000008
#define PLAYER_BULLET_PHYS_CONTACTTEST 0x55555555


class PlayerBullet:public Bullet
{
public:

	static PlayerBullet* create(const char*);
	static PlayerBullet* create();

	void bullet_init();

private:
	
};





#endif