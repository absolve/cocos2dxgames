#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include <vector>
#include "state.h"

using namespace std;


//!游戏开始场景

class HelloWorld : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
	//!重新开始回调函数
	void restartCallBack(cocos2d::Ref* pSender);

    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);

	//!碰撞检测
	void   checkCollision();

	//!点击事件
	bool   touchEvent(cocos2d::Touch *touch,cocos2d::Event * event);
	//!状态切换
	void   changeState(state<HelloWorld> *);
public:
	//更新函数
	void    update(float  dt);
	//!存储水管的容器
	vector<cocos2d::Sprite*> pipes;
	//!游戏运行的时间
	float    _time;
	//!游戏分数
	int    score;
	//!游戏最高分
	int    userScore;
	//!游戏金币
	int    gameGold;
	//!游戏分数字符串
	char     a[20];
	//!游戏面板分数字符串
	char     b[10];
	//!游戏面板最高分字符串
	char     c[10];
	//!游戏金币数量字符串
	char     d[10];
	//!获取游戏最高分数
	void     getUserScore();
	//!写入游戏最高分数
	void     setUserScore();
private:
	//!游戏中的当前状态
	state<HelloWorld> * currState;
};

#endif // __HELLOWORLD_SCENE_H__
