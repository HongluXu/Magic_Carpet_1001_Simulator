#ifndef __CREDIT_SCENE_H__
#define __CREDIT_SCENE_H__

#include "cocos2d.h"

#include "CreditLayer.h"

#define CREDIT_ROLL_UP_TAG 10
#define CREDIT_ROLL_DOWN_TAG 11
#define UP_ARR_FILE_NAME "resources/up_arr.png"
#define DOWN_ARR_FILE_NAME "resources/down_arr.png"

class CreditScene :public cocos2d::Layer
{
public:

	static cocos2d::Scene* createScene();

	/// <summary>
	/// Init scene.
	/// </summary>
	/// <returns></returns>
	virtual bool init();

	CREATE_FUNC(CreditScene);

	//Key press handles.
	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

	void update(float);

private:

	CreditLayer* credit_layer;

	//Scroll page settings.
	bool up_bondary = false;
	bool down_bondary = false;
	float up_b_value;
	float down_b_value;

	cocos2d::Sprite* up_arr;
	cocos2d::Sprite* down_arr;

};



#endif