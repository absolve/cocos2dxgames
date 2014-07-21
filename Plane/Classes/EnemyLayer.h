#ifndef __ENEMY_LAYER_H__
#define __ENEMY_LAYER_H__

#include "cocos2d.h"



class EnemyLayer:public  cocos2d::Layer
{
public:
	
	virtual   bool  init();
	CREATE_FUNC(EnemyLayer);

	//!创建各种类型的敌人
	void     createEnemy();
	
	//!增加开始时间
	void     setTime(float t){startTime=t;}
	float    getTime(){return startTime;}
	void	 addTime(float t) {startTime+=t;}
	bool     onTime() { if(startTime>delayTime) return true;
							else return false;}

public:
	//!各种类型的敌人容器
	cocos2d::Vector<cocos2d::Sprite*> enemyNum;
	static   std::string enemyStyle[3];
	//!已经死亡的敌机容器集
	cocos2d::Vector<cocos2d::Sprite*>deadEnemy;

private:

	//!时间延迟
	float    delayTime;
	//!开始时间
	float    startTime;

};

#endif