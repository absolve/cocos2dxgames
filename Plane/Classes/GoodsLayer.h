#ifndef  __GOODS_LAYER_H__
#define  __GOODS_LAYER_H__

#include "cocos2d.h"

class GoodsLayer:public  cocos2d::Layer
{
public:
	
	virtual    bool    init();
	CREATE_FUNC(GoodsLayer);

public:

	//!炸弹是否启动
	bool      explosion;
	bool      getIsEexplosion(){return  explosion;}
	void	  setExplosion(bool  e){explosion=e;}
	//!爆炸回调函数
	void      explosionCallBack(cocos2d::Ref* pSender);
	//!创建道具
	void      createBulletOrBmob();
	//!更新函数
	//void      updateTime(float);
	//!更改子弹类型
	void      changeBulletStyle();
	//!获取道具类型
	//int       getFlag()  {return flag;}
	//!获取子弹精灵
	//cocos2d::Sprite*   getDBullet() {return  dBullet;}
	////!获取炸弹精灵
	//cocos2d::Sprite*   getBomb() {return bomb;}
	//!精灵动作结束的回调函数
	//void      CallBack();

private:

	//!子弹精灵
	//cocos2d::Sprite*   dBullet;
	////!炸弹精灵
	//cocos2d::Sprite*   bomb;
	//!每个道具出现的时间
	//float     time;
	//float     delayTime;
	////!道具种类0代表炸弹1代表子弹
	//int       flag;


};

#endif