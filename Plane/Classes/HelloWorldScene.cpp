#include "HelloWorldScene.h"
#include "PlayerLayer.h"
#include "EnemyLayer.h"
#include "GoodsLayer.h"
#include "GameReady.h"
#include "gameStart.h"
#include "GamePause.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    auto closeItem = MenuItemImage::create(
                                           "close01.png",
                                           "close03.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Point(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                               800-closeItem->getContentSize().height/2));

	auto   onItem=MenuItemImage::create("pauseBT.png","pauseBT.png",
											CC_CALLBACK_1(HelloWorld::pauseCallBack,this));
	
	onItem->setPosition(25,770);

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem,NULL);
	menu->addChild(onItem,1,1);
    menu->setPosition(Point::ZERO);
    this->addChild(menu,5,11);

    /////////////////////////////
    // 3. add your codes below...
	//!添加背景图片1
	auto   bd1=Sprite::create("bg_01.jpg");
	bd1->setAnchorPoint(Point(0,0));
	bd1->setPosition(0,0);
	this->addChild(bd1,1,5);
	//!添加背景图片1
	auto   bd2=Sprite::create("bg_02.jpg");
	bd2->setAnchorPoint(Point(0,0));
	bd2->setPosition(0,800);
	this->addChild(bd2,1,6);



	//!添加游戏图片资源
	auto   spriteFrame=SpriteFrameCache::getInstance();
	spriteFrame->addSpriteFramesWithFile("plane.plist");
	//!设置游戏区域
	gameWin.setRect(0,0,480,800);
	//!添加定时器
	schedule(schedule_selector(HelloWorld::update));
	//!分数清零
	scores=0;
	highScore=getHighScore();
	XOffset=YOffset=0;
	//!设置游戏暂停的标志开始设置为否
	pauseFlag=false;

	//!添加事件监听
	auto    listener=EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan=CC_CALLBACK_2(HelloWorld::touchBegin,this);
	listener->onTouchMoved=CC_CALLBACK_2(HelloWorld::touchMove,this);
	listener->onTouchEnded=CC_CALLBACK_2(HelloWorld::touchEnd,this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener,this);

	//////////////////////////////////////////////////////////////////////////
	//!最后得分结果层
	initScoreLayer();
	//!添加准备的字符串
	auto    ready=LabelTTF::create("--Press  The  Screen  To  Start--","Arial",30);
	ready->setPosition(240,400);
	ready->setVisible(false);
	this->addChild(ready,2,9);
	//！添加实时分数标签
	auto    nowScore=LabelTTF::create(a,"Arial",25);
	nowScore->setPosition(240,760);
	this->addChild(nowScore,2,10);

	//!添加敌人精灵层
	 enemylayer =EnemyLayer::create();
	 this->addChild(enemylayer,1,1);

    //!添加玩家精灵层
	playerlayer  =PlayerLayer::create();
	this->addChild(playerlayer,2,2);

	//!添加特殊物品层
	goodslayer= GoodsLayer::create();
	this->addChild(goodslayer,3,3);
    
	//!设置当前的游戏状态
	currState=GameReady::getInstance();
	currState->enter(this);


    return true;
}

void  HelloWorld::initScoreLayer(){

	//!游戏最后分数层
	fscore=LayerColor::create(Color4B(0,0,0,150));
	auto    flags=LabelTTF::create("---Score---","Arial",35);
	//!当前得分的字符串
	sprintf(a,"%d",scores);
	auto	lastScore=LabelTTF::create(a,"Arial",28);
	lastScore->setPosition(240,500);
	flags->setPosition(240,600);
	auto    flag1=LabelTTF::create("---HighScore---","Arial",35);
	flag1->setPosition(240,400);
	//!最高分的字符串
	sprintf(hs,"%d",highScore);
	auto    hss=LabelTTF::create(hs,"Arial",28);
	hss->setPosition(240,300);

	fscore->addChild(hss,1,2);
	fscore->addChild(flags);
	fscore->addChild(flag1);
	fscore->addChild(lastScore,1,1);
	fscore->setVisible(false);
	this->addChild(fscore,4,4);
	//!添加重新开始菜单
	auto    resetItem=MenuItemFont::create("Restart",CC_CALLBACK_1(HelloWorld::restartCallBack,this));
	resetItem->setPosition(240,200);
	auto    menu1=Menu::create(resetItem,NULL);
	menu1->setPosition(Point::ZERO);
	fscore->addChild(menu1,1,1);

}

void  HelloWorld::updateBackGround(){

	//!滚动图片1
	auto  b1=dynamic_cast<Sprite*>(this->getChildByTag(5));
	auto  yOffset=b1->getPositionY();

	if(yOffset<=-800){
		b1->setPositionY(796);
	}else{
		yOffset-=1.5;
		b1->setPositionY(yOffset);
	}
	//!滚动图片2
	auto  b2=dynamic_cast<Sprite*>(this->getChildByTag(6));
	auto  yOffset1=b2->getPositionY();
	if(yOffset1<=-800){
		b2->setPositionY(796);
	}else{
		yOffset1-=1.5;
		b2->setPositionY(yOffset1);
	}

}

void  HelloWorld::updateHighScore(){
		highScore=scores;
		auto   fs=dynamic_cast<LabelTTF*>(fscore->getChildByTag(2));
		sprintf(hs,"%d",highScore);
		fs->setString(hs);
}

void  HelloWorld::update(float dt){

	currState->execute(this);

}

void  HelloWorld::saveHighScore(){
	auto   file=UserDefault::getInstance();
	file->setIntegerForKey("HighScore",highScore);
	file->flush();
}

int   HelloWorld::getHighScore(){
	auto   file=UserDefault::getInstance();
	highScore=file->getIntegerForKey("HighScore");
	return   highScore;
}

void  HelloWorld::restartCallBack(Ref* pSender){
	 changeState(GameReady::getInstance());
}

void  HelloWorld::changeState(state<HelloWorld> *s){
	
		currState->exit(this);
		currState=s;
		s->enter(this);

}

void  HelloWorld::pauseCallBack(Ref* pSender){


	auto   menu=dynamic_cast<Menu*>(this->getChildByTag(11));
	auto   item1=dynamic_cast<MenuItemImage*>(menu->getChildByTag(1));
	auto   spriteFrame=SpriteFrameCache::getInstance();
	if(pauseFlag){
		item1->setNormalSpriteFrame(spriteFrame->getSpriteFrameByName("pauseBT.png"));
		item1->setSelectedSpriteFrame(spriteFrame->getSpriteFrameByName("pauseBT.png"));
		this->changeState(GameStart::getInstance());
		pauseFlag=false;
	}else{
		item1->setNormalSpriteFrame(spriteFrame->getSpriteFrameByName("startBT.png"));
		item1->setSelectedSpriteFrame(spriteFrame->getSpriteFrameByName("startBT.png"));
		this->changeState(GamePause::getInstance());
		pauseFlag=true;
	}


}

bool  HelloWorld::touchBegin(Touch *touch,Event * event){

	/*log("begin");*/
	point=touch->getLocation();
	currState->handleEvent(this);
	return  true;
}

void  HelloWorld::touchMove(Touch *touch,Event * event){

	/*log("move");*/
	auto  point1 =touch->getLocation();
	XOffset =point1.x-point.x;
	YOffset	=point1.y-point.y;
	point=point1;
	//!调用状态的处理函数
	currState->handleEvent(this);


}

void  HelloWorld::touchEnd(Touch *touch,Event * event){

	/*log("end");*/
}

void  HelloWorld::updateScore(){
	 sprintf(a,"%d",scores);
	 auto	s1=dynamic_cast<LabelTTF*>(this->getChildByTag(10));
	 s1->setString(a);
}

void  HelloWorld::updateLastScore(){
	  sprintf(a,"%d",scores);
	  auto   s1=dynamic_cast<LabelTTF*>(fscore->getChildByTag(1));
	  s1->setString(a);
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
