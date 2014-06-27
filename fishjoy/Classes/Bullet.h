#pragma once

#include "cocos2d.h"

class Bullet:public  cocos2d::Node
{
public:
	

	virtual bool init(); 
	//!炮弹飞行
	void   fly(float,float,float,float=1.5);
	//!炮弹飞行结束回调函数
	void   over();
	CREATE_FUNC(Bullet);

private:
	bool   flyState;
};

