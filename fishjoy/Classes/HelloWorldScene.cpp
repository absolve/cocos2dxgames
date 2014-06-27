#include "HelloWorldScene.h"
#include "CannonLayer.h"
#include "PaneLayer.h"
#include "Control.h"
#include "weapon.h"
#include "MenuLayer.h"

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
    this->addChild(menu, 10);

    /////////////////////////////
    // 3. add your codes below...

	//!添加背景图片
	auto   bd=Sprite::create("images/background3.png");
	bd->setPosition(480,270);
	this->addChild(bd,1);

	//!添加背景粒子系统
	auto    texture=Director::getInstance()->getTextureCache();
	auto    snow=ParticleSnow::create();
	snow->setTexture(texture->addImage("stars.png"));
	snow->setPosition(480,540);
	this->addChild(snow,3);

	//!添加事件监听
	auto   listener=EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan=CC_CALLBACK_2(HelloWorld::touchEvent,this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener,this);

	//!添加定时器
	schedule(schedule_selector(HelloWorld::update));

	//!添加菜单层
	menulayer=MenuLayer::create();
	menulayer->setPosition(460,300);
	menulayer->setVisible(false);
	this->addChild(menulayer,2,4);
	//!添加鱼layer


	//!添加功能layer
	panelayer =PaneLayer::create();
	this->addChild(panelayer,2,2);
	//!添加炮台层
	cannonlayer =CannonLayer::create();
	this->addChild(cannonlayer,3,3);

    
	//!添加控制者
	Control::getInstance()->init(this);


    return true;
}

void HelloWorld::update(float  dt){

	/*log("hello");*/
	auto    weapon=dynamic_cast<Weapon*>(cannonlayer->getChildByTag(1));
	weapon->update();


}

void HelloWorld::pauseCallBack(Ref* pSender){



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


bool HelloWorld::touchEvent(Touch *touch,Event * event){

	/*log("hello");*/
	auto   point=touch->getLocation();
	
	auto    s=dynamic_cast<Weapon*>(cannonlayer->getChildByTag(1));

	s->shoot(point.x,point.y);


	return  true;
}