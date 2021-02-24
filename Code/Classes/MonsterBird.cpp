#include "MonsterBird.h"

USING_NS_CC;


MonsterBird * MonsterBird::create(const char * monster_file_name)
{
	MonsterBird* monster_sprite = new MonsterBird();

	if (monster_sprite && monster_sprite->initWithFile(monster_file_name))
	{
		monster_sprite->autorelease();
		return monster_sprite;
	}

	CC_SAFE_DELETE(monster_sprite);
	return nullptr;
}


MonsterBird * MonsterBird::create()
{
	MonsterBird* monster_sprite = new MonsterBird();

	if (monster_sprite && monster_sprite->initWithFile(MONSTER_BIRD_FILENAME))
	{
		monster_sprite->autorelease();
		return monster_sprite;
	}

	CC_SAFE_DELETE(monster_sprite);
	return nullptr;
}

void MonsterBird::monster_init()
{
	this->setTag(MONSTER_BIRD_TAG);
	this->health = MONSTER_BIRD_HEALTH;

	this->setMonster_physize(Size(MONSTER_BIRD_PHYS_WIDTH- MONSTER_PHYS_SIZE_CUT, MONSTER_BIRD_PHYS_HEIGHT- MONSTER_PHYS_SIZE_CUT));
	this->setMonster_phys(PhysicsBody::createBox(this->getMonster_physize(), PHYSICSBODY_MATERIAL_DEFAULT));
	this->setPhys_dynamic(true);
	this->setPhys_gravity(false);
	this->setPhys_rotation(false);
	this->setMonster_phys_tag(MONSTER_BIRD_PHYS_TAG);
	this->setMonster_phys_category(MONSTER_PHYS_CATEGORY);
	this->setMonster_phys_collision(MONSTER_PHYS_COLLISION);
	this->setMonster_phys_contacttest(MONSTER_PHYS_CONTACTTEST);

	this->setPhysicsBody(this->getMonster_phys());

	Vector<SpriteFrame*> bird_animation;
	bird_animation.reserve(3);
	auto instance = SpriteFrameCache::getInstance();
	bird_animation.pushBack(instance->getSpriteFrameByName(MONSTER_BIRD_ANI_FILENAME));
	bird_animation.pushBack(instance->getSpriteFrameByName(MONSTER_BIRD_ANI_FILENAME2));
	bird_animation.pushBack(instance->getSpriteFrameByName(MONSTER_BIRD_ANI_FILENAME3));
	Animation* animation = Animation::createWithSpriteFrames(bird_animation, 0.2f);
	Animate* animate = Animate::create(animation);
	RepeatForever* animate_loop = RepeatForever::create(animate);
	this->runAction(animate_loop);
	animate_loop->setTag(MONSTER_ACT_TAG);

	
}