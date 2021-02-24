#ifndef __BULLET_H__
#define __BULLET_H__

#include "cocos2d.h"

#define BULLET_PHYS_COLLISION 0x00000000

class Bullet:public cocos2d::Sprite
{
public:

	
	/// <summary>
	/// Init the bullet.
	/// </summary>
	virtual void bullet_init() {}
	/// <summary>
	/// Start the bullet.
	/// </summary>
	/// <param name="">Init velocity</param>
	virtual void set_up(cocos2d::Vec2);

	void setBullet_phys(cocos2d::PhysicsBody*);
	cocos2d::PhysicsBody* getBullet_phys();
	void setBullet_physize(cocos2d::Size);
	cocos2d::Size getBullet_physize(); 
	void setPhys_dynamic(bool);
	void setPhys_gravity(bool);
	void setPhys_tag(int);
	int getPhys_tag();
	void setPhys_category(int);
	/// <summary>
	/// Set physics collision mask.
	/// </summary>
	/// <param name="">Mask</param>
	void setPhys_collision(int);
	void setPhys_contacttest(int);
	void setPhys_rotation(bool);

	/// <summary>
	/// Set var:deleted if not.
	/// </summary>
	/// <returns></returns>
	bool delete_judge();

protected:

	cocos2d::PhysicsBody* bullet_phys;
	cocos2d::Size bullet_physize;	//colliding size.

	bool deleted = false;

};





#endif // !__BULLET_H__
