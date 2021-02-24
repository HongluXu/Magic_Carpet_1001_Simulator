#ifndef __MONSTER_H__
#define __MONSTER_H__

#include <vector>
#include <math.h>

#include "cocos2d.h"

#include "MonsterBullet.h"

//Monster vars.
#define MONSTER_PHYS_CATEGORY 0x00000004
#define MONSTER_PHYS_COLLISION 0x00000000
#define MONSTER_PHYS_CONTACTTEST 0x00000008
#define M_CLOUD_FILE_NAME "cloud1.png"
#define MONSTER_ACT_TAG 15
#define MONSTER_PHYS_SIZE_CUT 0

class Monster :public cocos2d::Sprite
{

public:

	/// <summary>
	/// Monster state.
	/// </summary>
	enum MonStateEnum
	{
		normal,
		dead
	};

	virtual void monster_init() {}

	void setMonster_phys(cocos2d::PhysicsBody*);
	cocos2d::PhysicsBody* getMonster_phys();
	void setMonster_physize(cocos2d::Size);
	cocos2d::Size getMonster_physize();
	void setMonster_phys_tag(int);
	int getMonster_phys_tag();
	void setMonster_phys_category(int);
	int getMonster_phys_category();
	void setMonster_phys_collision(int);
	void setMonster_phys_contacttest(int);
	int getMonster_phys_contacttest();
	void setPhys_dynamic(bool);
	void setPhys_gravity(bool);
	void setPhys_rotation(bool);
	void setPhys_velocity(cocos2d::Vec2);	

	/// <summary>
	/// Called when hitted.
	/// </summary>
	/// <returns></returns>
	bool hited();
	
	void act0(cocos2d::Size);	//Omega movement (size);
	void act1(float, float);	//left,leftup movement (duration, y velocity);
	void act2(float, float);	//up,down movement (duration, y velocity);
	void act3(float, float, float);	//left,up,left movement (dur1, y velocity, dur2);
	void act4();	//superman act1 ();
	void act5(cocos2d::Size,float);	//drift down movement (size, duration);
	void act6(cocos2d::Size size,float duration);	//wave movement (size, duration);
	void act7();	//boss move;

	std::vector<MonsterBullet*> monster_fire0();	//circle fire
	MonsterBullet* monster_fire1(cocos2d::Vec2);	//fire to player;
	MonsterBullet* monster_fire2(float);	//horizontal fire;
	std::vector<MonsterBullet*> monster_fire3(cocos2d::Size move_size);	//boss fire


	//void setA(int);
	
protected:

	cocos2d::PhysicsBody* monster_phys;
	cocos2d::Size monster_physize;
	int health;
	MonStateEnum state;

	//int a;


};



#endif // !__MONSTER_H__
