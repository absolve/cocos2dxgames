#include "HelloWorldScene.h"
#include "pipe.h"
#include "bird.h"
#include "gameReady.h"
#include "gameEnd.h"

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

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));  
	closeItem->setPosition(Point(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));
    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu, 5,40);
    /////////////////////////////
    // 3. add your codes below...
    //添加定时器
	schedule(schedule_selector(HelloWorld::update));
    //!添加背景图片1
    auto sprite = Sprite::create("images/background2.png");
	sprite->setScaleX(2.5);
	sprite->setScaleY(2.5);

    // position the sprite on the center of the screen
    sprite->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(sprite, 0);
    
	//!添加背景图片2
	auto   sprite1=Sprite::create("images/backgroundBottom.png");
	sprite1->setAnchorPoint(Point(0,0));
	sprite1->setPosition(0,0);
	this->addChild(sprite1,2);

	//!添加游戏准备图片
	auto   sprite2 =Sprite::create("images/getready.png");
	sprite2->setPosition(180,500);
	sprite2->setVisible(false);
	sprite2->setScaleX(2);
	sprite2->setScaleY(2);
	this->addChild(sprite2,2,2);

	//!添加游戏结束图片
	auto   sprite3=Sprite::create("images/gameover.png");
	sprite3->setScaleX(2);
	sprite3->setScaleY(2);
	sprite3->setPosition(180,500);
	sprite3->setVisible(false);
	this->addChild(sprite3,2,3);
	this->setOpacity(0.0f);

	//!添加分数面板图片
	auto   sprite4=Sprite::create("images/scoreboard.png");
	sprite4->setScaleX(2.5);
	sprite4->setScaleY(2.5);
	sprite4->setPosition(180,350);
	sprite4->setVisible(false);
	this->addChild(sprite4,2,4);
	sprite4->setOpacity(0.0f);

	//!添加分数面板分数字体
	score=0;
	sprintf(b,"%d",score);
	auto   fscores=LabelTTF::create(b,"Arial",25);
	this->addChild(fscores,5,100);
	fscores->setPosition(260,370);
	fscores->setVisible(false);
	//!添加一个新分数标志
	auto   newsprite=Sprite::create("images/newhighscore.png");
	newsprite->setScale(2);
	newsprite->setAnchorPoint(Point(1.5,-1.0));
	fscores->addChild(newsprite,1,1);
	newsprite->setVisible(false);

	//!添加分数面板最高分字体
	this->getUserScore();
	sprintf(c,"%d",userScore);
	auto   fuscores=LabelTTF::create(c,"Arial",25);
	fuscores->setPosition(260,320);
	fuscores->setVisible(false);
	this->addChild(fuscores,5,101);

	//!添加重新开始按钮
	auto   restartItem = MenuItemImage::create("images/pauseRestart.png","images/pauseRestart1.png",CC_CALLBACK_1(HelloWorld::restartCallBack,this));
	restartItem->setPosition(100,240);
	restartItem->setVisible(false);
	restartItem->setScale(0.7);
	menu->addChild(restartItem,0,1992);

	//!添加分数
	sprintf(a,"scores:%d",score);
	auto   scores=LabelTTF::create(a,"Arial",25);
	scores->setPosition(180,620);
	this->addChild(scores,4,10);

	//!添加事件
	auto   listener =EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan=CC_CALLBACK_2(HelloWorld::touchEvent,this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener,this);

	//!添加雪花效果
	auto   snow=ParticleSnow::create();
	auto   texture=Director::getInstance()->getTextureCache();
	snow->setTexture(texture->addImage("stars.png"));
	snow->setPosition(180,640);

	this->addChild(snow,2);

	//!添加滚动图片1
	auto   sbd1=Sprite::create("images/ground.png");
	sbd1->setAnchorPoint(Point(0,0));
	sbd1->setPosition(0,120);
	sbd1->setScale(2.2);
	this->addChild(sbd1,2,20);

	//!添加滚动图片2
	auto   sbd2=Sprite::create("images/ground.png");
	sbd2->setAnchorPoint(Point(0,0));
	sbd2->setPosition(360,120);
	sbd2->setScale(2.2);
	this->addChild(sbd2,2,21);

	//!添加游戏金币,该金币为玩家没玩一次游戏所得分数
	auto   goldsprite=Sprite::create("images/flappycoin.png");
	goldsprite->setScale(1.5);
	goldsprite->setAnchorPoint(Point(1.2,0));
	auto   file=UserDefault::getInstance();
	gameGold=file->getIntegerForKey("gameGold");
	sprintf(d,"%d",gameGold);
	auto   gold=LabelTTF::create(d,"Arial",20);
	gold->setPosition(45,580);
	gold->setAnchorPoint(Point(0,0));
	gold->addChild(goldsprite);
	this->addChild(gold,3,25);

	srand(time(0));
	_time=0.0f;
	//!设置当前状态
	currState =gameReady::getInstance();
	currState->enter(this);
    return true;
}

void HelloWorld::getUserScore(){
	auto   file=UserDefault::getInstance();
	userScore=file->getIntegerForKey("userScore");
}

void HelloWorld::setUserScore(){
	auto   file=UserDefault::getInstance();
	file->setIntegerForKey("userScore",score);
	file->flush();
	userScore=score;
}

void HelloWorld::update(float dt){
	/*log("hello world");*/
	_time+=dt;
	currState->execute(this);
}

void HelloWorld::changeState(state<HelloWorld> * s){
	currState->exit(this);
	currState=s;
	currState->enter(this);
}

void HelloWorld::checkCollision(){
	auto   ypos=bird::getInstance()->getYpos();
	if(ypos<=160){
		this->changeState(gameEnd::getInstance());
	}
	//!检测小鸟与水管的碰撞
	auto   rect1=bird::getInstance()->getRect();
	rect1.size.height-=5;
	rect1.size.width-=5;
	for(auto  i=pipes.begin();i!=pipes.end();++i)
	{
		auto  rect2=(*i)->getBoundingBox();
		if(rect1.intersectsRect(rect2)){
			changeState(gameEnd::getInstance());
			break;
		}	
	}
}

bool HelloWorld::touchEvent(Touch *touch,Event * event){
	/*log("hello");*/
	currState->handleEvent(this);
	return  true;
}

void HelloWorld::restartCallBack(Ref* pSender){
	changeState(gameReady::getInstance());
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

	UserDefault::getInstance()->setIntegerForKey("gameGold",gameGold);

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
