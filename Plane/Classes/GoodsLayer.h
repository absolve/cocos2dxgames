#ifndef  __GOODS_LAYER_H__
#define  __GOODS_LAYER_H__

#include "cocos2d.h"

class GoodsLayer:public  cocos2d::Layer
{
public:
	
	virtual    bool    init();

	CREATE_FUNC(GoodsLayer);
	bool      touch(cocos2d::Touch *touch,cocos2d::Event * event);


	//!Õ¨µ¯¾«Áé
	cocos2d::Sprite*   bomb1;
	cocos2d::Sprite*   getBomb(){return  bomb1;}
	//!Õ¨µ¯ÊÇ·ñÆô¶¯
	bool      explosion;
	bool      getIsEexplosion(){return  explosion;}
	void	  setExplosion(bool  e){explosion=e;}

};

#endif