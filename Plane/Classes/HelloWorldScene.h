#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "State.h"
class   PlayerLayer;
class   EnemyLayer;
class   GoodsLayer;



class HelloWorld : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
	//!更新函数
	void		update(float  dt);
	//!接触开始事件
	bool        touchBegin(cocos2d::Touch *touch,cocos2d::Event * event);
	//!拖动事件
	void		touchMove(cocos2d::Touch *touch,cocos2d::Event * event);
	//!接触结束事件
	void		touchEnd(cocos2d::Touch *touch,cocos2d::Event * event);
	//状态的切换
	void		changeState(state<HelloWorld>  *);
	//!更新分数显示
	void		updateScore();
	//!更新最后得分
	void		updateLastScore();
	//!更新最高分
	void		updateHighScore();
	//!重新开始回调函数
	void        restartCallBack(cocos2d::Ref* pSender);
	//!初始化游戏追后得分榜
	void        initScoreLayer();
	//!保存用户高分数据
	void        saveHighScore();
	//!获取最高分数据
	int         getHighScore();
	//!滚动背景图
	void        updateBackGround();
public:

	PlayerLayer   *		playerlayer;
	EnemyLayer	  *		enemylayer;
	GoodsLayer	  *		goodslayer;
	cocos2d::LayerColor	  *fscore;

	state<HelloWorld>  *currState;
	//!游戏分数
	int    scores;
	//!最高分
	int    highScore;
	int    getHS()  {return highScore;}
	//!分数字符串
	char   a[20];
	//!最高分数字符串
	char   hs[20];
	void   setScore(int  s)  {scores=s;}
	int	   getScore(){return  scores;}
	void   scorePlus() {scores++;}
	//!获取接触的初始坐标
	cocos2d::Point      point;
	//!偏移量x,y
	float				XOffset;
	float				YOffset;
	//!游戏区域
	cocos2d::Rect		gameWin;

};

#endif // __HELLOWORLD_SCENE_H__
