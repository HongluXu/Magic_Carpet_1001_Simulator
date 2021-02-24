#ifndef __MONSTER_ROCKET_H__
#define __MONSTER_ROCKET_H__

#include "Monster.h"

//Resources and vars
#define MONSTER_ROCKET_FILENAME "/resources/rocket1.png"
#define MONSTER_ROCKET_TAG 52
#define MONSTER_ROCKET_PHYS_WIDTH 70
#define MONSTER_ROCKET_PHYS_HEIGHT 70
#define MONSTER_ROCKET_PHYS_TAG 57
#define MONSTER_ROCKET_HEALTH 4
#define MONSTER_ROCKET_ANI_FILENAME "rocket1.png"
#define MONSTER_ROCKET_ANI_FILENAME2 "rocket2.png"

class MonsterRocket:public Monster
{
public:
	static MonsterRocket* create(const char*);

	static MonsterRocket* create();

	void monster_init();

private:

};




#endif // !__MONSTER_ROCKET_H__
