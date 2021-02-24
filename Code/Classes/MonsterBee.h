#ifndef __MONSTER_BEE_H__
#define __MONSTER_BEE_H__

#include "Monster.h"

//Resources and vars
#define MONSTER_BEE_FILENAME "/resources/bee1.png"
#define MONSTER_BEE_TAG 51
#define MONSTER_BEE_PHYS_WIDTH 50
#define MONSTER_BEE_PHYS_HEIGHT 50
#define MONSTER_BEE_PHYS_TAG 56
#define MONSTER_BEE_HEALTH 2
#define MONSTER_BEE_ANI_FILENAME "bee1.png"
#define MONSTER_BEE_ANI_FILENAME2 "bee2.png"

class MonsterBee:public Monster
{
public:
	static MonsterBee* create(const char*);	//Self define resources;

	static MonsterBee* create();

	void monster_init();

private:

};




#endif // !__MONSTER_BEE_H__
