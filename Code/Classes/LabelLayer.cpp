#include "LabelLayer.h"

#include <string>

USING_NS_CC;

bool LabelLayer::init()
{

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	float center_x = visibleSize.width / 2 + origin.x;
	float center_y = visibleSize.height / 2 + origin.y;
	Vec2 center_point = Vec2(center_x, center_x);

	this->p_life = 0;
	this->score = 0;

	//Score text.
	this->score_label = Label::create(std::to_string(this->score), "fonts/Marker Felt.ttf", 24);
	score_label->setPosition(Vec2(100,100));
	this->addChild(score_label);

	//Player life text.
	this->plife_label = Label::create(std::to_string(this->p_life), "fonts/Marker Felt.ttf", 24);
	plife_label->setPosition(Vec2(200, 100));
	this->addChild(plife_label);


	return true;
}

void LabelLayer::set_score(int score)
{
	this->score = score;
	this->score_label->setString(std::to_string(this->score));
}

int LabelLayer::get_score()
{
	return this->score;
}

void LabelLayer::set_plife(int life)
{
	this->p_life = life;
	this->plife_label->setString(std::to_string(this->p_life));
}

int LabelLayer::get_plife()
{
	return this->p_life;
}

