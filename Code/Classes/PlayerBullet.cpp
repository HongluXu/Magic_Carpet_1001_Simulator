#include "PlayerBullet.h"

USING_NS_CC;

PlayerBullet * PlayerBullet::create(const char * playbullet_file_name)
{
	PlayerBullet* playbullet_sprite = new PlayerBullet();

	if (playbullet_sprite && playbullet_sprite->initWithFile(playbullet_file_name))
	{
		playbullet_sprite->autorelease();
		return playbullet_sprite;
	}

	CC_SAFE_DELETE(playbullet_sprite);
	return nullptr;
}

PlayerBullet * PlayerBullet::create()
{
	PlayerBullet* playbullet_sprite = new PlayerBullet();

	if (playbullet_sprite && playbullet_sprite->initWithFile(PLAYER_BULLET_FILENAME))
	{
		playbullet_sprite->autorelease();
		return playbullet_sprite;
	}

	CC_SAFE_DELETE(playbullet_sprite);
	return nullptr;
}

void PlayerBullet::bullet_init()
{
	this->setTag(PLAYER_BULLET_TAG);

	this->setBullet_physize(Size(PLAYER_BULLET_PHYS_WIDTH, PLAYER_BULLET_PHYS_HEIGHT));
	this->setBullet_phys(PhysicsBody::createBox(this->getBullet_physize(), PHYSICSBODY_MATERIAL_DEFAULT));
	this->setPhys_dynamic(true);
	this->setPhys_gravity(false);
	this->setPhys_rotation(false);
	this->setPhys_tag(PLAYER_BULLET_PHYS_TAG);
	this->setPhys_category(PLAYER_BULLET_PHYS_CATEGORY);
	this->setPhys_collision(BULLET_PHYS_COLLISION);
	this->setPhys_contacttest(PLAYER_BULLET_PHYS_CONTACTTEST);

	this->addComponent(this->getBullet_phys());
}


