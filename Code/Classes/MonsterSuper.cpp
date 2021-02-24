#include "MonsterSuper.h"

USING_NS_CC;

MonsterSuper * MonsterSuper::create(const char * monster_file_name)
{
	MonsterSuper* monster_sprite = new MonsterSuper();

	if (monster_sprite && monster_sprite->initWithFile(monster_file_name))
	{
		monster_sprite->autorelease();
		return monster_sprite;
	}

	CC_SAFE_DELETE(monster_sprite);
	return nullptr;
}

MonsterSuper * MonsterSuper::create()
{
	MonsterSuper* monster_sprite = new MonsterSuper();

	if (monster_sprite && monster_sprite->initWithFile(MONSTER_SUPER_FILENAME))
	{
		monster_sprite->autorelease();
		return monster_sprite;
	}

	CC_SAFE_DELETE(monster_sprite);
	return nullptr;
}

void MonsterSuper::monster_init()
{
	this->setTag(MONSTER_SUPER_TAG);
	this->health = MONSTER_SUPER_HEALTH;

	this->setMonster_physize(Size(MONSTER_SUPER_PHYS_WIDTH- MONSTER_PHYS_SIZE_CUT, MONSTER_SUPER_PHYS_HEIGHT- MONSTER_PHYS_SIZE_CUT));
	this->setMonster_phys(PhysicsBody::createBox(this->getMonster_physize(), PHYSICSBODY_MATERIAL_DEFAULT));
	this->setPhys_dynamic(true);
	this->setPhys_gravity(false);
	this->setPhys_rotation(false);
	this->setMonster_phys_tag(MONSTER_SUPER_PHYS_TAG);
	this->setMonster_phys_category(MONSTER_PHYS_CATEGORY);
	this->setMonster_phys_collision(MONSTER_PHYS_COLLISION);
	this->setMonster_phys_contacttest(MONSTER_PHYS_CONTACTTEST);

	this->setPhysicsBody(this->getMonster_phys());

	Vector<SpriteFrame*> super_animation;
	super_animation.reserve(2);
	auto instance = SpriteFrameCache::getInstance();
	super_animation.pushBack(instance->getSpriteFrameByName(MONSTER_SUPER_ANI_FILENAME));
	super_animation.pushBack(instance->getSpriteFrameByName(MONSTER_SUPER_ANI_FILENAME2));
	Animation* animation = Animation::createWithSpriteFrames(super_animation, 0.1f);
	Animate* animate = Animate::create(animation);
	RepeatForever* animate_loop = RepeatForever::create(animate);
	this->runAction(animate_loop);
	animate_loop->setTag(MONSTER_ACT_TAG);
}
