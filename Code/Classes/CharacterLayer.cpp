#include "CharacterLayer.h"

#include "MonsterBird.h"
#include "MonsterBee.h"
#include "MonsterRocket.h"
#include "MonsterSuper.h"
#include "EdgeBoxOut.h"
#include "EdgeBoxIn.h"
#include "GameOverScene.h"
#include "MonsterBoss.h"

//#include "SimpleAudioEngine.h"
#include "AudioEngine.h"

USING_NS_CC;

bool CharacterLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	//Get resources.
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(BIRD_PLIST);
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(BEE_PLIST);
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(ROCKET_PLIST);
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(SUPER_PLIST);
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(PLAYER_PLIST);
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(PLAYER_D_PLIST);
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(CLOUD_PLIST);

	Vec2 center_point = Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y);
	this->right_ref_x = visibleSize.width + MONSTER_MAX_SIZE;
	this->top_ref_y = visibleSize.height + MONSTER_MAX_SIZE;

	//Outer box for out of bound detection.
	auto edge_box_out = EdgeBoxOut::create();
	edge_box_out->edge_box_out_init(Size(visibleSize.width + 500, visibleSize.height + 500),PHYSICSBODY_MATERIAL_DEFAULT);
	edge_box_out->setPosition(center_point);
	this->addChild(edge_box_out);

	//Iner box for moveable detection.
	auto edge_box_in = EdgeBoxIn::create();
	edge_box_in->edge_box_in_init(Size(visibleSize.width - 100, visibleSize.height - 100), PhysicsMaterial(0.0f, 0.0f, 0.0f));
	edge_box_in->setPosition(center_point);
	this->addChild(edge_box_in);

	//Player;
	player = Player::create();
	player->player_init(visibleSize);
	this->addChild(player);

	//Keyboard listener;
	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(CharacterLayer::onKeyPressed, this);
	listener->onKeyReleased = CC_CALLBACK_2(CharacterLayer::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, player);

	//Contact listener;
	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(CharacterLayer::myContactBegin, this);
	contactListener->onContactSeparate = CC_CALLBACK_1(CharacterLayer::onContactSeparate, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);

	//Start state machine.
	this->next_delay = CCDelayTime::create(2.0f);
	this->callback = CallFunc::create(this, callfunc_selector(CharacterLayer::monster_refresh));
	this->runAction(Sequence::create(this->next_delay, this->callback, nullptr));

	return true;
}

void CharacterLayer::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event * event)
{
	Vec2 vel;
	switch (keyCode)
	{
		//Player move.
		case cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW:
			this->player->move_up();
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW:
			this->player->move_down();
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW:
			this->player->move_left();
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
			this->player->move_right();
			break;
		//player shoot;
		case cocos2d::EventKeyboard::KeyCode::KEY_Z:
			if (this->player->getState() == Player::PlayerStateEnum::normal || this->player->getState() == Player::PlayerStateEnum::immune)
			{
				if (!player_bullet_flag)
				{
					experimental::AudioEngine::play2d(PLAYER_SHOOT_SE);
				
					player_bullet = player->player_fire();
					this->addChild(player_bullet);
					this->player_bullet_flag = true;
				}
			}
			break;
		//Debug;
		case cocos2d::EventKeyboard::KeyCode::KEY_E:
			vel = this->player->getPhysicsBody()->getVelocity();
			break;
		default:
			break;
	}
	

}

void CharacterLayer::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event * event)
{
	if (Player::PlayerStateEnum::normal == this->player->getState() || Player::PlayerStateEnum::immune == this->player->getState())
	{
		switch (keyCode)
		{
			case cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW:
				this->player->stop_up();
				break;
			case cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW:
				this->player->stop_down();
				break;
			case cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW:
				this->player->stop_left();
				break;
			case cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
				this->player->stop_right();
				break;
			default:
				break;
		}
	}
}

bool CharacterLayer::myContactBegin(cocos2d::PhysicsContact & contact)
{
	auto phybody_a = contact.getShapeA()->getBody();
	auto phybody_b = contact.getShapeB()->getBody();
	auto phys_a_tag = phybody_a->getTag();
	auto phys_b_tag = phybody_b->getTag();

	//Out of bound.
	if (phys_a_tag == EDGE_BOX_OUT_PHYS_TAG)
	{
		if (phys_b_tag == PLAYER_BULLET_PHYS_TAG)
		{
			this->player_bullet_flag = false;
		}
		if (phybody_b->getNode() != nullptr)
		{
			phybody_b->getNode()->removeFromParentAndCleanup(true);
		}
	}
	else if (phys_b_tag == EDGE_BOX_OUT_PHYS_TAG)
	{
		if (phys_a_tag == PLAYER_BULLET_PHYS_TAG)
		{
			this->player_bullet_flag = false;
		}
		if (phybody_a->getNode() != nullptr)
		{
			phybody_a->getNode()->removeFromParentAndCleanup(true);
		}
	}
	//Enemy hit.
	else if (phys_a_tag != PLAYER_PHYBODY_TAG && phys_b_tag != PLAYER_PHYBODY_TAG)
	{
		experimental::AudioEngine::play2d(MONSTER_HIT_SE);

		if (phys_a_tag == PLAYER_BULLET_PHYS_TAG)
		{
			this->player_bullet_flag = false;
			PlayerBullet* player_bullet = (PlayerBullet*)(phybody_a->getNode());
			if (player_bullet != nullptr)
			{
				player_bullet->removeFromParentAndCleanup(false);
			}
			Monster* monster_node = (Monster*)(phybody_b->getNode());
			if (monster_node->hited())
			{
				this->score_up = true;
				if (monster_node->getTag() == MONSTER_BOSS_TAG)
				{
					experimental::AudioEngine::stopAll();
					this->win_flag = true;
				}
			}
		}
		else if (phys_b_tag == PLAYER_BULLET_PHYS_TAG)
		{
			this->player_bullet_flag = false;
			PlayerBullet* player_bullet = (PlayerBullet*)(phybody_b->getNode());
			if (player_bullet != nullptr)
			{
				player_bullet->removeFromParentAndCleanup(false);
			}
			Monster* monster_node = (Monster*)(phybody_a->getNode());
			if (monster_node->hited())
			{
				this->score_up = true;
				if (monster_node->getTag() == MONSTER_BOSS_TAG)
				{
					experimental::AudioEngine::stopAll();
					this->win_flag = true;
				}
			}
		}
	}
	//Player hit.
	else if (phys_a_tag == PLAYER_PHYBODY_TAG && phys_b_tag != EDGE_BOX_IN_PHYS_TAG)
	{
		if (phybody_b->getTag() == MONSTER_BULLET_PHYS_TAG)
		{
			if (phybody_b->getNode() != nullptr)
			{
				phybody_b->getNode()->removeFromParentAndCleanup(true);
			}
		}
		else
		{
			Monster* monster_node = (Monster*)(phybody_b->getNode());
			if (monster_node->hited())
			{
				this->score_up = true;
				if (monster_node->getTag() == MONSTER_BOSS_TAG)
				{
					experimental::AudioEngine::stopAll();
					this->win_flag = true;
				}
			}
		}
		Player* player = (Player*)(phybody_a->getNode());
		if (player->hited())
		{
			experimental::AudioEngine::stopAll();
			auto game_over_scene = GameOverScene::createScene();
			auto dir = Director::getInstance();
			dir->replaceScene(game_over_scene);
		}
	}
	else if (phys_b_tag == PLAYER_PHYBODY_TAG && phys_a_tag != EDGE_BOX_IN_PHYS_TAG)
	{
		if (phybody_a->getTag() == MONSTER_BULLET_PHYS_TAG)
		{
			if (phybody_a->getNode() != nullptr)
			{
				phybody_a->getNode()->removeFromParentAndCleanup(true);
			}
		}
		else
		{
			Monster* monster_node = (Monster*)(phybody_a->getNode());
			if (monster_node->hited())
			{
				this->score_up = true;
				if (monster_node->getTag() == MONSTER_BOSS_TAG)
				{
					experimental::AudioEngine::stopAll();
					this->win_flag = true;
				}
			}
		}
		Player* player = (Player*)(phybody_b->getNode());
		if (player->hited())
		{
			experimental::AudioEngine::stopAll();
			auto game_over_scene = GameOverScene::createScene();
			auto dir = Director::getInstance();
			dir->replaceScene(game_over_scene);
		}
	}

	return true;

}

bool CharacterLayer::onContactSeparate(cocos2d::PhysicsContact & contact)
{
	auto phybody_a = contact.getShapeA()->getBody();
	auto phybody_b = contact.getShapeB()->getBody();
	auto phys_a_tag = phybody_a->getTag();
	auto phys_b_tag = phybody_b->getTag();

	//Movable area detection.
	if (phys_a_tag == PLAYER_PHYBODY_TAG && phys_b_tag == EDGE_BOX_IN_PHYS_TAG)
	{
		auto vel = phybody_a->getVelocity();
		if ((50 - fabs(vel.x)) > 0 && (vel.x != 0))
		{
			phybody_a->setVelocity(Vec2(0, vel.y));
		}
		if ((50 - fabs(vel.y)) > 0 && (vel.y != 0))
		{
			phybody_a->setVelocity(Vec2(vel.x,0));
		}
	}
	else if (phys_a_tag == EDGE_BOX_IN_PHYS_TAG && phys_b_tag == PLAYER_PHYBODY_TAG)
	{
		auto vel = phybody_b->getVelocity();
		if ((50 - fabs(vel.x)) > 0 && (vel.x != 0))
		{
			phybody_b->setVelocity(Vec2(0, vel.y));
		}
		if ((50 - fabs(vel.y)) > 0 && (vel.y != 0))
		{
			phybody_b->setVelocity(Vec2(vel.x, 0));
		}
	}
	return true;
}

void CharacterLayer::monster_refresh()
{

	switch (wave)
	{
		//Test.
		case -1 :
		{
			MonsterBoss* boss = MonsterBoss::create();
			boss->monster_init();
			boss->setPosition(Vec2(500, 500));
			this->addChild(boss);
			break;
		}
		//Wave start.
		case 0:
		{
			MonsterBird* monster1 = MonsterBird::create();
			monster1->monster_init();
			monster1->setPosition(Vec2(this->right_ref_x, 534));
			this->addChild(monster1);
			monster1->act1(5.0f,-50);

			MonsterBird* monster2 = MonsterBird::create();
			monster2->monster_init();
			monster2->setPosition(Vec2(this->right_ref_x+30, 434));
			this->addChild(monster2);
			monster2->act1(5.0f, -50);

			this->wave++;
			this->next_delay = CCDelayTime::create(2.0f);
			this->runAction(Sequence::create(next_delay, callback, nullptr));
			break;
		}
		case 1:
		{
			MonsterBird* monster3 = MonsterBird::create();
			monster3->monster_init();
			monster3->setPosition(Vec2(this->right_ref_x, 384));
			this->addChild(monster3);
			monster3->act1(2.0f, 50);

			MonsterBee* monster4 = MonsterBee::create();
			monster4->monster_init();
			monster4->setPosition(Vec2(this->right_ref_x, 100));
			this->addChild(monster4);
			monster4->act0(Size(200,200));

			this->wave++;
			this->next_delay = CCDelayTime::create(2.0f);
			this->runAction(Sequence::create(next_delay, callback, nullptr));
			break;
		}
		case 2:
		{
			MonsterBird* monster5 = MonsterBird::create();
			monster5->monster_init();
			monster5->setPosition(Vec2(this->right_ref_x, 284));
			this->addChild(monster5);
			monster5->act1(0.0f, 50);

			MonsterBee* monster6 = MonsterBee::create();
			monster6->monster_init();
			monster6->setPosition(Vec2(this->right_ref_x, 504));
			this->addChild(monster6);
			monster6->act2(0.5f,-50);

			MonsterBee* monster7 = MonsterBee::create();
			monster7->monster_init();
			monster7->setPosition(Vec2(this->right_ref_x+30, 434));
			this->addChild(monster7);
			monster7->act2(0.5f, -50);

			MonsterBee* monster8 = MonsterBee::create();
			monster8->monster_init();
			monster8->setPosition(Vec2(this->right_ref_x+60, 544));
			this->addChild(monster8);
			monster8->act2(0.5f, -50);

			this->wave++;
			this->next_delay = CCDelayTime::create(5.0f);
			this->runAction(Sequence::create(next_delay, callback, nullptr));
			break;

		}
		case 3:
		{
			MonsterRocket* monster9 = MonsterRocket::create();
			monster9->monster_init();
			monster9->setPosition(Vec2(this->right_ref_x, 100));
			this->addChild(monster9);
			monster9->act3(1.0f,100,5.0f);
			//Create delay sequence.
			auto sequence9 = Sequence::create(
				DelayTime::create(4.0f),
				CallFuncN::create([this, monster9](Node*)
				{
					this->addChild(monster9->monster_fire2(0));
				}),
				DelayTime::create(4.0f),
				CallFuncN::create([this, monster9](Node*)
				{
					this->addChild(monster9->monster_fire2(0));
				}),
				nullptr);
			monster9->runAction(sequence9);

			MonsterRocket* monster10 = MonsterRocket::create();
			monster10->monster_init();
			monster10->setPosition(Vec2(this->right_ref_x, 384));
			this->addChild(monster10);
			monster10->act3(1.0f, -70, 4.0f);
			auto sequence10 = Sequence::create(
				DelayTime::create(2.0f),
				CallFuncN::create([this, monster10](Node*)
				{
					std::vector<MonsterBullet*> bullets = monster10->monster_fire0();
					for (MonsterBullet* bullet : bullets)
					{
						this->addChild(bullet);
					}
				}),
				DelayTime::create(2.0f),
				CallFuncN::create([this, monster10](Node*)
				{
					std::vector<MonsterBullet*> bullets = monster10->monster_fire0();
					for (MonsterBullet* bullet : bullets)
					{
						this->addChild(bullet);
					}
				}), nullptr);
			monster10->runAction(sequence10);

			MonsterBird* monster11 = MonsterBird::create();
			monster11->monster_init();
			monster11->setPosition(Vec2(this->right_ref_x, 454));
			this->addChild(monster11);
			monster11->act1(4.0f, -50);

			MonsterBird* monster12 = MonsterBird::create();
			monster12->monster_init();
			monster12->setPosition(Vec2(this->right_ref_x+30, 384));
			this->addChild(monster12);
			monster12->act1(4.0f, -50);

			MonsterBird* monster13 = MonsterBird::create();
			monster13->monster_init();
			monster13->setPosition(Vec2(this->right_ref_x + 60, 556));
			this->addChild(monster13);
			monster13->act1(4.0f, -50);

			this->wave++;
			this->next_delay = CCDelayTime::create(2.0f);
			this->runAction(Sequence::create(next_delay, callback, nullptr));
			break;

		}
		case 4:
		{
			MonsterBird* monster14 = MonsterBird::create();
			monster14->monster_init();
			monster14->setPosition(Vec2(this->right_ref_x, 334));
			this->addChild(monster14);
			monster14->act1(0.0f, 50);

			MonsterBird* monster15 = MonsterBird::create();
			monster15->monster_init();
			monster15->setPosition(Vec2(this->right_ref_x+60, 234));
			this->addChild(monster15);
			monster15->act1(0.0f, 50);

			this->wave++;
			this->next_delay = CCDelayTime::create(7.0f);
			this->runAction(Sequence::create(next_delay, callback, nullptr));
			break;
		}
		case 5:
		{
			MonsterBee* monster16 = MonsterBee::create();
			monster16->monster_init();
			monster16->setPosition(Vec2(this->right_ref_x, 100));
			this->addChild(monster16);
			monster16->act2(0.2f, -30);
			auto pla = this->player;
			auto sequence16 = Sequence::create(
				DelayTime::create(7.0f),
				CallFuncN::create([this, monster16, pla](Node*)
				{
					this->addChild(monster16->monster_fire1(pla->getPosition()));
				}),nullptr);
			monster16->runAction(sequence16);

			MonsterBee* monster17 = MonsterBee::create();
			monster17->monster_init();
			monster17->setPosition(Vec2(this->right_ref_x, 526));
			this->addChild(monster17);
			monster17->act2(0.2f, -30);
			auto sequence17 = Sequence::create(
				DelayTime::create(7.0f),
				CallFuncN::create([this, monster17, pla](Node*)
				{
					this->addChild(monster17->monster_fire1(pla->getPosition()));
				}), nullptr);
			monster17->runAction(sequence17);

			MonsterBee* monster18 = MonsterBee::create();
			monster18->monster_init();
			monster18->setPosition(Vec2(this->right_ref_x+30, 334));
			this->addChild(monster18);
			monster18->act2(0.2f, -30);
			auto sequence18 = Sequence::create(
				DelayTime::create(7.0f),
				CallFuncN::create([this, monster18, pla](Node*)
				{
					this->addChild(monster18->monster_fire1(pla->getPosition()));
				}), nullptr);
			monster18->runAction(sequence18);

			this->wave++;
			this->next_delay = CCDelayTime::create(5.0f);
			this->runAction(Sequence::create(next_delay, callback, nullptr));
			break;
		}
		case 6:
		{
			MonsterBird* monster19 = MonsterBird::create();
			monster19->monster_init();
			monster19->setPosition(Vec2(this->right_ref_x, 304));
			this->addChild(monster19);
			monster19->act1(10.0f, 0);
			auto sequence19 = Sequence::create(
				DelayTime::create(3.0f),
				CallFuncN::create([this, monster19](Node*)
				{
					this->addChild(monster19->monster_fire2(50));
				}),
				DelayTime::create(1.0f),
					CallFuncN::create([this, monster19](Node*)
				{
					this->addChild(monster19->monster_fire2(-50));
				}),nullptr);
			monster19->runAction(sequence19);

			MonsterBird* monster20 = MonsterBird::create();
			monster20->monster_init();
			monster20->setPosition(Vec2(this->right_ref_x+30, 234));
			this->addChild(monster20);
			monster20->act1(3.5f, -50);
			auto pla = this->player;
			auto sequence20 = Sequence::create(
				DelayTime::create(4.5f),
				CallFuncN::create([this, monster20, pla](Node*)
				{
					this->addChild(monster20->monster_fire1(pla->getPosition()));
				}), nullptr);
			monster20->runAction(sequence20);

			MonsterBird* monster21 = MonsterBird::create();
			monster21->monster_init();
			monster21->setPosition(Vec2(this->right_ref_x + 30, 374));
			this->addChild(monster21);
			monster21->act1(3.5f, 50);
			//auto pla = this->player;
			auto sequence21 = Sequence::create(
				DelayTime::create(4.5f),
				CallFuncN::create([this, monster21, pla](Node*)
			{
				this->addChild(monster21->monster_fire1(pla->getPosition()));
			}), nullptr);
			monster21->runAction(sequence21);
		
			this->wave++;
			this->next_delay = CCDelayTime::create(1.0f);
			this->runAction(Sequence::create(next_delay, callback, nullptr));
			break;
		}
		case 7:
		{
			MonsterSuper* monster22 = MonsterSuper::create();
			monster22->monster_init();
			monster22->setPosition(Vec2(this->right_ref_x, 304));
			this->addChild(monster22);
			monster22->act4();
			Player* pla = this->player;
			auto sequence22 = Sequence::create(
				DelayTime::create(1.5f),
				CallFuncN::create([this, monster22, pla](Node*)
				{
					this->addChild(monster22->monster_fire1(pla->getPosition()));
				}), 
				DelayTime::create(1.0f),
				CallFuncN::create([this, monster22, pla](Node*)
				{
					this->addChild(monster22->monster_fire1(pla->getPosition()));
				}),
				DelayTime::create(1.0f),
				CallFuncN::create([this, monster22, pla](Node*)
				{
					this->addChild(monster22->monster_fire1(pla->getPosition()));
				}),nullptr);
			monster22->runAction(sequence22);

			this->wave++;
			this->next_delay = CCDelayTime::create(4.0f);
			this->runAction(Sequence::create(next_delay, callback, nullptr));
			break;
		}
		case 8:
		{
			MonsterSuper* monster23 = MonsterSuper::create();
			monster23->monster_init();
			monster23->setPosition(Vec2(150, this->top_ref_y));
			this->addChild(monster23);
			monster23->act5(Size(50, 50), 0.3f);
			Player* pla = this->player;
			auto sequence23 = Sequence::create(
				DelayTime::create(5.0f),
				CallFuncN::create([this, monster23, pla](Node*)
				{
					this->addChild(monster23->monster_fire1(pla->getPosition()));
				}),
				DelayTime::create(5.0f),
				CallFuncN::create([this, monster23, pla](Node*)
				{
					this->addChild(monster23->monster_fire1(pla->getPosition()));
				}),nullptr);
			monster23->runAction(sequence23);

			MonsterSuper* monster24 = MonsterSuper::create();
			monster24->monster_init();
			monster24->setPosition(Vec2(800, this->top_ref_y));
			this->addChild(monster24);
			monster24->act5(Size(50, 50), 0.3);
			auto sequence24 = Sequence::create(
				DelayTime::create(10.0f),
				CallFuncN::create([this, monster24, pla](Node*)
				{
					this->addChild(monster24->monster_fire1(pla->getPosition()));
				}), nullptr);
			monster24->runAction(sequence24);

			MonsterSuper* monster25 = MonsterSuper::create();
			monster25->monster_init();
			monster25->setPosition(Vec2(400, this->top_ref_y+60));
			this->addChild(monster25);
			monster25->act5(Size(50, 50), 0.5);

			MonsterRocket* monster26 = MonsterRocket::create();
			monster26->monster_init();
			monster26->setPosition(Vec2(this->right_ref_x, 50));
			this->addChild(monster26);
			monster26->act3(1.0f,50,6.0f);

			MonsterRocket* monster27 = MonsterRocket::create();
			monster27->monster_init();
			monster27->setPosition(Vec2(this->right_ref_x+60, 284));
			this->addChild(monster27);
			monster27->act3(1.0f, -50, 1.5f);
			auto sequence27 = Sequence::create(
				DelayTime::create(1.0f),
				CallFuncN::create([this, monster27](Node*)
				{
					std::vector<MonsterBullet*> bullets = monster27->monster_fire0();
					for (MonsterBullet* bullet : bullets)
					{
						this->addChild(bullet);
					}
				}),
				DelayTime::create(1.0f),
				CallFuncN::create([this, monster27](Node*)
				{
					std::vector<MonsterBullet*> bullets = monster27->monster_fire0();
					for (MonsterBullet* bullet : bullets)
					{
						this->addChild(bullet);
					}
				}), nullptr);
			monster27->runAction(sequence27);

			this->wave++;
			this->next_delay = CCDelayTime::create(2.0f);
			this->runAction(Sequence::create(next_delay, callback, nullptr));
			break;
		}
		case 9:
		{
			MonsterBee* monster28 = MonsterBee::create();
			monster28->monster_init();
			monster28->setPosition(Vec2(this->right_ref_x, 420));
			this->addChild(monster28);
			monster28->act0(Size(150, 150));

			MonsterBee* monster29 = MonsterBee::create();
			monster29->monster_init();
			monster29->setPosition(Vec2(this->right_ref_x+60, 450));
			this->addChild(monster29);
			monster29->act0(Size(150, 150));
			auto sequence29 = Sequence::create(
				DelayTime::create(5.0f),
				CallFuncN::create([this, monster29](Node*)
				{
					this->addChild(monster29->monster_fire2(0.0f));
				}), nullptr);
			monster28->runAction(sequence29);

			this->wave++;
			this->next_delay = CCDelayTime::create(2.0f);
			this->runAction(Sequence::create(next_delay, callback, nullptr));
			break;
		}
		case 10:
		{
			MonsterBird* monster30 = MonsterBird::create();
			monster30->monster_init();
			monster30->setPosition(Vec2(this->right_ref_x, 484));
			this->addChild(monster30);
			monster30->act1(1.0f, -50);

			MonsterBird* monster31 = MonsterBird::create();
			monster31->monster_init();
			monster31->setPosition(Vec2(this->right_ref_x+30, 534));
			this->addChild(monster31);
			monster31->act1(1.0f, -50);

			MonsterBird* monster32 = MonsterBird::create();
			monster32->monster_init();
			monster32->setPosition(Vec2(this->right_ref_x + 60, 584));
			this->addChild(monster32);
			monster32->act1(1.0f, -50);

			this->wave++;
			this->next_delay = CCDelayTime::create(5.0f);
			this->runAction(Sequence::create(next_delay, callback, nullptr));
			break;
		}
		case 11:
		{
			MonsterBee* monster33 = MonsterBee::create();
			monster33->monster_init();
			monster33->setPosition(Vec2(this->right_ref_x, 350));
			this->addChild(monster33);
			monster33->act1(10.0f,0);

			MonsterBee* monster34 = MonsterBee::create();
			monster34->monster_init();
			monster34->setPosition(Vec2(this->right_ref_x+30, 380));
			this->addChild(monster34);
			monster34->act1(3.0f, 40);
			Player* pla = this->player;
			auto sequence34 = Sequence::create(
				DelayTime::create(4.0f),
				CallFuncN::create([this, monster34, pla](Node*)
				{
					this->addChild(monster34->monster_fire1(pla->getPosition()));
				}), nullptr);
			monster34->runAction(sequence34);

			MonsterBee* monster35 = MonsterBee::create();
			monster35->monster_init();
			monster35->setPosition(Vec2(this->right_ref_x + 30, 320));
			this->addChild(monster35);
			monster35->act1(3.0f, -40);
			auto sequence35 = Sequence::create(
				DelayTime::create(4.0f),
				CallFuncN::create([this, monster35, pla](Node*)
				{
					this->addChild(monster35->monster_fire1(pla->getPosition()));
				}), nullptr);
			monster35->runAction(sequence35);

			MonsterBee* monster36 = MonsterBee::create();
			monster36->monster_init();
			monster36->setPosition(Vec2(this->right_ref_x + 60, 410));
			this->addChild(monster36);
			monster36->act1(3.0f, 80);
			auto sequence36 = Sequence::create(
				DelayTime::create(5.0f),
				CallFuncN::create([this, monster36, pla](Node*)
				{
					this->addChild(monster36->monster_fire1(pla->getPosition()));
				}), nullptr);
			monster36->runAction(sequence36);

			MonsterBee* monster37 = MonsterBee::create();
			monster37->monster_init();
			monster37->setPosition(Vec2(this->right_ref_x + 60, 290));
			this->addChild(monster37);
			monster37->act1(3.0f, -80);
			auto sequence37 = Sequence::create(
				DelayTime::create(5.0f),
				CallFuncN::create([this, monster37, pla](Node*)
			{
				this->addChild(monster37->monster_fire1(pla->getPosition()));
			}), nullptr);
			monster37->runAction(sequence37);

			this->wave++;
			this->next_delay = CCDelayTime::create(3.0f);
			this->runAction(Sequence::create(next_delay, callback, nullptr));
			break;
		}
		case 12:
		{
			MonsterRocket* monster38 = MonsterRocket::create();
			monster38->monster_init();
			monster38->setPosition(Vec2(this->right_ref_x, 50));
			this->addChild(monster38);
			monster38->act0(Size(150, 200));
			auto sequence38 = Sequence::create(
				DelayTime::create(6.0f),
				CallFuncN::create([this, monster38](Node*)
				{
					std::vector<MonsterBullet*> bullets = monster38->monster_fire0();
					for (MonsterBullet* bullet : bullets)
					{
						this->addChild(bullet);
					}
				}), nullptr);
			monster38->runAction(sequence38);

			MonsterRocket* monster39 = MonsterRocket::create();
			monster39->monster_init();
			monster39->setPosition(Vec2(this->right_ref_x, 484));
			this->addChild(monster39);
			monster39->act0(Size(150, 200));
			auto sequence39 = Sequence::create(
				DelayTime::create(6.0f),
				CallFuncN::create([this, monster39](Node*)
			{
				std::vector<MonsterBullet*> bullets = monster39->monster_fire0();
				for (MonsterBullet* bullet : bullets)
				{
					this->addChild(bullet);
				}
			}), nullptr);
			monster39->runAction(sequence39);

			this->wave++;
			this->next_delay = CCDelayTime::create(6.0f);
			this->runAction(Sequence::create(next_delay, callback, nullptr));
			break;
		}
		//Same logic for wave 13 and 17.
		case 13:
		case 17:
		{
			MonsterBee* monster40 = MonsterBee::create();
			monster40->monster_init();
			monster40->setPosition(Vec2(this->right_ref_x - 60, this->top_ref_y + 60));
			this->addChild(monster40);
			monster40->act1(0.0f, -80);

			MonsterBee* monster41 = MonsterBee::create();
			monster41->monster_init();
			monster41->setPosition(Vec2(this->right_ref_x, this->top_ref_y));
			this->addChild(monster41);
			monster41->act1(0.0f, -80);

			MonsterBee* monster42 = MonsterBee::create();
			monster42->monster_init();
			monster42->setPosition(Vec2(this->right_ref_x + 60, this->top_ref_y - 60));
			this->addChild(monster42);
			monster42->act1(0.0f, -80);

			MonsterBee* monster43 = MonsterBee::create();
			monster43->monster_init();
			monster43->setPosition(Vec2(this->right_ref_x - 30, -30));
			this->addChild(monster43);
			monster43->act1(0.0f, 80);

			MonsterBee* monster44 = MonsterBee::create();
			monster44->monster_init();
			monster44->setPosition(Vec2(this->right_ref_x + 30, 30));
			this->addChild(monster44);
			monster44->act1(0.0f, 80);

			MonsterBee* monster45 = MonsterBee::create();
			monster45->monster_init();
			monster45->setPosition(Vec2(this->right_ref_x + 90, 90));
			this->addChild(monster45);
			monster45->act1(0.0f, 80);

			this->wave++;
			this->next_delay = CCDelayTime::create(2.0f);
			this->runAction(Sequence::create(next_delay, callback, nullptr));
			break;
		}
		case 18:
		case 14:
		{		
			MonsterRocket* monster46 = MonsterRocket::create();
			monster46->monster_init();
			monster46->setPosition(Vec2(this->right_ref_x, 10));
			this->addChild(monster46);
			monster46->act3(1.0f,50,3.0f);
			Player* pla = this->player;
			auto sequence46 = Sequence::create(
				DelayTime::create(4.0f),
				CallFuncN::create([this, monster46](Node*)
				{
					this->addChild(monster46->monster_fire2(0));
				}),
				DelayTime::create(1.0f),
				CallFuncN::create([this, monster46, pla](Node*)
				{
					this->addChild(monster46->monster_fire1(pla->getPosition()));
				}), nullptr);
			monster46->runAction(sequence46);

			MonsterRocket* monster47 = MonsterRocket::create();
			monster47->monster_init();
			monster47->setPosition(Vec2(this->right_ref_x, 384));
			this->addChild(monster47);
			monster47->act3(0.0f, 0, 1.0f);
			//Player* pla = this->player;
			auto sequence47 = Sequence::create(
				DelayTime::create(2.0f),
				CallFuncN::create([this, monster47](Node*)
				{
					std::vector<MonsterBullet*> bullets = monster47->monster_fire0();
					for (MonsterBullet* bullet : bullets)
					{
						this->addChild(bullet);
					}
				}), nullptr);
			monster47->runAction(sequence47);

			this->wave++;
			this->next_delay = CCDelayTime::create(6.0f);
			this->runAction(Sequence::create(next_delay, callback, nullptr));
			break;
		}
		case 15:
		{
			MonsterRocket* monster48 = MonsterRocket::create();
			monster48->monster_init();
			monster48->setPosition(Vec2(this->right_ref_x, 384));
			this->addChild(monster48);
			monster48->act0(Size(150,100));
			auto sequence48 = Sequence::create(
				DelayTime::create(5.0f),
				CallFuncN::create([this, monster48](Node*)
				{
					std::vector<MonsterBullet*> bullets = monster48->monster_fire0();
					for (MonsterBullet* bullet : bullets)
					{
						this->addChild(bullet);
					}
				}), nullptr);
			monster48->runAction(sequence48);

			MonsterRocket* monster49 = MonsterRocket::create();
			monster49->monster_init();
			monster49->setPosition(Vec2(this->right_ref_x, 192));
			this->addChild(monster49);
			monster49->act0(Size(150, 100));
			auto sequence49 = Sequence::create(
				DelayTime::create(5.0f),
				CallFuncN::create([this, monster49](Node*)
				{
					std::vector<MonsterBullet*> bullets = monster49->monster_fire0();
					for (MonsterBullet* bullet : bullets)
					{
						this->addChild(bullet);
					}
				}), nullptr);
			monster49->runAction(sequence49);

			this->wave++;
			this->next_delay = CCDelayTime::create(2.0f);
			this->runAction(Sequence::create(next_delay, callback, nullptr));
			break;

		}
		case 16:
		{
			MonsterBird* monster50 = MonsterBird::create();
			monster50->monster_init();
			monster50->setPosition(Vec2(this->right_ref_x, 434));
			this->addChild(monster50);
			monster50->act1(2.0f, -80);
			Player* pla = this->player;
			auto sequence50 = Sequence::create(
				DelayTime::create(4.0f),
				CallFuncN::create([this, monster50, pla](Node*)
				{
					this->addChild(monster50->monster_fire1(pla->getPosition()));
				}), nullptr);
			monster50->runAction(sequence50);

			MonsterBird* monster51 = MonsterBird::create();
			monster51->monster_init();
			monster51->setPosition(Vec2(this->right_ref_x, 234));
			this->addChild(monster51);
			monster51->act1(2.0f, 80);
			auto sequence51 = Sequence::create(
				DelayTime::create(4.0f),
				CallFuncN::create([this, monster51, pla](Node*)
				{
					this->addChild(monster51->monster_fire1(pla->getPosition()));
				}), nullptr);
			monster51->runAction(sequence51);

			MonsterBird* monster52 = MonsterBird::create();
			monster52->monster_init();
			monster52->setPosition(Vec2(this->right_ref_x+30, 384));
			this->addChild(monster52);
			monster52->act1(2.0f, -40);
			auto sequence52 = Sequence::create(
				DelayTime::create(4.0f),
				CallFuncN::create([this, monster52, pla](Node*)
				{
					this->addChild(monster52->monster_fire1(pla->getPosition()));
				}), nullptr);
			monster52->runAction(sequence52);

			MonsterBird* monster53 = MonsterBird::create();
			monster53->monster_init();
			monster53->setPosition(Vec2(this->right_ref_x+30, 284));
			this->addChild(monster53);
			monster53->act1(2.0f, 40);
			auto sequence53 = Sequence::create(
				DelayTime::create(4.0f),
				CallFuncN::create([this, monster53, pla](Node*)
				{
					this->addChild(monster53->monster_fire1(pla->getPosition()));
				}), nullptr);
			monster53->runAction(sequence53);

			MonsterBird* monster54 = MonsterBird::create();
			monster54->monster_init();
			monster54->setPosition(Vec2(this->right_ref_x+60, 334));
			this->addChild(monster54);
			monster54->act1(10.0f, 0);
			auto sequence54 = Sequence::create(
				DelayTime::create(3.0f),
				CallFuncN::create([this, monster54](Node*)
				{
					this->addChild(monster54->monster_fire2(0));
				}), nullptr);
			monster54->runAction(sequence54);

			this->wave++;
			this->next_delay = CCDelayTime::create(2.0f);
			this->runAction(Sequence::create(next_delay, callback, nullptr));
			break;
		}
		case 25:
		case 24:
		case 23:
		case 20:
		case 19:
		{
			Vec2 position;
			if (this->wave == 19 || this->wave == 24)
			{
				position = Vec2(this->right_ref_x, 576);
				this->next_delay = CCDelayTime::create(3.0f);
			}
			else if (this->wave == 20 || this->wave == 25)
			{
				position = Vec2(this->right_ref_x, 284);
				this->next_delay = CCDelayTime::create(2.0f);
			}
			else if (this->wave == 23)
			{
				position = Vec2(this->right_ref_x, 184);
				this->next_delay = CCDelayTime::create(5.0f);
			}
		
			Player* pla = this->player;
			int number = 0;
			monster_sequence = CallFuncN::create(
				[this, position, number, pla](Node*) mutable
				{
					auto monster = MonsterBird::create();
					monster->monster_init();
					monster->setPosition(position);
					this->addChild(monster);
					monster->act6(Size(200, 70), 1.0f);
					if (number == 0)
					{
						Sequence* fire_seq = Sequence::create(
							DelayTime::create(3.0f),
							CallFuncN::create(
								[this, pla, monster](Node*)
								{
									this->addChild(monster->monster_fire1(pla->getPosition()));
								}
							), nullptr
						);
						monster->runAction(fire_seq);
					}
					else if (number == 5)
					{
						Sequence* fire_seq = Sequence::create(
							DelayTime::create(5.0f),
							CallFuncN::create(
								[this, pla, monster](Node*)
								{
									this->addChild(monster->monster_fire1(pla->getPosition()));
								}
							), nullptr
						);
						monster->runAction(fire_seq);

					}

					number++;
				}
			);

			auto delay1 = DelayTime::create(0.2f);
			Sequence* sequence_row = Sequence::create(
				monster_sequence, delay1->clone(),
				monster_sequence, delay1->clone(),
				monster_sequence, delay1->clone(),
				monster_sequence, delay1->clone(),
				monster_sequence, delay1->clone(),
				monster_sequence, delay1->clone(),nullptr);

			this->runAction(sequence_row);

			this->wave++;
			this->runAction(Sequence::create(next_delay, callback, nullptr));
			break;
		}
		case 26:
		case 21:
		{
			MonsterBee* monster55 = MonsterBee::create();
			monster55->monster_init();
			monster55->setPosition(Vec2(this->right_ref_x, 484));
			this->addChild(monster55);
			monster55->act2(0.3f, 50);
			Player* pla = this->player;
			auto sequence55 = Sequence::create(
				DelayTime::create(4.0f),
				CallFuncN::create(
					[this, monster55, pla](Node*)
					{
						this->addChild(monster55->monster_fire1(pla->getPosition()));
					}
				),
				nullptr
			);
			monster55->runAction(sequence55);

			MonsterBee* monster56 = MonsterBee::create();
			monster56->monster_init();
			monster56->setPosition(Vec2(this->right_ref_x + 60, 384));
			this->addChild(monster56);
			monster56->act2(0.3f, 50);
			auto sequence56 = Sequence::create(
				DelayTime::create(4.0f),
				CallFuncN::create(
					[this, monster56, pla](Node*)
					{
						this->addChild(monster56->monster_fire1(pla->getPosition()));
					}
				),
				nullptr
				);
			monster56->runAction(sequence56);

			MonsterBee* monster57 = MonsterBee::create();
			monster57->monster_init();
			monster57->setPosition(Vec2(this->right_ref_x + 60, 584));
			this->addChild(monster57);
			monster57->act2(0.3f, 50);
			auto sequence57 = Sequence::create(
				DelayTime::create(4.0f),
				CallFuncN::create(
					[this, monster57, pla](Node*)
					{
						this->addChild(monster57->monster_fire1(pla->getPosition()));
					}
				),
				nullptr
				);
			monster57->runAction(sequence57);

			this->wave++;
			this->next_delay = DelayTime::create(5.0f);
			this->runAction(Sequence::create(next_delay, callback, nullptr));
			break;
		}
		case 22:
		{
			Player* pla = this->player;

			MonsterBee* monster56 = MonsterBee::create();
			monster56->monster_init();
			monster56->setPosition(Vec2(this->right_ref_x, 584));
			this->addChild(monster56);
			monster56->act1(10.0f, 0);
			auto sequence56 = Sequence::create(
				DelayTime::create(2.0f),
				CallFuncN::create(
					[this, monster56, pla](Node*)
					{
						this->addChild(monster56->monster_fire1(pla->getPosition()));
					}
				),
				DelayTime::create(2.0f),
				CallFuncN::create(
					[this, monster56, pla](Node*)
					{
						this->addChild(monster56->monster_fire1(pla->getPosition()));
					}
				),
				nullptr
			);
			monster56->runAction(sequence56);

			MonsterBee* monster57 = MonsterBee::create();
			monster57->monster_init();
			monster57->setPosition(Vec2(this->right_ref_x + 30, 634));
			this->addChild(monster57);
			monster57->act1(4.0f, -80);
			auto sequence57 = Sequence::create(
				DelayTime::create(3.0f),
				CallFuncN::create(
					[this, monster57, pla](Node*)
					{
						this->addChild(monster57->monster_fire1(pla->getPosition()));
					}
				),
				nullptr
				);
			monster57->runAction(sequence57);

			MonsterBee* monster58 = MonsterBee::create();
			monster58->monster_init();
			monster58->setPosition(Vec2(this->right_ref_x + 30, 534));
			this->addChild(monster58);
			monster58->act1(4.0f, 80);
			auto sequence58 = Sequence::create(
				DelayTime::create(3.0f),
				CallFuncN::create(
					[this, monster58, pla](Node*)
					{
						this->addChild(monster58->monster_fire1(pla->getPosition()));
					}
				),
				nullptr
				);
			monster58->runAction(sequence58);

			MonsterBee* monster59 = MonsterBee::create();
			monster59->monster_init();
			monster59->setPosition(Vec2(this->right_ref_x + 60, 684));
			this->addChild(monster59);
			monster59->act1(4.0f, -90);
			auto sequence59 = Sequence::create(
				DelayTime::create(3.5f),
				CallFuncN::create(
					[this, monster59, pla](Node*)
					{
						this->addChild(monster59->monster_fire1(pla->getPosition()));
					}
				),
				nullptr
				);
			monster59->runAction(sequence59);

			MonsterBee* monster60 = MonsterBee::create();
			monster60->monster_init();
			monster60->setPosition(Vec2(this->right_ref_x + 60, 484));
			this->addChild(monster60);
			monster60->act1(4.0f, 80);
			auto sequence60 = Sequence::create(
				DelayTime::create(3.5f),
				CallFuncN::create(
					[this, monster60, pla](Node*)
					{
						this->addChild(monster60->monster_fire1(pla->getPosition()));
					}
				),
				nullptr
				);
			monster60->runAction(sequence60);

			this->wave++;
			this->next_delay = DelayTime::create(5.0f);
			this->runAction(Sequence::create(next_delay, callback, nullptr));
			break;

		}
		case 27:
		{
			Player* pla = this->player;

			MonsterSuper* monster61 = MonsterSuper::create();
			monster61->monster_init();
			monster61->setPosition(Vec2(412, this->top_ref_y));
			this->addChild(monster61);
			monster61->act5(Size(50,50),0.5f);
			auto sequence61 = Sequence::create(
				DelayTime::create(4.0f),
				CallFuncN::create(
					[this, monster61, pla](Node*)
					{
						this->addChild(monster61->monster_fire1(pla->getPosition()));
					}
				),
				nullptr
				);
			monster61->runAction(sequence61);

			MonsterSuper* monster62 = MonsterSuper::create();
			monster62->monster_init();
			monster62->setPosition(Vec2(362, this->top_ref_y+30));
			this->addChild(monster62);
			monster62->act5(Size(50, 50), 0.7f);

			MonsterSuper* monster63 = MonsterSuper::create();
			monster63->monster_init();
			monster63->setPosition(Vec2(562, this->top_ref_y+30));
			this->addChild(monster63);
			monster63->act5(Size(50, 50), 0.7f);

			MonsterSuper* monster64 = MonsterSuper::create();
			monster64->monster_init();
			monster64->setPosition(Vec2(312, this->top_ref_y+60));
			this->addChild(monster64);
			monster64->act5(Size(50, 50), 0.5f);
			auto sequence64 = Sequence::create(
				DelayTime::create(4.0f),
				CallFuncN::create(
					[this, monster64, pla](Node*)
					{
						this->addChild(monster64->monster_fire1(pla->getPosition()));
					}
				),
				DelayTime::create(1.0f),
				CallFuncN::create(
					[this, monster64, pla](Node*)
					{
						this->addChild(monster64->monster_fire1(pla->getPosition()));
					}
				),
				nullptr
				);
			monster64->runAction(sequence64);

			MonsterSuper* monster65 = MonsterSuper::create();
			monster65->monster_init();
			monster65->setPosition(Vec2(612, this->top_ref_y+60));
			this->addChild(monster65);
			monster65->act5(Size(50, 50), 0.5f);
			auto sequence65 = Sequence::create(
				DelayTime::create(4.0f),
				CallFuncN::create(
					[this, monster65, pla](Node*)
					{
						this->addChild(monster65->monster_fire1(pla->getPosition()));
					}
				),
				DelayTime::create(1.0f),
				CallFuncN::create(
					[this, monster65, pla](Node*)
					{
						this->addChild(monster65->monster_fire1(pla->getPosition()));
					}
				),
				nullptr
				);
			monster65->runAction(sequence65);

			MonsterSuper* monster66 = MonsterSuper::create();
			monster66->monster_init();
			monster66->setPosition(Vec2(900, this->top_ref_y+60));
			this->addChild(monster66);
			monster66->act5(Size(50, 50), 0.5f);
			auto sequence66 = Sequence::create(
				DelayTime::create(4.0f),
				CallFuncN::create(
					[this, monster66, pla](Node*)
					{
						this->addChild(monster66->monster_fire1(pla->getPosition()));
					}
				),
				DelayTime::create(1.0f),
				CallFuncN::create(
					[this, monster66, pla](Node*)
					{
						this->addChild(monster66->monster_fire1(pla->getPosition()));
					}
				),
				nullptr
				);
			monster66->runAction(sequence66);

			this->wave++;
			this->next_delay = DelayTime::create(16.0f);
			this->runAction(Sequence::create(next_delay, callback, nullptr));
			break;
		}
		case 28:
		{
			Player* pla = this->player;

			int number = 0;
			this->monster_sequence = CallFuncN::create(
				[this, number, pla](Node*) mutable
				{
					float y_pos = 0;
					switch (number)
					{
					case 0:
						y_pos = 668;
						break;
					case 1:
						y_pos = 568;
						break;
					case 2:
						y_pos = 468;
						break;
					case 3:
						y_pos = 368;
						break;
					case 4:
						y_pos = 268;
						break;
					}
					MonsterRocket* monster = MonsterRocket::create();
					monster->monster_init();
					monster->setPosition(Vec2(this->right_ref_x, y_pos));
					this->addChild(monster);
					monster->act1(10.0f, 0);

					auto fire_seq = Sequence::create(
						DelayTime::create(3.0f),
						CallFuncN::create(
							[this, monster, pla](Node*)
							{
								this->addChild(monster->monster_fire1(pla->getPosition()));
							}
						),
						nullptr
						);
					monster->runAction(fire_seq);
					(number)++;
				} 
			);

			auto delay2 = DelayTime::create(1.0f);
			Sequence* monster_scall = Sequence::create(
				monster_sequence, delay2->clone(),
				monster_sequence, delay2->clone(),
				monster_sequence, delay2->clone(),
				monster_sequence, delay2->clone(),
				monster_sequence, nullptr
			);
			this->runAction(monster_scall);

			this->wave++;
			this->next_delay = DelayTime::create(10.0f);
			this->runAction(Sequence::create(next_delay, callback, nullptr));
			break;
		}
		case 29:
		{
			int number = 0;
			this->monster_sequence = CallFuncN::create(
				[this, number](Node*) mutable
			{
				float y_pos = 0;
				switch (number)
				{
				case 0:
					y_pos = 100;
					break;
				case 1:
					y_pos = 200;
					break;
				case 2:
					y_pos = 300;
					break;
				case 3:
					y_pos = 400;
					break;
				case 4:
					y_pos = 500;
					break;
				}
				MonsterRocket* monster = MonsterRocket::create();
				monster->monster_init();
				monster->setPosition(Vec2(this->right_ref_x, y_pos));
				this->addChild(monster);
				monster->act3(0.0f, 0,0.0f);

				auto fire_seq = Sequence::create(
					DelayTime::create(3.0f),
					CallFuncN::create(
						[this, monster](Node*)
						{
							std::vector<MonsterBullet*> bullets = monster->monster_fire0();
							for (MonsterBullet* bullet:bullets)
							{
								this->addChild(bullet);
							}
						}
					),
					nullptr
					);
				monster->runAction(fire_seq);

				(number)++;
			}
			);

			auto delay3 = DelayTime::create(0.5f);
			Sequence* monster_scall = Sequence::create(
				monster_sequence, delay3->clone(),
				monster_sequence, delay3->clone(),
				monster_sequence, delay3->clone(),
				monster_sequence, delay3->clone(),
				monster_sequence, nullptr
			);
			this->runAction(monster_scall);

			this->wave++;
			this->next_delay = DelayTime::create(10.0f);
			this->runAction(Sequence::create(next_delay, callback, nullptr));
			break;

		}
		case 30:
		{
			this->boss_stage_flag = true;

			Player* pla = this->player;

			auto boss = MonsterBoss::create();
			boss->monster_init();
			boss->setPosition(Vec2(this->right_ref_x, visibleSize.height / 2 + origin.y));
			this->addChild(boss);

			auto moveby = MoveBy::create(1.0f, Vec2(-200, 0));
			auto sequencetest = Sequence::create(
				moveby,
				CallFunc::create(boss, callfunc_selector(MonsterBoss::act7)),
				nullptr
			);
			boss->runAction(sequencetest);
			auto fire_seq = Sequence::create(
				DelayTime::create(1.0f),
				CallFuncN::create(
					[this, boss](Node*)
					{
						std::vector<MonsterBullet*> bullets = boss->monster_fire3(Size(100, 50));
						for (MonsterBullet* bullet : bullets)
						{
							this->addChild(bullet);
						}
					}
				),
				DelayTime::create(1.0f),
				CallFuncN::create(
					[this, boss](Node*)
					{
						std::vector<MonsterBullet*> bullets = boss->monster_fire3(Size(100, 50));
						for (MonsterBullet* bullet : bullets)
						{
							this->addChild(bullet);
						}
					}
				),
				DelayTime::create(1.0f),
				CallFuncN::create(
					[this, boss](Node*)
					{
						std::vector<MonsterBullet*> bullets = boss->monster_fire3(Size(100, 50));
						for (MonsterBullet* bullet : bullets)
						{
							this->addChild(bullet);
						}
					}
				),
				DelayTime::create(1.0f),
				CallFuncN::create(
					[this, boss, pla](Node*)
					{
						this->addChild(boss->monster_fire1(pla->getPosition()));
					}
				),
				nullptr
				);

			boss->runAction(RepeatForever::create(fire_seq));
			break;
		}
	}
}

bool CharacterLayer::getBSF()
{
	return this->boss_stage_flag;
}

int CharacterLayer::get_plife()
{
	return this->player->get_plife();
}

void CharacterLayer::set_scoreup(bool score_up)
{
	this->score_up = score_up;
}

bool CharacterLayer::get_scoreup()
{
	return this->score_up;
}

bool CharacterLayer::get_win_flag()
{
	return this->win_flag;
}