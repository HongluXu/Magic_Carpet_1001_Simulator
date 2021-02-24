#ifndef __EDGE_BOX_OUT_H__
#define __EDGE_BOX_OUT_H__

#include "cocos2d.h"

#define EDGE_BOX_OUT_TAG 1
#define EDGE_BOX_OUT_WIDTH 10.0f
#define EDGE_BOX_OUT_PHYS_TAG 2
#define EDGE_BOX_OUT_PHYS_CATEGORY 0xFFFFFFFF
#define EDGE_BOX_OUT_PHYS_COLLISION 0x00000000
#define EDGE_BOX_OUT_PHYS_CONTACTTEST 0xFFFFFFFF

class EdgeBoxOut:public cocos2d::Node
{
public:

	static EdgeBoxOut* create();
	/// <summary>
	/// Init the box
	/// </summary>
	/// <param name="">Size</param>
	/// <param name="">Material</param>
	void edge_box_out_init(cocos2d::Size, cocos2d::PhysicsMaterial);	//Need to set the size first;

	void setEdge_out_phys(cocos2d::PhysicsBody*);
	cocos2d::PhysicsBody* getEdge_out_phys();
	void setEdge_out_phys_size(cocos2d::Size);
	cocos2d::Size getEdge_out_phys_size();
	void setEdge_out_phys_tag(int);
	void setEdge_category(int);
	void setEdge_collision(int);
	void setEdge_contacttest(int);


private:

	cocos2d::PhysicsBody* edge_out_phys;
	cocos2d::Size edge_out_phys_size;

};




#endif // !__EDGE_BOX_OUT_H__
