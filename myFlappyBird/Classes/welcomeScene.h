#ifndef __WELCOME_SCENE_H__
#define __WELCOME_SCENE_H__

#include "cocos2d.h"
//!游戏欢迎界面

class welcomeScene: public cocos2d::Layer
{
public:	
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(welcomeScene);
public:
	void menuCloseCallback(cocos2d::Ref* pSender);
	//!开始游戏按钮
	void gameStartCallBack(cocos2d::Ref* pSender);
	//!设置游戏属性
	void gameOptionCallBack(cocos2d::Ref* pSender);
	//!点击事件
	bool   touchEvent(cocos2d::Touch *touch,cocos2d::Event * event);
};

#endif // !1