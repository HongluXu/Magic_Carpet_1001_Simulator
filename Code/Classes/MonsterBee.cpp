#include "MonsterBee.h"

USING_NS_CC;

MonsterBee * MonsterBee::create(const char * monster_file_name)
{
	MonsterBee* monster_sprite = new MonsterBee();

	if (monster_sprite && monster_sprite->initWithFile(monster_file_name))
	{
		monster_sprite->autorelease();
		return monster_sprite;
	}

	CC_SAFE_DELETE(monster_sprite);
	return nullptr;
}

MonsterBee * MonsterBee::create()
{
	MonsterBee* monster_sprite = new MonsterBee();

	if (monster_sprite && monster_sprite->initWithFile(MONSTER_BEE_FILENAME))
	{
		monster_sprite->autorelease();
		return monster_sprite;
	}

	CC_SAFE_DELETE(monster_sprite);
	return nullptr;
}

void MonsterBee::monster_init()
{
	this->setTag(MONSTER_BEE_TAG);
	this->health = MONSTER_BEE_HEALTH;

	this->setMonster_physize(Size(MONSTER_BEE_PHYS_WIDTH- MONSTER_PHYS_SIZE_CUT, MONSTER_BEE_PHYS_HEIGHT- MONSTER_PHYS_SIZE_CUT));
	this->setMonster_phys(PhysicsBody::createBox(this->getMonster_physize(), PHYSICSBODY_MATERIAL_DEFAULT));
	this->setPhys_dynamic(true);
	this->setPhys_gravity(false);
	this->setPhys_rotation(false);
	this->setMonster_phys_tag(MONSTER_BEE_PHYS_TAG);
	this->setMonster_phys_category(MONSTER_PHYS_CATEGORY);
	this->setMonster_phys_collision(MONSTER_PHYS_COLLISION);
	this->setMonster_phys_contacttest(MONSTER_PHYS_CONTACTTEST);

	this->setPhysicsBody(this->getMonster_phys());

	Vector<SpriteFrame*> bee_animation;
	bee_animation.reserve(2);
	auto instance = SpriteFrameCache::getInstance();
	bee_animation.pushBack(instance->getSpriteFrameByName(MONSTER_BEE_ANI_FILENAME));
	bee_animation.pushBack(instance->getSpriteFrameByName(MONSTER_BEE_ANI_FILENAME2));
	Animation* animation = Animation::createWithSpriteFrames(bee_animation, 0.1f);
	Animate* animate = Animate::create(animation);
	RepeatForever* animate_loop = RepeatForever::create(animate);
	this->runAction(animate_loop);
	animate_loop->setTag(MONSTER_ACT_TAG);
}
