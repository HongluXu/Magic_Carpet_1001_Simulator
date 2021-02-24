#include "GameOverScene.h"

#include "MenuScene.h"

USING_NS_CC;

Scene * GameOverScene::createScene()
{
	auto scene = Scene::create();

	auto layer = GameOverScene::create();

	scene->addChild(layer);

	return scene;
}

bool GameOverScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	Vec2 center_point = Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y);

	auto game_over_label = Label::createWithSystemFont("GAME OVER", "Arial",50);
	game_over_label->setAnchorPoint(Vec2(0.5f,0.5f));
	game_over_label->setPosition(center_point);
	this->addChild(game_over_label, 5);

	//Start key listener.
	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(GameOverScene::onKeyPressed, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	return true;
}

void GameOverScene::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event * event)
{
	switch (keyCode)
	{
		case cocos2d::EventKeyboard::KeyCode::KEY_Z:
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
