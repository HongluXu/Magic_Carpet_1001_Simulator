#include "VictoryScene.h"

#include "MenuScene.h"

#include <string>

USING_NS_CC;

Scene * VictoryScene::createScene(int score)
{
	auto scene = Scene::create();

	auto layer = VictoryScene::create();

	layer->set_score(score);

	scene->addChild(layer);

	return scene;
}

bool VictoryScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	Vec2 center_point = Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y);

	//Create V scene elements.
	auto game_over_label = Label::createWithSystemFont("Congratulation! You Win!", "Arial", 50);
	game_over_label->setAnchorPoint(Vec2(0.5f, 0.5f));
	game_over_label->setPosition(center_point);
	this->addChild(game_over_label, 5);

	this->score_label = Label::createWithSystemFont(std::to_string(this->score), "Arial", 50);
	score_label->setAnchorPoint(Vec2(0.5f, 0.5f));
	score_label->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y - 200));
	this->addChild(score_label, 5);

	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(VictoryScene::onKeyPressed, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	this->scheduleUpdate();

	return true;
}

void VictoryScene::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event * event)
{
	switch (keyCode)
	{
		case cocos2d::EventKeyboard::KeyCode::KEY_X:
		{

			//Next scene;
			auto game_scene = MenuScene::createScene();

			auto dir = Director::getInstance();
			dir->replaceScene(game_scene);

			break;
		}
		default:
			break;
	}



}

void VictoryScene::set_score(int score)
{
	this->score = score;
	this->score_label->setString(std::to_string(this->score+1000));
}
