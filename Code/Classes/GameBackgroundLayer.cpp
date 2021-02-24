#include "GameBackgroundLayer.h"

USING_NS_CC;

bool GameBackgroundLayer::init()
{

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	float center_x = visibleSize.width / 2 + origin.x;
	float center_y = visibleSize.height / 2 + origin.y;
	Vec2 center_point = Vec2(center_x, center_x);
	
	this->background = Sprite::create(BACKGROUND_FILE);
	background->setAnchorPoint(Vec2(0.0f, 0.5f));
	background->setPosition(Vec2(0, center_y));

	this->addChild(background);

	//Loop the background.
	auto place_act = Place::create(Vec2(0, center_y));
	auto move_to_act = MoveTo::create(BACKGROUND_MOVE_DURATION,Vec2(-BACKGROUND_IN_WIDTH, center_y));
	auto sequence_act = Sequence::create(place_act->clone(), move_to_act->clone(), nullptr);
	auto reqeate_act = RepeatForever::create(sequence_act);
	reqeate_act->setTag(BACKGROUND_MOVE_ACT_TAG);

	background->runAction(reqeate_act);

	return true;
}

void GameBackgroundLayer::stop_move()
{
	this->background->stopActionByTag(BACKGROUND_MOVE_ACT_TAG);
}
