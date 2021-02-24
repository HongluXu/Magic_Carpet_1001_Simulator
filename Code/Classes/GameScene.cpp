#include "GameScene.h"

#include "VictoryScene.h"

#include "AudioEngine.h"

USING_NS_CC;

cocos2d::Scene * GameScene::createScene()
{
	auto scene = Scene::createWithPhysics();

	auto layer = GameScene::create();

	scene->addChild(layer);

	return scene;
}

bool GameScene::init()
{
	
	experimental::AudioEngine::play2d(STAGE1_BGM_FILE_NAME, true);

	this->background_layer = GameBackgroundLayer::create();
	this->addChild(background_layer,-5);

	this->character_layer = CharacterLayer::create();
	this->addChild(character_layer, 5);

	this->label_layer = LabelLayer::create();
	this->addChild(label_layer, 10);

	this->scheduleUpdate();

	return true;
}

void GameScene::update(float)
{
	//control the bg;
	if (this->bg_moving == true && this->character_layer->getBSF())
	{
		this->background_layer->stop_move();
		this->bg_moving = false;
	}

	//set player life label;
	int plife_temp = this->character_layer->get_plife();
	if (plife_temp != this->p_life)
	{
		this->p_life = plife_temp;
		this->label_layer->set_plife(this->p_life);
	}

	//set the score label;
	if (this->character_layer->get_scoreup())
	{
		this->score += SCORE_UP;
		this->label_layer->set_score(this->score);
		this->character_layer->set_scoreup(false);
	}

	//win the game;
	if (this->character_layer->get_win_flag())
	{
		auto victory_scene = VictoryScene::createScene(this->score);
		auto dir = Director::getInstance();
		dir->replaceScene(victory_scene);
	}

}
