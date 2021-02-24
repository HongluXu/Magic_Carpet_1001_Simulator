#ifndef __CHARACTER_LAYER_H__
#define __CHARACTER_LAYER_H__

#include "cocos2d.h"

#include "Player.h"
#include "PlayerBullet.h"

//Resources addresses.
#define	MONSTER_MAX_SIZE 100
#define BIRD_PLIST "/resources/bird_sheet.plist"
#define BEE_PLIST "/resources/bee_sheet.plist"
#define ROCKET_PLIST "/resources/rocket_sheet.plist"
#define SUPER_PLIST "/resources/super_sheet.plist"
#define PLAYER_PLIST "/resources/player_sheet.plist"
#define PLAYER_D_PLIST "/resources/pd_sheet.plist"
#define CLOUD_PLIST "/resources/cloud_sheet.plist"
#define PLAYER_SHOOT_SE "resources/sound/mp3/player_shoot_se.mp3"
#define MONSTER_HIT_SE "resources/sound/mp3/monster_hit_se.mp3"


class CharacterLayer :public cocos2d::Layer
{
public:
	/// <summary>
	/// Init the Character Layer.
	/// </summary>
	/// <returns></returns>
	bool init();

	CREATE_FUNC(CharacterLayer);

	//Button functions.
	void onKeyPressed(cocos2d::EventKeyboard::KeyCode, cocos2d::Event*);
	void onKeyReleased(cocos2d::EventKeyboard::KeyCode, cocos2d::Event*);

	//Contact detection.
	bool myContactBegin(cocos2d::PhysicsContact&);
	bool onContactSeparate(cocos2d::PhysicsContact&);

	//Game sequence state machine.
	void monster_refresh();
	
	/// <summary>
	/// Get var:boss_stage_flag.
	/// </summary>
	/// <returns></returns>
	bool getBSF();

	/// <summary>
	/// Get player life.
	/// </summary>
	/// <returns></returns>
	int get_plife();

	void set_scoreup(bool score_up);
	bool get_scoreup();

	bool get_win_flag();

private:
	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;	//Center for calculation

	Player* player;
	bool player_bullet_flag = false;	//One bullete at a time.
	PlayerBullet* player_bullet;

	bool playerx_collision = false;
	bool playery_collision = false;

	int wave = 0;	//state machine wave number.
	float right_ref_x;	//spawn right side reference position.
	float top_ref_y;	//spawn y reference position
	cocos2d::CCDelayTime* next_delay;	//state machine delay time.
	cocos2d::Action* callback;
	cocos2d::CallFuncN* monster_sequence;	//refresh in a row;

	bool boss_stage_flag = false;

	bool score_up = false;

	bool win_flag = false;
	
};



#endif // !__CHARACTER_LAYER_H__
