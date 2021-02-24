#include "MenuScene.h"

#include "GameScene.h"
#include "CreditScene.h"

//#include "SimpleAudioEngine.h"
#include "AudioEngine.h"

USING_NS_CC;

cocos2d::Scene * MenuScene::createScene()
{
	auto scene = Scene::create();

	auto layer = MenuScene::create();

	scene->addChild(layer);

	return scene;
}

bool MenuScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//Load resources
	experimental::AudioEngine::preload(BG_MUSIC_FILE_NAME);
	experimental::AudioEngine::preload(ARROW_SE_FILE_NAME);
	experimental::AudioEngine::preload(PLAYER_SHOOT_SE);
	experimental::AudioEngine::preload(MONSTER_HIT_SE);
	experimental::AudioEngine::preload(STAGE1_BGM_FILE_NAME);

	Vec2 center_point = Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y);

	//Menu elements.
	auto title = Sprite::create(TITLE_FILE_NAME);
	title->setAnchorPoint(Vec2(0.5f,0.5f));
	title->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height + origin.y - 148));
	this->addChild(title);

	auto man_pic = Sprite::create(MAN_FILE_NAME);
	man_pic->setAnchorPoint(Vec2(0.5f, 0.5f));
	man_pic->setPosition(Vec2(visibleSize.width / 2 + origin.x - 150, visibleSize.height / 2 + origin.y - 150));
	this->addChild(man_pic);

	auto simulator_label = Label::createWithTTF("SIMULATOR", "fonts/Marker Felt.ttf", 54);
	simulator_label->setColor(Color3B(153,217,234));
	simulator_label->setPosition(Vec2(visibleSize.width / 2 + origin.x + 350, visibleSize.height / 2 + origin.y + 120));
	this->addChild(simulator_label);

	auto start_label = Label::createWithTTF("Start", "fonts/Marker Felt.ttf", 54);
	start_label->setAnchorPoint(Vec2(0.0f, 0.5f));
	start_label->setPosition(START_L_POSITION);
	this->addChild(start_label);

	auto credit_label = Label::createWithTTF("Credits", "fonts/Marker Felt.ttf", 54);
	credit_label->setAnchorPoint(Vec2(0.0f, 0.5f));
	credit_label->setPosition(CREDIT_L_POSITION);
	this->addChild(credit_label);

	this->arrow_sprite = Sprite::create(ARROW_FILE_NAME);
	this->arrow_sprite->setPosition(Vec2(ARROW_X_POSITION, 300));
	this->addChild(this->arrow_sprite);
	this->menu_select = 1;

	menu_bgm_id = experimental::AudioEngine::play2d(BG_MUSIC_FILE_NAME,true);

	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(MenuScene::onKeyPressed, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	return true;
}

void MenuScene::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event * event)
{
	switch (keyCode)
	{
		//Move arrow.
		case cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		case cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW:
		{
			experimental::AudioEngine::play2d(ARROW_SE_FILE_NAME,false,0.3f);
			if (this->menu_select == 1)
			{
				this->arrow_sprite->setPosition(Vec2(ARROW_X_POSITION, 200));
				this->menu_select = 2;
			}
			else if (this->menu_select == 2)
			{
				this->arrow_sprite->setPosition(Vec2(ARROW_X_POSITION, 300));
				this->menu_select = 1;
			}
			break;
		}
		case cocos2d::EventKeyboard::KeyCode::KEY_Z:
		{
			experimental::AudioEngine::play2d(ARROW_SE_FILE_NAME, false, 0.3f);
			experimental::AudioEngine::stop(menu_bgm_id);
			//Next scene;
			if (this->menu_select == 1)
			{
				auto game_scene = GameScene::createScene();

				auto dir = Director::getInstance();
				dir->replaceScene(game_scene);

				break;
			}
			else if (this->menu_select == 2)
			{
				auto credit_scene = CreditScene::createScene();

				auto dir = Director::getInstance();
				dir->replaceScene(credit_scene);

				break;
			}

		}
		default:
			break;
	}
}

void MenuScene::mouse_dis_init()
{
	this->mouse_display = Label::createWithTTF("X:                    Y:", "fonts/Marker Felt.ttf", 18);
	this->mouse_display->setAnchorPoint(Vec2(0.0f, 0.0f));
	this->mouse_display->setPosition(Vec2(10, 100));
	this->addChild(this->mouse_display);
	this->x_posi = Label::createWithTTF("0.0", "fonts/Marker Felt.ttf", 18);
	this->x_posi->setAnchorPoint(Vec2(0.0f, 0.0f));
	this->x_posi->setPosition(Vec2(30, 100));
	this->addChild(this->x_posi);
	this->y_posi = Label::createWithTTF("0.0", "fonts/Marker Felt.ttf", 18);
	this->y_posi->setAnchorPoint(Vec2(0.0f, 0.0f));
	this->y_posi->setPosition(Vec2(150, 100));
	this->addChild(this->y_posi);

	auto _mouseListener = EventListenerMouse::create();
	_mouseListener->onMouseMove = CC_CALLBACK_1(MenuScene::onMouseMove, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(_mouseListener, this);
}

void MenuScene::onMouseMove(cocos2d::Event * event)
{
	cocos2d::EventMouse* e = (cocos2d::EventMouse*)event;
	this->x_posi->setString(std::to_string(e->getCursorX()));
	this->y_posi->setString(std::to_string(e->getCursorY()));
}