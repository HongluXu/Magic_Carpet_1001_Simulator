#ifndef __MONSTER_BIRD_H__
#define __MONSTER_BIRD_H__

#include <vector>

#include "Monster.h"
//#include "MonsterBullet.h"

//Resources and vars
#define MONSTER_BIRD_FILENAME "/resources/bird_a1_50_50.png"
#define MONSTER_BIRD_ANI_FILENAME "bird_a1_50_50.png"
#define MONSTER_BIRD_ANI_FILENAME2 "bird_a2_50_50.png"
#define MONSTER_BIRD_ANI_FILENAME3 "bird_a3_50_50.png"
#define MONSTER_BIRD_TAG 50
#define MONSTER_BIRD_PHYS_WIDTH 50
#define MONSTER_BIRD_PHYS_HEIGHT 50
#define MONSTER_BIRD_PHYS_TAG 55
#define MONSTER_BIRD_HEALTH 1

class MonsterBird:public Monster
{
public:

	static MonsterBird* create(const char*);

	static MonsterBird* create();

	void monster_init();

private:

};




#endif // !__MONSTER_BIRD_H__
