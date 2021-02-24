#include "TestScene.h"

#include <vector>

#include "MonsterBird.h"
//#include "MonsterBullet.h"
#include "Player.h"

USING_NS_CC;

cocos2d::Scene * TestScene::createScene()
{
	//auto scene = Scene::create();

	auto scene = Scene::createWithPhysics();

	auto layer = TestScene::create();

	scene->addChild(layer);

	return scene;
}

bool TestScene::init()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	Vec2 center_point = Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y);

	//auto monster = MonsterBird::create();
	//monster->monster_init();
	//monster->setPosition(center_point);
	//auto sequence = Sequence::create(
	//	DelayTime::create(1.0f),
	//	CallFuncN::create([monster](Node*)
	//	{
	//		monster->monster_fire1(this)
	//	}),
	//	DelayTime::create(duration2),
	//	CallFuncN::create([this, y_vel](Node*)
	//{
	//	this->setPhys_velocity(Vec2(-300, 0));
	//}), nullptr);
	//this->runAction(sequence);



	//MonsterBird* monster_bird = MonsterBird::create();
	//monster_bird->monster_init();
	//monster_bird->setPosition(center_point);
	//this->addChild(monster_bird);

	//std::vector<MonsterBullet*> monster_bullets = monster_bird->monster_fire();
	//this->addChild(monster_bullets[0]);

	//auto player = Player::create();
	//player->player_init();
	//player->setPosition(Vec2(100, 600));
	//this->addChild(player);

	//auto player_bullet = player->player_fire();
	//this->addChild(player_bullet);


	return true;
}
