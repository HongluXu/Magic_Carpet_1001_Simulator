#ifndef __GAME_OVER_SCENE_H__
#define __GAME_OVER_SCENE_H__

#include "cocos2d.h"

class GameOverScene :public cocos2d::Layer
{
public:

	static cocos2d::Scene* createScene();

	/// <summary>
	/// Init.
	/// </summary>
	/// <returns></returns>
	virtual bool init();

	// implement the "static create()" method manually
	CREATE_FUNC(GameOverScene);

	/// <summary>
	/// Key handle, mostly retart the game.
	/// </summary>
	/// <param name="keyCode"></param>
	/// <param name="event"></param>
	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

private:

};





#endif // !__GAME_SCENE_H__
