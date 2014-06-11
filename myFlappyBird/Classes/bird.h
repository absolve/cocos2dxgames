#ifndef  __BIRD_H__
#define  __BIRD_H__

#include "cocos2d.h"
USING_NS_CC;

class  HelloWorld;

class bird
{
public:
	
	static  bird*   getInstance();
	static  void    destory();
	void	        createBird(float,float,HelloWorld *);
	virtual  ~bird(){}
	//!更新函数
	void    update(float  dt);
	//!小鸟飞行
	void    fly(float);
	//!设置飞行初速度
	void    setFlySpeed(float  s)  {flySpeed=s;}
	//!移除小鸟
	void    removeBird();
	//!获取小鸟的y坐标
	float   getYpos() ;
	//!动画停止
	void    stopAni();
	//!获取小鸟的矩形大小
	Rect    getRect();




	CC_SYNTHESIZE(bool,isflying,flying)


private:

	bird();
	static  bird*   instance;
	//!保存着小鸟精灵指针
	Sprite  *   pbird;
	//!加速度
	float    aspeed;
	//!飞行初速度
	float    flySpeed;
	//!旋转角度
	float    rotation;

};

#endif // !1