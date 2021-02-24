#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "cocos2d.h"

#include "PlayerBullet.h"

//Resources and vars
#define PLAYER_FILENAME "/resources/player1.png"
#define PLAYER_SPRITE_TAG 10
#define PLAYER_PHYBODY_TAG 15
#define PLAYER_WIDTH 100
#define PLAYER_HEIGHT 100
#define PLAYER_CATEGORY 0xAAAAAAAA
#define PLAYER_COLLISION 0x0000000A
#define PLAYER_CONTACTTEST 0xFFFFFFFF
#define PLAYER_MOVE_SPEED 400
#define PLAYER_START_Y 500
#define PLAYER_INMUME_TIME 4.0f
#define PLAYER_LIFE 5
#define PLAYER_ANI_FILENAME "player1.png"
#define PLAYER_ANI_FILENAME2 "player2.png"
#define PLAYER_ANI_FILENAME3 "player3.png"
#define PLAYER_ANI_TAG 5
#define PLAYER_D_ANI_FILENAME "pd1.png"
#define PLAYER_D_ANI_FILENAME2 "pd2.png"
#define PLAYER_D_ANI_TAG 6
#define PLAYER_PHYS_SIZE_CUT 40
#define PLAYER_FIRE_SPEED 600

class Player:public cocos2d::Sprite
{
public:

	/// <summary>
	/// Player states.
	/// </summary>
	enum PlayerStateEnum
	{
		start_move,
		immune,
		normal,
		dead
	};

	static Player* create(const char*);

	static Player* create();

	void player_init(cocos2d::Size win_size);	//Only lack of setPosition, need to set later;
	void start();	//start the player from the edge;
	bool hited();	//Call when hitted.
	void d_animation();	//Dead animation.

	void setPlayer_phybody_tag(int);
	int getPlayer_phybody_tag();
	void setPlayer_physize(cocos2d::Size);
	cocos2d::Size getPlayer_physize();
	cocos2d::PhysicsBody* getPlayer_phys();
	void setPlayer_category(int);
	int getPlayer_category();
	void setPlayer_contacttest(int);
	int getPlayer_contacttest();
	void setPlayer_collision(int);
	PlayerStateEnum getState();
	void setState(PlayerStateEnum);

	//Player movements.
	PlayerBullet* player_fire();
	void move_up();
	void move_down();
	void move_left();
	void move_right();
	void stop_up();
	void stop_down();
	void stop_left();
	void stop_right();

	int get_plife();

private:
	cocos2d::Size player_physize;
	cocos2d::PhysicsBody* player_phys;
	int health;	//Health per life.
	int life;	//Total lives.
	PlayerStateEnum state;
	cocos2d::Size win_size;
};





#endif // !__PLAYER_H__
