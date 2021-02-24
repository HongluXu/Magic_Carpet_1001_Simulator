#include "CreditScene.h"

#include "MenuScene.h"

USING_NS_CC;

cocos2d::Scene * CreditScene::createScene()
{
	auto scene = Scene::create();

	auto layer = CreditScene::create();

	scene->addChild(layer);

	return scene;
}

bool CreditScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto center = Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y);

	this->up_b_value = visibleSize.height / 2 + origin.y;
	this->down_b_value = up_b_value - 500;

	this->credit_layer = CreditLayer::create();
	this->credit_layer->setPosition(origin);
	this->addChild(this->credit_layer, 5);

	//Arrows
	this->up_arr = Sprite::create(UP_ARR_FILE_NAME);
	this->up_arr->setPosition(Vec2(visibleSize.width + origin.x - 100, origin.y + 200));
	this->up_arr->setVisible(true);
	this->addChild(this->up_arr);
	this->up_arr->setVisible(false);

	this->down_arr = Sprite::create(DOWN_ARR_FILE_NAME);
	this->down_arr->setPosition(Vec2(visibleSize.width + origin.x - 100, origin.y + 100));
	this->down_arr->setVisible(true);
	this->addChild(this->down_arr);
	this->down_arr->setVisible(false);

	auto return_x = Label::create("Press 'X' to return.", "fonts/Marker Felt.ttf", 24);
	return_x->setAnchorPoint(Vec2(1.0f, 0.5f));
	return_x->setPosition(Vec2(visibleSize.width + origin.x - 150, origin.y + 50));
	return_x->setColor(Color3B::BLUE);
	this->addChild(return_x);
	
	//Scroll the page.
	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(CreditScene::onKeyPressed, this);
	listener->onKeyReleased = CC_CALLBACK_2(CreditScene::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	this->scheduleUpdate();

	return true;
}

void CreditScene::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event * event)
{
	switch (keyCode)
	{
	case cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW:
	{
		this->credit_layer->stopActionByTag(CREDIT_ROLL_UP_TAG);
		break;
	}
	case cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW:
	{
		this->credit_layer->stopActionByTag(CREDIT_ROLL_DOWN_TAG);
		break;
	}
	}
}

void CreditScene::update(float)
{
	//CCLOG("aaaaa %f", (this->credit_layer->getPosition().y));
	//if ((this->credit_layer->getPosition().y) >= this->up_b_value)
	//{
	//	CCLOG("up_b_value");
	//	this->up_bondary = true;
	//	this->credit_layer->stopActionByTag(CREDIT_ROLL_UP_TAG);
	//	this->up_arr->setVisible(false);
	//}
	//else
	//{
	//	this->up_bondary = false;
	//	this->up_arr->setVisible(true);
	//}
	//if ((this->credit_layer->getPosition().y) <= this->down_b_value)
	//{
	//	CCLOG("down_b_value");
	//	this->down_bondary = true;
	//	this->credit_layer->stopActionByTag(CREDIT_ROLL_DOWN_TAG);
	//	this->down_arr->setVisible(false);
	//}
	//else
	//{
	//	this->down_bondary = false;
	//	this->down_arr->setVisible(true);
	//}

}

void CreditScene::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event * event)
{
	switch (keyCode)
	{
	//case cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW:
	//{
	//	if (this->up_bondary)
	//	{
	//		break;
	//	}
	//	auto move_up = MoveBy::create(0.1f, Vec2(0, 20));
	//	auto repeat_up = RepeatForever::create(move_up);
	//	repeat_up->setTag(CREDIT_ROLL_UP_TAG);
	//	this->credit_layer->runAction(repeat_up);
	//	break;
	//}
	//case cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW:
	//{
	//	if (this->down_bondary)
	//	{
	//		break;
	//	}
	//	auto move_down = MoveBy::create(0.1f, Vec2(0, -20));
	//	auto repeat_down = RepeatForever::create(move_down);
	//	repeat_down->setTag(CREDIT_ROLL_DOWN_TAG);
	//	this->credit_layer->runAction(repeat_down);
	//	break;
	//}
	case cocos2d::EventKeyboard::KeyCode::KEY_X:
	{
		auto menu_scene = MenuScene::createScene();

		auto dir = Director::getInstance();
		dir->replaceScene(menu_scene);

		break;
	}
	}
}

//void MenuScene::mouse_dis_init()
//{
//	this->mouse_display = Label::createWithTTF("X:                    Y:", "fonts/Marker Felt.ttf", 18);
//	this->mouse_display->setAnchorPoint(Vec2(0.0f, 0.0f));
//	this->mouse_display->setPosition(Vec2(10, 100));
//	this->addChild(this->mouse_display);
//	this->x_posi = Label::createWithTTF("0.0", "fonts/Marker Felt.ttf", 18);
//	this->x_posi->setAnchorPoint(Vec2(0.0f, 0.0f));
//	this->x_posi->setPosition(Vec2(30, 100));
//	this->addChild(this->x_posi);
//	this->y_posi = Label::createWithTTF("0.0", "fonts/Marker Felt.ttf", 18);
//	this->y_posi->setAnchorPoint(Vec2(0.0f, 0.0f));
//	this->y_posi->setPosition(Vec2(150, 100));
//	this->addChild(this->y_posi);
//
//	auto _mouseListener = EventListenerMouse::create();
//	_mouseListener->onMouseMove = CC_CALLBACK_1(MenuScene::onMouseMove, this);
//	_eventDispatcher->addEventListenerWithSceneGraphPriority(_mouseListener, this);
//}
//
//void MenuScene::onMouseMove(cocos2d::Event * event)
//{
//	cocos2d::EventMouse* e = (cocos2d::EventMouse*)event;
//	this->x_posi->setString(std::to_string(e->getCursorX()));
//	this->y_posi->setString(std::to_string(e->getCursorY()));
//}