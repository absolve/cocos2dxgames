#ifndef  __WELCOME_SCENCE_H__
#define  __WELCOME_SCENCE_H__

#include "cocos2d.h"

class WelcomeScence:public cocos2d::Layer
{
public:
	

	static    cocos2d::Scene*   createScene();

	virtual   bool   init();
	CREATE_FUNC(WelcomeScence);
	//!开始按钮回调函数
	void      startButtonCallBack(cocos2d::Ref* pSender);
	//!场景切换按钮
	void      selectButtonCallBack(cocos2d::Ref* pSender);
	//!关闭按钮
	void menuCloseCallback(cocos2d::Ref* pSender);

};

#endif