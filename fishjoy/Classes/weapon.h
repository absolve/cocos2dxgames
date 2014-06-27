#ifndef  __WEAPON_H__
#define  __WEAPON_H__

#include "cocos2d.h"
#include <vector>

//!炮台等级
enum  _cannon{
	cannon_1=1,
	cannon_2,
	cannon_3,cannon_4,cannon_5,cannon_6,cannon_7,cannon_8
};
//!炮弹的射程
enum  _range{
	range_1=1,
	range_2,range_3,range_4,range_5,range_6,range_7
};
//!炮弹的命中率
enum  _hit{
	hit_1=10,
	hit_2=15,hit_3=20,hit_4=25,hit_5=30,hit_6=40,
	hit_7=50
};

class   Bullet;

class Weapon:public  cocos2d::Node
{
public:

	//!初始化武器
	virtual bool init(); 

	//!拥有8中不同的炮台
	_cannon   currCannon;
	//!每个炮台的命中概率
	_range    currRange;
	//!每个炮台的射程
	_hit	  currHit;
	//!切换炮台
	void      change(int);
	//!瞄准
	void      shoot(float,float);

	//!炮弹
	Bullet*   b1;

	//!渔网
	cocos2d::Vector<cocos2d::Sprite *>fishnets;

	//!创建渔网
	void      addFishNet(float,float);

	//!fishnet设置消除时间
	float    lifetime;
	//!碰撞检测
	void      checkColloisn(cocos2d::Sprite*);

	//!跟新函数
	void      update();
	


	CREATE_FUNC(Weapon);
};

#endif
