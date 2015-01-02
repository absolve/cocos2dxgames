#include "welcomeScene.h"
#include "HelloWorldScene.h"

USING_NS_CC;


Scene*  welcomeScene::createScene(){
	// 'scene' is an autorelease object
	auto scene = Scene::create();
	// 'layer' is an autorelease object
	auto layer = welcomeScene::create();
	// add layer as a child to scene
	scene->addChild(layer);
	// return the scene
	return scene;
}

bool   welcomeScene::init(){
	// 1. super init first
	if ( !Layer::init() )
	{
		return false;
	}
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();
	//!退出按钮
	auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(welcomeScene::menuCloseCallback, this));
	closeItem->setPosition(Point(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
		origin.y + closeItem->getContentSize().height/2));

	//!游戏开始按钮
	auto  starGame =MenuItemImage::create("images/start.png","images/start1.png",CC_CALLBACK_1(welcomeScene::gameStartCallBack,this));
	starGame->setPosition(180,400);
	
	auto menu = Menu::create(closeItem,starGame, NULL);
	menu->setPosition(Point::ZERO);

	this->addChild(menu,1);

	//!添加背景
	auto  bg=Sprite::create("images/background2.png");
	bg->setScaleX(2.5);
	bg->setScaleY(2.5);
	// position the sprite on the center of the screen
	bg->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
	this->addChild(bg,0);

	//!添加标志
	auto  logo=Sprite::create("images/mylogo.png");

	logo->setScaleX(2);
	logo->setScaleY(2);

	logo->setPosition(180,560);
	this->addChild(logo,0);

	auto  fly1=MoveTo::create(2.0, Point(180, 600));
	auto  fly2=MoveTo::create(1.9,Point(180,500));
	auto  s1= Sequence ::create(fly1,fly2,NULL);
	logo->runAction(RepeatForever::create(s1));

	auto   listener=EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan=CC_CALLBACK_2(welcomeScene::touchEvent,this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener,this);

	return  true;
}

bool  welcomeScene::touchEvent(Touch *touch,Event * event){
	return  true;
}

void  welcomeScene::menuCloseCallback(cocos2d::Ref* pSender){

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
	return;
#endif

	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif

	//切换场景
	//Director::getInstance()->replaceScene(TransitionFade::create(1.2,
	//										HelloWorld::createScene()));

}

void welcomeScene::gameStartCallBack(cocos2d::Ref* pSender){
	//切换场景
	Director::getInstance()->replaceScene(TransitionFade::create(1.2,HelloWorld::createScene()));
}

void welcomeScene::gameOptionCallBack(cocos2d::Ref* pSender){
}

