#ifndef __EDGE_BOX_IN_H__
#define __EDGE_BOX_IN_H__

#include "cocos2d.h"

//Init variables.
#define EDGE_BOX_IN_TAG 3
#define EDGE_BOX_IN_WIDTH 1.0f
#define EDGE_BOX_IN_PHYS_TAG 4
#define EDGE_BOX_IN_PHYS_CATEGORY 0xAAAAAAAA
#define EDGE_BOX_IN_PHYS_COLLISION 0xAAAAAAAA
#define EDGE_BOX_IN_PHYS_CONTACTTEST 0xF0000002

class EdgeBoxIn :public cocos2d::Node
{
public:

	static EdgeBoxIn* create();
	/// <summary>
	/// Init the edge box.
	/// </summary>
	/// <param name="">Size</param>
	/// <param name="">Material</param>
	void edge_box_in_init(cocos2d::Size, cocos2d::PhysicsMaterial);	//Do not set the size; need to set the size first;

	void setEdge_in_phys(cocos2d::PhysicsBody*);
	cocos2d::PhysicsBody* getEdge_in_phys();
	void setEdge_in_phys_size(cocos2d::Size);
	cocos2d::Size getEdge_in_phys_size();
	void setEdge_in_phys_tag(int);
	void setEdge_category(int);
	void setEdge_collision(int);
	void setEdge_contacttest(int);


private:

	cocos2d::PhysicsBody* edge_in_phys;
	cocos2d::Size edge_in_phys_size;

};




#endif // !__EDGE_BOX_OUT_H__
