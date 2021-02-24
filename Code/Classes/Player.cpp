#include "Player.h"

USING_NS_CC;

Player* Player::create(const char* play_file_name)
{
	Player* player_sprite = new Player();

	if (player_sprite && player_sprite->initWithFile(play_file_name))
	{
		player_sprite->autorelease(); 
		return player_sprite;
	}

	CC_SAFE_DELETE(player_sprite);
	return nullptr;
}

Player * Player::create()
{
	Player* player_sprite = new Player();

	if (player_sprite && player_sprite->initWithFile(PLAYER_FILENAME))
	{
		player_sprite->autorelease();
		return player_sprite;
	}

	CC_SAFE_DELETE(player_sprite);
	return nullptr;
}

void Player::player_init(Size win_size)
{
	this->win_size = win_size;

	this->setTag(PLAYER_SPRITE_TAG);
	this->health = 1;
	this->life = PLAYER_LIFE;
	
	this->player_physize = cocos2d::Size(PLAYER_WIDTH- PLAYER_PHYS_SIZE_CUT, PLAYER_HEIGHT- PLAYER_PHYS_SIZE_CUT);
	this->player_phys = PhysicsBody::createBox(player_physize, PhysicsMaterial(0.0f, 0.0f, 0.0f));
	this->player_phys->setDynamic(true);
	this->player_phys->setGravityEnable(false);
	this->player_phys->setRotationEnable(false);
	this->player_phys->setCategoryBitmask(PLAYER_CATEGORY);
	this->player_phys->setCollisionBitmask(0x0);
	this->player_phys->setContactTestBitmask(0x0);
	this->player_phys->setTag(PLAYER_PHYBODY_TAG);
	this->setPhysicsBody(this->player_phys);

	//finishes everything and start the player;
	this->Player::PlayerStateEnum::start_move;
	this->start();

}

void Player::start()
{
	if (this->state != Player::PlayerStateEnum::start_move)
	{
		return;
	}

	this->stopActionByTag(PLAYER_D_ANI_TAG);

	//Animation.
	Vector<SpriteFrame*> player_animation;
	player_animation.reserve(3);
	auto instance = SpriteFrameCache::getInstance();
	player_animation.pushBack(instance->getSpriteFrameByName(PLAYER_ANI_FILENAME));
	player_animation.pushBack(instance->getSpriteFrameByName(PLAYER_ANI_FILENAME2));
	player_animation.pushBack(instance->getSpriteFrameByName(PLAYER_ANI_FILENAME3));
	Animation* animation = Animation::createWithSpriteFrames(player_animation, 0.1f);
	auto main_animate = Animate::create(animation);
	auto animate_loop = RepeatForever::create(main_animate);
	animate_loop->setTag(PLAYER_ANI_TAG);
	this->runAction(animate_loop);

	//Init vars.
	this->health = 1;
	this->player_phys->setCollisionBitmask(0x0);
	this->player_phys->setContactTestBitmask(0x0);
	this->setPosition(Vec2(-100, PLAYER_START_Y));
	auto moveto = MoveTo::create(2.0f, Vec2((this->win_size.width)/4, PLAYER_START_Y));

	//Immune for some time.
	this->runAction(Sequence::create(
		moveto,
		CallFuncN::create(
			[this](Node*)
			{
				this->setPlayer_collision(PLAYER_COLLISION);
				this->setState(Player::PlayerStateEnum::immune);
			}
		),
		DelayTime::create(PLAYER_INMUME_TIME-2.0f),
		CallFuncN::create(
			[this](Node*)
			{
				if (Player::PlayerStateEnum::immune != this->getState())
				{
					return;
				}
				this->player_phys->setContactTestBitmask(PLAYER_CONTACTTEST);
				this->state = PlayerStateEnum::normal;
			}
		),
		nullptr
	));
}

void Player::setPlayer_phybody_tag(int tag)
{
	//this->player_phybody_tag = tag;
	this->player_phys->setTag(tag);
}

int Player::getPlayer_phybody_tag()
{
	return this->player_phys->getTag();
}

void Player::setPlayer_physize(Size size)
{
	this->player_physize = size;
	//this->player_phys->setSize

}

Size Player::getPlayer_physize()
{
	return this->player_physize;
}

PhysicsBody * Player::getPlayer_phys()
{
	return this->player_phys;
}

void Player::setPlayer_category(int category)
{
	//this->player_category = category;
	this->player_phys->setCategoryBitmask(category);
}

int Player::getPlayer_category()
{
	return this->player_phys->getCategoryBitmask();
}

void Player::setPlayer_contacttest(int contacttest)
{
	//this->player_contacttest = contacttest;
	this->player_phys->setContactTestBitmask(contacttest);
}

int Player::getPlayer_contacttest()
{
	return this->player_phys->getContactTestBitmask();
}

void Player::setPlayer_collision(int collision)
{
	this->player_phys->setCollisionBitmask(collision);
}

Player::PlayerStateEnum Player::getState()
{
	return state;
}

void Player::setState(PlayerStateEnum player_enum)
{
	this->state = player_enum;
}

bool Player::hited()
{
	//Only if normal state.
	if (Player::PlayerStateEnum::normal == this->state)
	{
		this->health--;
		if (this->health <= 0)
		{
			this->life--;
			//Out of life.
			if (this->life <= 0)
			{
				return true;
			}
			//Restart.
			else
			{
				this->setPlayer_collision(0x0);
				this->setPlayer_contacttest(0x0);
				this->state = PlayerStateEnum::dead;
				this->d_animation();
			}
		}
	}
	return false;
}

void Player::d_animation()
{
	if (PlayerStateEnum::dead != this->state)
	{
		return;
	}

	//Stop other animations.
	this->stopActionByTag(PLAYER_ANI_TAG);

	Vector<SpriteFrame*> player_d_animation;
	player_d_animation.reserve(2);
	auto instance = SpriteFrameCache::getInstance();
	player_d_animation.pushBack(instance->getSpriteFrameByName(PLAYER_D_ANI_FILENAME));
	player_d_animation.pushBack(instance->getSpriteFrameByName(PLAYER_D_ANI_FILENAME2));
	Animation* animation = Animation::createWithSpriteFrames(player_d_animation, 0.1f);
	auto main_animate = Animate::create(animation);
	auto d_animate_loop = RepeatForever::create(main_animate);
	d_animate_loop->setTag(PLAYER_D_ANI_TAG);
	this->runAction(d_animate_loop);

	this->player_phys->setVelocity(Vec2(0, 0));
	auto moveby = MoveBy::create(2.0f, Vec2(0, -768));

	//Restart.
	auto sequence = Sequence::create(
		moveby,
		CallFuncN::create(
			[this](Node*)
			{
				this->setState(Player::PlayerStateEnum::start_move);
			}
		),
		CallFunc::create(this, callfunc_selector(Player::start)),
		nullptr
	);
	this->runAction(sequence);

}

PlayerBullet* Player::player_fire()
{
	//Create bullet.
	auto player_bullet = PlayerBullet::create();
	player_bullet->bullet_init();
	player_bullet->setPosition(Vec2(this->getPosition().x, this->getPosition().y));
	player_bullet->set_up(Vec2(PLAYER_FIRE_SPEED,0));

	return player_bullet;
}

void Player::move_up()
{
	if (Player::PlayerStateEnum::normal != this->state && Player::PlayerStateEnum::immune != this->state)
	{
		return;
	}
	float x_vel = this->player_phys->getVelocity().x;
	this->player_phys->setVelocity(Vec2(x_vel, PLAYER_MOVE_SPEED));
}

void Player::move_down()
{
	if (Player::PlayerStateEnum::normal != this->state && Player::PlayerStateEnum::immune != this->state)
	{
		return;
	}
	float x_vel = this->player_phys->getVelocity().x;
	this->player_phys->setVelocity(Vec2(x_vel, -PLAYER_MOVE_SPEED));
}

void Player::move_left()
{
	if (Player::PlayerStateEnum::normal != this->state && Player::PlayerStateEnum::immune != this->state)
	{
		return;
	}
	float y_vel = this->player_phys->getVelocity().y;
	this->player_phys->setVelocity(Vec2(-PLAYER_MOVE_SPEED, y_vel));
}

void Player::move_right()
{
	if (Player::PlayerStateEnum::normal != this->state && Player::PlayerStateEnum::immune != this->state)
	{
		return;
	}
	float y_vel = this->player_phys->getVelocity().y;
	this->player_phys->setVelocity(Vec2(PLAYER_MOVE_SPEED, y_vel));
}

void Player::stop_up()
{
	float x_vel = this->player_phys->getVelocity().x;
	float y_vel = this->player_phys->getVelocity().y;
	if (y_vel > 0)
	{
		this->player_phys->setVelocity(Vec2(x_vel, 0));
	}
}

void Player::stop_down()
{
	float x_vel = this->player_phys->getVelocity().x;
	float y_vel = this->player_phys->getVelocity().y;
	if (y_vel < 0)
	{
		this->player_phys->setVelocity(Vec2(x_vel, 0));
	}
}

void Player::stop_left()
{
	float x_vel = this->player_phys->getVelocity().x;
	float y_vel = this->player_phys->getVelocity().y;
	if (x_vel < 0)
	{
		this->player_phys->setVelocity(Vec2(0, y_vel));
	}
}

void Player::stop_right()
{
	float x_vel = this->player_phys->getVelocity().x;
	float y_vel = this->player_phys->getVelocity().y;
	if (x_vel > 0)
	{
		this->player_phys->setVelocity(Vec2(0, y_vel));
	}
}

int Player::get_plife()
{
	return this->life;
}
