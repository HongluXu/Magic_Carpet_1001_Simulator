#include "MonsterBoss.h"

USING_NS_CC;


MonsterBoss * MonsterBoss::create(const char * monster_file_name)
{
	MonsterBoss* monster_sprite = new MonsterBoss();

	if (monster_sprite && monster_sprite->initWithFile(monster_file_name))
	{
		monster_sprite->autorelease();
		return monster_sprite;
	}

	CC_SAFE_DELETE(monster_sprite);
	return nullptr;
}


MonsterBoss * MonsterBoss::create()
{
	MonsterBoss* monster_sprite = new MonsterBoss();

	if (monster_sprite && monster_sprite->initWithFile(MONSTER_BOSS_FILENAME))
	{
		monster_sprite->autorelease();
		return monster_sprite;
	}

	CC_SAFE_DELETE(monster_sprite);
	return nullptr;
}

void MonsterBoss::monster_init()
{
	this->setTag(MONSTER_BOSS_TAG);
	this->health = MONSTER_BOSS_HEALTH;

	this->setMonster_physize(Size(MONSTER_BOSS_PHYS_WIDTH- MONSTER_PHYS_SIZE_CUT, MONSTER_BOSS_PHYS_HEIGHT- MONSTER_PHYS_SIZE_CUT));
	this->setMonster_phys(PhysicsBody::createBox(this->getMonster_physize(), PHYSICSBODY_MATERIAL_DEFAULT));
	this->setPhys_dynamic(true);
	this->setPhys_gravity(false);
	this->setPhys_rotation(false);
	this->setMonster_phys_tag(MONSTER_BOSS_PHYS_TAG);
	this->setMonster_phys_category(MONSTER_PHYS_CATEGORY);
	this->setMonster_phys_collision(MONSTER_PHYS_COLLISION);
	this->setMonster_phys_contacttest(MONSTER_PHYS_CONTACTTEST);

	this->addComponent(this->getMonster_phys());

}
