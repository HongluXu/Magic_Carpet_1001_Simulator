#ifndef __LABEL_LAYER_H__
#define __LABEL_LAYER_H__

#include "cocos2d.h"

class LabelLayer :public cocos2d::Layer
{
public:

	virtual bool init();

	CREATE_FUNC(LabelLayer);

	void set_score(int score);
	int get_score();
	void set_plife(int life);
	int get_plife();

private:

	int score;
	int p_life;	//player life.

	cocos2d::Label* score_label;
	cocos2d::Label* plife_label;

};




#endif // __LABEL_LAYER_H__
