#ifndef __MONSTER_BOSS_H__
#define __MONSTER_BOSS_H__

#include "Monster.h"
//#include "MonsterBullet.h"

#define MONSTER_BOSS_FILENAME "/resources/boss1.png"
#define MONSTER_BOSS_TAG 60
#define MONSTER_BOSS_PHYS_WIDTH 150
#define MONSTER_BOSS_PHYS_HEIGHT 150
#define MONSTER_BOSS_PHYS_TAG 65
#define MONSTER_BOSS_HEALTH 10

class MonsterBoss :public Monster
{
public:

	static MonsterBoss* create(const char*);

	static MonsterBoss* create();

	void monster_init();

private:


};




#endif // !__MONSTER_BOSS_H__
