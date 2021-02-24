#ifndef __GAME_BACKGROUND_LAYER_H__
#define __GAME_BACKGROUND_LAYER_H__

#include "cocos2d.h"

#define BACKGROUND_FILE "/resources/bg_real.png"
#define BACKGROUND_LEFT_OUT 10
#define SCREEN_WIDTH 1024
#define BACKGROUND_FULL_WIDTH 3072
#define BACKGROUND_IN_WIDTH (BACKGROUND_FULL_WIDTH-SCREEN_WIDTH)
#define BACKGROUND_MOVE_DURATION 30.0f
#define BACKGROUND_MOVE_ACT_TAG 10

class GameBackgroundLayer:public cocos2d::Layer
{
public:

	/// <summary>
	/// Init.
	/// </summary>
	/// <returns></returns>
	virtual bool init();

	// implement the "static create()" method manually
	CREATE_FUNC(GameBackgroundLayer);

	/// <summary>
	/// Stop moving the background.
	/// </summary>
	void stop_move();

private:

	cocos2d::Sprite* background;

};




#endif // !__GAME_BACKGROUND_LAYER_H__
