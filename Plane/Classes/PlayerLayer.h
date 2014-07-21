#ifndef   __PLAYER_LAYER_H__
#define   __PLAYER_LAYER_H__

#include "cocos2d.h"

//!玩家层,玩家可控制的飞机

enum  bulletStyle
{
	_bullet1=1,
	_bullet2
};

class PlayerLayer:public  cocos2d::Layer
{
public:
	
	virtual  bool   init();

	CREATE_FUNC(PlayerLayer);
	//!获取玩家精灵
	cocos2d::Node*   getPlayer();
	//!子弹的集合
	cocos2d::Vector<cocos2d::Sprite*> bullets;
	//!添加子弹
	void     shoot();
	//!子弹类型
	bulletStyle   bstyle;
	void		  setBulletStyle(bulletStyle bs){bstyle=bs;}
	//!更新时间
	void     update(float);
	//!设置玩家飞机位置
	void	 setPlanePos(float,float);
	//!获取飞机的矩形
	cocos2d::Rect     getPlaneRect();

private:
	float	time;
	float   delayTime;

};

#endif