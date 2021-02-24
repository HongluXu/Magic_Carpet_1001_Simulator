#ifndef __MENU_SCENE_H__
#define __MENU_SCENE_H__

#include "cocos2d.h"

#define TITLE_FILE_NAME "resources/title_label_1024_296.png"
#define MAN_FILE_NAME "resources/menu_pic_408.png"
#define START_L_POSITION cocos2d::Vec2(700,300)
#define CREDIT_L_POSITION cocos2d::Vec2(700,200)
#define ARROW_FILE_NAME "resources/arrows.png"
#define ARROW_X_POSITION 650
#define BG_MUSIC_FILE_NAME "resources/sound/mp3/menu_bgm.mp3"
#define ARROW_SE_FILE_NAME	"resources/sound/mp3/arrow_se.mp3"

class MenuScene:public cocos2d::Layer
{
public:

	static cocos2d::Scene* createScene();

	virtual bool init();

	// implement the "static create()" method manually
	CREATE_FUNC(MenuScene);

	/// <summary>
	///  Key listener.
	/// </summary>
	/// <param name="keyCode"></param>
	/// <param name="event"></param>
	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

	/// <summary>
	/// Mouse move detection.
	/// </summary>
	/// <param name="event"></param>
	void onMouseMove(cocos2d::Event *event);
	/// <summary>
	/// Debug mouse.
	/// </summary>
	void mouse_dis_init();
private:

	int menu_select = 0;

	cocos2d::Sprite* arrow_sprite;

	cocos2d::Label* mouse_display;
	cocos2d::Label* x_posi;
	cocos2d::Label* y_posi;

	int menu_bgm_id;

};



#endif