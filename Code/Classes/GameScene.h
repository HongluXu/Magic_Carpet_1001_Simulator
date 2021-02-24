#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"

#include "GameBackgroundLayer.h"
#include "CharacterLayer.h"
#include "LabelLayer.h"

#define STAGE1_BGM_FILE_NAME "resources/sound/mp3/stage1.mp3"
#define SCORE_UP 100

class GameScene:public cocos2d::Layer
{
public:

	static cocos2d::Scene* createScene();

	/// <summary>
	/// Init
	/// </summary>
	/// <returns></returns>
	virtual bool init();

	// implement the "static create()" method manually
	CREATE_FUNC(GameScene);

	void update(float);

private:

	GameBackgroundLayer* background_layer;
	CharacterLayer* character_layer;
	LabelLayer* label_layer;

	bool bg_moving = true;

	int p_life = 0;
	int score = 0;

};





#endif // !__GAME_SCENE_H__
