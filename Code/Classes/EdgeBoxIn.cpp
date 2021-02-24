#include "EdgeBoxIn.h"

USING_NS_CC;

EdgeBoxIn * EdgeBoxIn::create()
{
	EdgeBoxIn * ret = new (std::nothrow) EdgeBoxIn();
	if (ret && ret->init())
	{
		ret->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(ret);
	}
	return ret;
}

void EdgeBoxIn::edge_box_in_init(Size size, PhysicsMaterial physicsMaterial)
{
	this->edge_in_phys_size = size;
	this->edge_in_phys = PhysicsBody::createEdgeBox(this->edge_in_phys_size, physicsMaterial, EDGE_BOX_IN_WIDTH);
	this->edge_in_phys->setDynamic(false);
	this->edge_in_phys->setGravityEnable(false);
	this->edge_in_phys->setTag(EDGE_BOX_IN_PHYS_TAG);
	this->edge_in_phys->setCategoryBitmask(EDGE_BOX_IN_PHYS_CATEGORY);
	this->edge_in_phys->setContactTestBitmask(EDGE_BOX_IN_PHYS_CONTACTTEST);

	this->setPhysicsBody(this->edge_in_phys);

}

void EdgeBoxIn::setEdge_in_phys(cocos2d::PhysicsBody* physicsBody)
{
	this->edge_in_phys = physicsBody;
}

cocos2d::PhysicsBody * EdgeBoxIn::getEdge_in_phys()
{
	return this->edge_in_phys;
}

void EdgeBoxIn::setEdge_in_phys_size(cocos2d::Size size)
{
	this->edge_in_phys_size = size;
}

cocos2d::Size EdgeBoxIn::getEdge_in_phys_size()
{
	return this->edge_in_phys_size;
}

void EdgeBoxIn::setEdge_in_phys_tag(int tag)
{
	this->edge_in_phys->setTag(tag);
}

void EdgeBoxIn::setEdge_category(int category)
{
	this->edge_in_phys->setCategoryBitmask(category);
}

void EdgeBoxIn::setEdge_collision(int collision)
{
	this->edge_in_phys->setCollisionBitmask(collision);
}

void EdgeBoxIn::setEdge_contacttest(int contacttest)
{
	this->edge_in_phys->setContactTestBitmask(contacttest);
}
