#include "CreditLayer.h"

USING_NS_CC;

bool CreditLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto center_x = visibleSize.width / 2 + origin.x;

	//Set the credit texts.
	auto label1 = Label::create("Credits", "fonts/Marker Felt.ttf", 32);
	label1->setAnchorPoint(Vec2(0.5f, 0.5f));
	label1->setPosition(Vec2(center_x, visibleSize.height-50));
	this->addChild(label1);

	auto label10 = Label::create("Powered by: 'Cocos2dx'", "fonts/Marker Felt.ttf", 32);
	label10->setAnchorPoint(Vec2(0.5f, 0.5f));
	label10->setPosition(Vec2(center_x, visibleSize.height - 100));
	this->addChild(label10);

	auto label2 = Label::create("Original Design: 'NTDEC'", "fonts/Marker Felt.ttf", 32);
	label2->setAnchorPoint(Vec2(0.5f, 0.5f));
	label2->setPosition(Vec2(center_x, visibleSize.height - 150));
	this->addChild(label2);

	auto label3 = Label::create("Developer: Honglu Xu", "fonts/Marker Felt.ttf", 32);
	label3->setAnchorPoint(Vec2(0.5f, 0.5f));
	label3->setPosition(Vec2(center_x, visibleSize.height - 250));
	this->addChild(label3);

	auto label4 = Label::create("Art: Honglu Xu", "fonts/Marker Felt.ttf", 32);
	label4->setAnchorPoint(Vec2(0.5f, 0.5f));
	label4->setPosition(Vec2(center_x, visibleSize.height - 350));
	this->addChild(label4);

	auto label5 = Label::create("Oringinal Design:'NTDEC'", "fonts/Marker Felt.ttf", 32);
	label5->setAnchorPoint(Vec2(0.5f, 0.5f));
	label5->setPosition(Vec2(center_x, visibleSize.height - 400));
	this->addChild(label5);

	auto label6 = Label::create("Music/Sound: Honglu Xu", "fonts/Marker Felt.ttf", 32);
	label6->setAnchorPoint(Vec2(0.5f, 0.5f));
	label6->setPosition(Vec2(center_x, visibleSize.height - 500));
	this->addChild(label6);

	auto label7 = Label::create("Oringinal Design:'NTDEC'", "fonts/Marker Felt.ttf", 32);
	label7->setAnchorPoint(Vec2(0.5f, 0.5f));
	label7->setPosition(Vec2(center_x, visibleSize.height - 550));
	this->addChild(label7);

	auto label8 = Label::create("Material used: Vocal: 'MIKU_V3_DARK'; 'Tianyi_CHN';", "fonts/Marker Felt.ttf", 32);
	label8->setAnchorPoint(Vec2(0.5f, 0.5f));
	label8->setPosition(Vec2(center_x, visibleSize.height - 600));
	this->addChild(label8);

	auto label9 = Label::create("Kenney Vleugels: 'RPGsounds_Kenney' ", "fonts/Marker Felt.ttf", 32);
	label9->setAnchorPoint(Vec2(0.5f, 0.5f));
	label9->setPosition(Vec2(center_x, visibleSize.height - 650));
	this->addChild(label9);



	return true;
}