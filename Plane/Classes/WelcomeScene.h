#ifndef __WELCOME_SCENE_H__
#define __WELCOME_SCENE_H__

#include "cocos2d.h"

class WelcomeScene:public  cocos2d::Layer
{
public:
	
	static cocos2d::Scene* createScene();
	//!初始化函数
	virtual bool  init();
	CREATE_FUNC(WelcomeScene);
	//!定时器函数
	void    update(float  dt);
	//!菜单回调函数
	void    nextSceneCallBack(cocos2d::Ref* pSender);
	//!退出按钮回调事件
	void    closeCallBack(cocos2d::Ref* pSender);



};

#endif