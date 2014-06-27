#ifndef  __MENU_LAYER_H__
#define  __MENU_LAYER_H__


#include "cocos2d.h"

class MenuLayer:public cocos2d::Layer
{
public:
	
	virtual   bool    init();
	CREATE_FUNC(MenuLayer);

	void menuContinueCallback(cocos2d::Ref* pSender);
	void menuRestartCallBack(cocos2d::Ref* pSender);
	void menuExitCallBack(cocos2d::Ref* pSender);


};

#endif