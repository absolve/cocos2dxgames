#ifndef __PANE_LAYER_H__
#define __PANE_LAYER_H__

#include "cocos2d.h"

class PaneLayer:public  cocos2d::Layer
{
public:
	
	virtual   bool    init();
	CREATE_FUNC(PaneLayer);
	//!暂停按钮回调函数
	void    pauseButtonCallBack(cocos2d::Ref* pSender);
	//!截屏按钮回调函数
	void    cameraButtonCallBack(cocos2d::Ref* pSender);
	//!音乐按钮回调函数
	void    musicButtonCallBack(cocos2d::Ref* pSender);
	//!炮台等级减少回调函数
	void    cannondecCallBack(cocos2d::Ref* pSender);
	//!炮台等级增加回调函数
	void    cannonaddCallBack(cocos2d::Ref* pSender);


};

#endif