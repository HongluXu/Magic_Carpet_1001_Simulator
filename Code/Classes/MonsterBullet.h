#ifndef __MONSTER_BULLET_H__
#define __MONSTER_BULLET_H__

#include "Bullet.h"

//Resources and vars
#define MONSTER_BULLET_TAG 30
#define MONSTER_BULLET_PHYS_TAG 35
#define MONSTER_BULLET_FILENAME "/resources/monster_bullet.png"
#define MONSTER_BULLET_PHYS_WIDTH 5
#define MONSTER_BULLET_PHYS_HEIGHT 5
#define MONSTER_BULLET_PHYS_CATEGORY 0x00000001
#define MONSTER_BULLET_PHYS_CONTACTTEST 0x00000002

class MonsterBullet:public Bullet
{
public:

	static MonsterBullet* create(const char*);
	static MonsterBullet* create();

	void bullet_init();



private:

};



#endif // !__MONSTER_BULLET_H__
