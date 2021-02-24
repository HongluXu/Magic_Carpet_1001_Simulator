#include "Bullet.h"

void Bullet::setBullet_phys(cocos2d::PhysicsBody * physicsBody)
{
	this->bullet_phys = physicsBody;
}

cocos2d::PhysicsBody * Bullet::getBullet_phys()
{
	return this->bullet_phys;
}

void Bullet::setBullet_physize(cocos2d::Size size)
{
	this->bullet_physize = size;
}

cocos2d::Size Bullet::getBullet_physize()
{
	return this->bullet_physize;
}

void Bullet::setPhys_dynamic(bool flag)
{
	this->bullet_phys->setDynamic(flag);
}

//bool Bullet::getPhys_dynamic()
//{
//	return this->bullet_phys->getDynam;
//}

void Bullet::setPhys_gravity(bool flag)
{
	this->bullet_phys->setGravityEnable(flag);
}

//void Bullet::setBullet_tag(int tag)
//{
//	this->setTag(tag);
//}
//
//int Bullet::getBullet_tag()
//{
//	return this->getTag();
//}

void Bullet::setPhys_tag(int tag)
{
	this->bullet_phys->setTag(tag);
}

int Bullet::getPhys_tag()
{
	return this->bullet_phys->getTag();
}

void Bullet::setPhys_category(int category)
{
	this->bullet_phys->setCategoryBitmask(category);
}

void Bullet::setPhys_collision(int collision)
{
	this->bullet_phys->setCollisionBitmask(collision);
}

void Bullet::setPhys_contacttest(int contacttest)
{
	this->bullet_phys->setContactTestBitmask(contacttest);
}

void Bullet::setPhys_rotation(bool flag)
{
	this->bullet_phys->setRotationEnable(flag);
}

//bool Bullet::getPhys_gravity()
//{
//	return this->bullet_phys->getG;
//}

void Bullet::set_up(cocos2d::Vec2 speed)
{
	this->bullet_phys->setVelocity(speed);
}

bool Bullet::delete_judge()
{
	if (this->deleted == true)
	{
		return false;
	}
	else
	{
		this->deleted = true;
		return true;
	}

	return false;
}