#include "Monster.h"

USING_NS_CC;

void Monster::setMonster_physize(Size size)
{
	this->monster_physize = size;
}

cocos2d::Size Monster::getMonster_physize()
{
	return this->monster_physize;
}

void Monster::setMonster_phys_tag(int tag)
{
	this->monster_phys->setTag(tag);
}

int Monster::getMonster_phys_tag()
{
	return this->monster_phys->getTag();
}

void Monster::setMonster_phys_category(int category)
{
	this->monster_phys->setCategoryBitmask(category);
}

int Monster::getMonster_phys_category()
{
	return this->monster_phys->getCategoryBitmask();
}

void Monster::setMonster_phys_collision(int collision)
{
	this->monster_phys->setCollisionBitmask(collision);
}

void Monster::setMonster_phys_contacttest(int contacttest)
{
	this->monster_phys->setContactTestBitmask(contacttest);
}

int Monster::getMonster_phys_contacttest()
{
	return this->monster_phys->getContactTestBitmask();
}

void Monster::setPhys_dynamic(bool flag)
{
	this->monster_phys->setDynamic(flag);
}

void Monster::setPhys_gravity(bool flag)
{
	this->monster_phys->setGravityEnable(flag);
}

void Monster::setPhys_rotation(bool flag)
{
	this->monster_phys->setRotationEnable(flag);
}

void Monster::setPhys_velocity(cocos2d::Vec2 vel)
{
	this->monster_phys->setVelocity(vel);
}

bool Monster::hited()
{
	if (this->state == MonStateEnum::dead)
	{
		return false;
	}

	this->health--;
	//dead.
	if (this->health <= 0)
	{
		this->state = MonStateEnum::dead;

		//Clean up and destroy.
		auto sequ = Sequence::create(
			CCCallFuncN::create(
				[this](Node*)
				{
					this->setMonster_phys_category(0x0);
					this->setMonster_phys_collision(0x0);
					this->setMonster_phys_contacttest(0x0);
					this->setSpriteFrame(M_CLOUD_FILE_NAME);
				}
			),
			CCDelayTime::create(0.5f),
			CCCallFuncN::create(
				[this](Node*)
				{
					this->removeFromParentAndCleanup(true);
				}
			),
			nullptr
		);
		this->stopAllActions();
		this->runAction(sequ);

		return true;
		
	}
	return false;
}

void Monster::act0(Size size)
{
	//Set Bezier lines.
	ccBezierConfig bez_conf;

	bez_conf.controlPoint_1 = Vec2(-(size.width*0.255), (size.height*0.0));
	bez_conf.controlPoint_2 = Vec2(-(size.width*0.353), (size.height*0.123));
	bez_conf.endPosition = Vec2(-(size.width*0.353), (size.height*0.278));
	auto bez1 = BezierBy::create(0.3f, bez_conf);

	bez_conf.controlPoint_1 = Vec2((size.width*0.0), (size.height*0.154));
	bez_conf.controlPoint_2 = Vec2((size.width*0.268), (size.height*0.2));
	bez_conf.endPosition = Vec2((size.width*0.268), (size.height*0.4));
	auto bez2 = BezierBy::create(0.3f, bez_conf);

	bez_conf.controlPoint_1 = Vec2((size.width*0.0), (size.height*0.169));
	bez_conf.controlPoint_2 = Vec2(-(size.width*0.134), (size.height*0.292));
	bez_conf.endPosition = Vec2(-(size.width*0.390), (size.height*0.292));
	auto bez3 = BezierBy::create(0.3f, bez_conf);

	bez_conf.controlPoint_1 = Vec2(-(size.width*0.268), (size.height*0.0));
	bez_conf.controlPoint_2 = Vec2(-(size.width*0.378), -(size.height*0.185));
	bez_conf.endPosition = Vec2(-(size.width*0.378), -(size.height*0.338));
	auto bez4 = BezierBy::create(0.3f, bez_conf);

	bez_conf.controlPoint_1 = Vec2((size.width*0.0), -(size.height*0.154));
	bez_conf.controlPoint_2 = Vec2((size.width*0.220), -(size.height*0.231));
	bez_conf.endPosition = Vec2((size.width*0.220), -(size.height*0.385));
	auto bez5 = BezierBy::create(0.3f, bez_conf);

	bez_conf.controlPoint_1 = Vec2((size.width*0.0), -(size.height*0.154));
	bez_conf.controlPoint_2 = Vec2(-(size.width*0.093), -(size.height*0.262));
	bez_conf.endPosition = Vec2(-(size.width*0.366), -(size.height*0.262));
	auto bez6 = BezierBy::create(0.3f, bez_conf);

	auto sequence = Sequence::create(bez1, bez2, bez3, bez4, bez5, bez6, nullptr);

	auto repeat = RepeatForever::create(sequence);

	this->runAction(repeat);
}

void Monster::act1(float duration, float y_vel)
{
	this->monster_phys->setVelocity(Vec2(-170, 0));
	auto sequence = Sequence::create(DelayTime::create(duration),
		CallFuncN::create([this,y_vel](Node*)
		{
			this->setPhys_velocity(Vec2(-150, y_vel));
		}),
		nullptr);
	this->runAction(sequence);
}

void Monster::act2(float duration, float y_vel)
{
	auto x_vel = -(duration * 150);
	auto moveby1 = MoveBy::create(duration, Vec2(x_vel,y_vel));
	auto moveby2 = MoveBy::create(duration, Vec2(x_vel, -y_vel));
	auto seuqence = Sequence::create(moveby1, moveby2,nullptr);
	auto repeat = RepeatForever::create(seuqence);
	this->runAction(repeat);
}

void Monster::act3(float duration1, float y_vel, float duration2)
{
	this->monster_phys->setVelocity(Vec2(-170, 0));
	auto sequence = Sequence::create(
		DelayTime::create(duration1),
		CallFuncN::create([this, y_vel](Node*)
		{
			this->setPhys_velocity(Vec2(0, y_vel));
		}),
		DelayTime::create(duration2),
		CallFuncN::create([this, y_vel](Node*)
		{
			this->setPhys_velocity(Vec2(-300, 0));
		}), nullptr);
	this->runAction(sequence);
}

void Monster::act4()
{
	auto moveby1 = MoveBy::create(3.0f, Vec2(-400, 400));
	auto moveby2 = MoveBy::create(3.0f, Vec2(-400, -300));
	auto sequence = Sequence::create(
		moveby1, moveby2,
		CallFuncN::create([this](Node*)
		{
			this->setPhys_velocity(Vec2(150,-150));
		}),nullptr);
	this->runAction(sequence);
}

void Monster::act5(cocos2d::Size size,float duration)
{
	auto width = size.width;
	auto height = size.height;
	ccBezierConfig bez_conf;

	bez_conf.controlPoint_1 = Vec2((0.0f*width), -(0.167*height));
	bez_conf.controlPoint_2 = Vec2((0.714f*width), -(0.333*height));
	bez_conf.endPosition = Vec2((1.0f*width), -(0.5*height));
	auto bez1 = BezierBy::create(duration, bez_conf);

	bez_conf.controlPoint_1 = Vec2((0.0f*width), -(0.167*height));
	bez_conf.controlPoint_2 = Vec2(-(0.714f*width), -(0.333*height));
	bez_conf.endPosition = Vec2(-(1.0f*width), -(0.5*height));
	auto bez2 = BezierBy::create(duration, bez_conf);

	auto sequence = Sequence::create(bez1, bez2, nullptr);
	auto repeat = RepeatForever::create(sequence);

	this->runAction(repeat);
}

void Monster::act6(cocos2d::Size size,float duration)
{
	auto width = size.width;
	auto height = size.height;
	ccBezierConfig bez_conf;

	bez_conf.controlPoint_1 = Vec2((-0.25f*width), (0.0f*height));
	bez_conf.controlPoint_2 = Vec2((-0.25f*width), (1.0f*height));
	bez_conf.endPosition = Vec2((-0.5f*width), (1.0f*height));
	auto bez1 = BezierBy::create(duration/2, bez_conf);

	bez_conf.controlPoint_1 = Vec2((-0.25f*width), (0.0f*height));
	bez_conf.controlPoint_2 = Vec2((-0.25f*width), (-1.0f*height));
	bez_conf.endPosition = Vec2((-0.5f*width), (-1.0f*height));
	auto bez2 = BezierBy::create(duration/2, bez_conf);

	auto sequence = Sequence::create(bez1, bez2, nullptr);
	auto repeat = RepeatForever::create(sequence);

	this->runAction(repeat);
}

void Monster::act7()
{
	auto moveby1 = MoveBy::create(1.0f,Vec2(0,150));
	auto moveby2 = MoveBy::create(1.0f, Vec2(-200, 150));
	auto moveby3 = MoveBy::create(1.0f, Vec2(-200, -150));
	auto moveby4 = MoveBy::create(1.0f, Vec2(0, -150));
	auto moveby5 = MoveBy::create(1.0f, Vec2(0, -150));
	auto moveby6 = MoveBy::create(1.0f, Vec2(200, -150));
	auto moveby7 = MoveBy::create(1.0f, Vec2(200, 150));
	auto moveby8 = MoveBy::create(1.0f, Vec2(0, 150));

	auto sequence = Sequence::create(
		moveby1,
		moveby2,
		moveby3,
		moveby4,
		moveby5,
		moveby6,
		moveby7,
		moveby8,
		nullptr
	);

	auto repeat = RepeatForever::create(sequence);
	this->runAction(repeat);
}

std::vector<MonsterBullet*> Monster::monster_fire0()
{
	std::vector<MonsterBullet*> temp_vec;
	Vec2 position = this->getPosition();

	//Define circles.
	for (int i = 0; i < 8; i++)
	{
		MonsterBullet* monster_bullet = MonsterBullet::create();
		monster_bullet->bullet_init();
		monster_bullet->setPosition(position);
		switch (i)
		{
			case 0:
			{
				monster_bullet->set_up(Vec2(-150, 0));
				break;
			}
			case 1:
			{
				monster_bullet->set_up(Vec2(-100, -100));
				break;
			}
			case 2:
			{
				monster_bullet->set_up(Vec2(0, -150));
				break;
			}
			case 3:
			{
				monster_bullet->set_up(Vec2(100, -100));
				break;
			}
			case 4:
			{
				monster_bullet->set_up(Vec2(150, 0));
				break;
			}
			case 5:
			{
				monster_bullet->set_up(Vec2(100, 100));
				break;
			}
			case 6:
			{
				monster_bullet->set_up(Vec2(0, 150));
				break;
			}
			case 7:
			{
				monster_bullet->set_up(Vec2(-100, 100));
				break;
			}
		}
		temp_vec.push_back(monster_bullet);
	}

	return temp_vec;
}

MonsterBullet* Monster::monster_fire1(cocos2d::Vec2 player_vec)
{
	auto pos_x = this->getPosition().x;
	auto pos_y = this->getPosition().y;
	float vel_xx = -(this->getPosition().x - player_vec.x);	//absolute velocity;
	float vel_yy = -(this->getPosition().y - player_vec.y);
	float vel_ratio = vel_yy / vel_xx;
	float angle = atan(vel_ratio);
	MonsterBullet* monster_bullet = MonsterBullet::create();
	monster_bullet->bullet_init();
	monster_bullet->setPosition(Vec2(pos_x, pos_y));
	float vel_x = cos(angle)*150;
	float vel_y = sin(angle)*150;
	if (vel_xx < 0)
	{
		vel_x = -(abs(vel_x));
	}
	else if (vel_xx > 0)
	{
		vel_x = abs(vel_x);
	}
	if (vel_yy < 0)
	{
		vel_y = -(abs(vel_y));
	}
	else if (vel_yy > 0)
	{
		vel_y = abs(vel_y);
	}
	monster_bullet->set_up(Vec2(vel_x, vel_y));
	return monster_bullet;
}

MonsterBullet* Monster::monster_fire2(float y_vel)
{
	MonsterBullet* monster_bullet = MonsterBullet::create();
	monster_bullet->bullet_init();
	monster_bullet->setPosition(Vec2(this->getPosition().x, this->getPosition().y));
	monster_bullet->set_up(Vec2(-150, y_vel));
	return monster_bullet;
}

std::vector<MonsterBullet*> Monster::monster_fire3(Size move_size)
{
	std::vector<MonsterBullet*> bullets;
	Vec2 position = this->getPosition();

	//5 movements.
	for (int i = 0; i < 5; i++)
	{
		MonsterBullet* bullet = MonsterBullet::create();
		bullet->bullet_init();
		bullet->setPosition(position);

		switch (i)
		{
		case 0:
		{
			bullet->set_up(Vec2(-150, 300));
			break;
		}
		case 1:
		{
			bullet->set_up(Vec2(-150, 150));
			break;
		}
		case 2:
		{
			bullet->set_up(Vec2(-150, -150));
			break;
		}
		case 3:
		{
			bullet->set_up(Vec2(-150, -300));
			break;
		}
		case 4:
		{
			ccBezierConfig bez_conf;

			bez_conf.controlPoint_1 = Vec2((-0.307)*(move_size.width), (0.0)*move_size.height);
			bez_conf.controlPoint_2 = Vec2((-0.739)*(move_size.width), (-0.227)*move_size.height);
			bez_conf.endPosition = Vec2((-0.739)*(move_size.width), (-0.604)*move_size.height);
			auto bez1 = BezierBy::create(0.2f, bez_conf);

			bez_conf.controlPoint_1 = Vec2((0.0)*(move_size.width), (-0.226)*move_size.height);
			bez_conf.controlPoint_2 = Vec2((0.102)*(move_size.width), (-0.396)*move_size.height);
			bez_conf.endPosition = Vec2((0.193)*(move_size.width), (-0.396)*move_size.height);
			auto bez2 = BezierBy::create(0.2f, bez_conf);

			bez_conf.controlPoint_1 = Vec2((0.125)*(move_size.width), (0.0)*move_size.height);
			bez_conf.controlPoint_2 = Vec2((0.205)*(move_size.width), (0.132)*move_size.height);
			bez_conf.endPosition = Vec2((0.205)*(move_size.width), (0.396)*move_size.height);
			auto bez3 = BezierBy::create(0.2f, bez_conf);

			bez_conf.controlPoint_1 = Vec2((0.0)*(move_size.width), (0.340)*move_size.height);
			bez_conf.controlPoint_2 = Vec2((-0.364)*(move_size.width), (0.604)*move_size.height);
			bez_conf.endPosition = Vec2((-0.659)*(move_size.width), (0.604)*move_size.height);
			auto bez4 = BezierBy::create(0.2f, bez_conf);

			bullet->runAction(RepeatForever::create(Sequence::create(bez1, bez2, bez3, bez4, nullptr)));
		}
		}

		bullets.push_back(bullet);
	}
	return bullets;
}

void Monster::setMonster_phys(cocos2d::PhysicsBody* physicsBody)
{
	this->monster_phys = physicsBody;
}

cocos2d::PhysicsBody * Monster::getMonster_phys()
{
	return this->monster_phys;
}