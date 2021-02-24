#ifndef __MONSTER_SUPER_H__
#define __MONSTER_SUPER_H__

#include "Monster.h"

//Resources and vars
#define MONSTER_SUPER_FILENAME "/resources/super1.png"
#define MONSTER_SUPER_TAG 53
#define MONSTER_SUPER_PHYS_WIDTH 50
#define MONSTER_SUPER_PHYS_HEIGHT 50
#define MONSTER_SUPER_PHYS_TAG 58
#define MONSTER_SUPER_HEALTH 3
#define MONSTER_SUPER_ANI_FILENAME "super1.png"
#define MONSTER_SUPER_ANI_FILENAME2 "super2.png"


class MonsterSuper :public Monster
{
public:
	static MonsterSuper* create(const char*);

	static MonsterSuper* create();

	void monster_init();

private:

};




#endif // !__MONSTER_ROCKET_H__
