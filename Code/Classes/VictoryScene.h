#ifndef __VICTORY_SCENE_H__
#define __VICTORY_SCENE_H__

#include "cocos2d.h"

class VictoryScene :public cocos2d::Layer
{
public:

	static cocos2d::Scene* createScene(int score);

	virtual bool init();

	CREATE_FUNC(VictoryScene);

	/// <summary>
	/// Key handler.
	/// </summary>
	/// <param name="keyCode"></param>
	/// <param name="event"></param>
	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

	void set_score(int score);

private:

	int score;

	cocos2d::Label* score_label;

};





#endif // !__GAME_SCENE_H__
