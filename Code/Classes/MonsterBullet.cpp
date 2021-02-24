#include "MonsterBullet.h"

USING_NS_CC;

MonsterBullet* MonsterBullet::create(const char * monsbullet_file_name)
{
	MonsterBullet* monsbullet_sprite = new MonsterBullet();

	if (monsbullet_sprite && monsbullet_sprite->initWithFile(monsbullet_file_name))
	{
		monsbullet_sprite->autorelease();
		return monsbullet_sprite;
	}

	CC_SAFE_DELETE(monsbullet_sprite);
	return nullptr;
}

MonsterBullet* MonsterBullet::create()
{
	MonsterBullet* monsbullet_sprite = new MonsterBullet();

	if (monsbullet_sprite && monsbullet_sprite->initWithFile(MONSTER_BULLET_FILENAME))
	{
		monsbullet_sprite->autorelease();
		return monsbullet_sprite;
	}

	CC_SAFE_DELETE(monsbullet_sprite);
	return nullptr;
}

void MonsterBullet::bullet_init()
{
	this->setTag(MONSTER_BULLET_TAG);

	this->setBullet_physize(Size(MONSTER_BULLET_PHYS_WIDTH, MONSTER_BULLET_PHYS_HEIGHT));
	this->setBullet_phys(PhysicsBody::createBox(this->getBullet_physize(), PHYSICSBODY_MATERIAL_DEFAULT));
	this->setPhys_dynamic(true);
	this->setPhys_gravity(false);
	this->setPhys_rotation(false);
	this->setPhys_tag(MONSTER_BULLET_PHYS_TAG);
	this->setPhys_category(MONSTER_BULLET_PHYS_CATEGORY);
	this->setPhys_collision(BULLET_PHYS_COLLISION);
	this->setPhys_contacttest(MONSTER_BULLET_PHYS_CONTACTTEST);

	this->addComponent(this->getBullet_phys());

}