#include "EdgeBoxOut.h"

USING_NS_CC;

EdgeBoxOut * EdgeBoxOut::create()
{
	EdgeBoxOut * ret = new (std::nothrow) EdgeBoxOut();
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

void EdgeBoxOut::edge_box_out_init(Size size,PhysicsMaterial physicsMaterial)
{
	this->edge_out_phys_size = size;
	this->edge_out_phys = PhysicsBody::createEdgeBox(this->edge_out_phys_size, physicsMaterial, EDGE_BOX_OUT_WIDTH);
	this->edge_out_phys->setDynamic(false);
	this->edge_out_phys->setGravityEnable(false);
	this->edge_out_phys->setTag(EDGE_BOX_OUT_PHYS_TAG);
	this->edge_out_phys->setCategoryBitmask(EDGE_BOX_OUT_PHYS_CATEGORY);
	this->edge_out_phys->setContactTestBitmask(EDGE_BOX_OUT_PHYS_CONTACTTEST);

	this->setPhysicsBody(this->edge_out_phys);

}

void EdgeBoxOut::setEdge_out_phys(cocos2d::PhysicsBody* physicsBody)
{
	this->edge_out_phys = physicsBody;
}

cocos2d::PhysicsBody * EdgeBoxOut::getEdge_out_phys()
{
	return this->edge_out_phys;
}

void EdgeBoxOut::setEdge_out_phys_size(cocos2d::Size size)
{
	this->edge_out_phys_size = size;
}

cocos2d::Size EdgeBoxOut::getEdge_out_phys_size()
{
	return this->edge_out_phys_size;
}

void EdgeBoxOut::setEdge_out_phys_tag(int tag)
{
	this->edge_out_phys->setTag(tag);
}

void EdgeBoxOut::setEdge_category(int category)
{
	this->edge_out_phys->setCategoryBitmask(category);
}

void EdgeBoxOut::setEdge_collision(int collision)
{
	this->edge_out_phys->setCollisionBitmask(collision);
}

void EdgeBoxOut::setEdge_contacttest(int contacttest)
{
	this->edge_out_phys->setContactTestBitmask(contacttest);
}
