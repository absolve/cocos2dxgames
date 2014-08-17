#include "WelcomeScene.h"
#include "HelloWorldScene.h"
USING_NS_CC;

Scene * WelcomeScene::createScene(){

	auto  scene =Scene::create();
	auto  layer=WelcomeScene::create();
	scene->addChild(layer);
	return  scene;
	
}

bool   WelcomeScene::init(){

	if(!Layer::init()){
		return  false;
	}

	//!ÉèÖÃ¶¨Ê±Æ÷
	schedule(schedule_selector(WelcomeScene::update));
	
	//!±³¾°Í¼1
	auto  bd1=Sprite::create("bg_01.jpg");
	bd1->setAnchorPoint(Point(0,0));
	bd1->setPosition(0,0);
	//!±³¾°Í¼2
	auto  bd2=Sprite::create("bg_02.jpg");
	bd2->setAnchorPoint(Point(0,0));
	bd2->setPosition(0,800);
	//!Ìí¼Ólogo1
	auto  logo1=Sprite::create("logo.png");
	logo1->setPosition(Point(240,600));
	//!Ìí¼Ólogo2
	auto  logo2=Sprite::create("BigPlane.png");
	logo2->setPosition(Point(70,620));

	this->addChild(bd1,1,1);
	this->addChild(bd2,1,2);
	this->addChild(logo1,1);
	this->addChild(logo2,1);

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();

	//!¹Ø±Õ°´Å¥

	auto  closeItem = MenuItemImage::create("close01.png","close03.png",
											CC_CALLBACK_1(WelcomeScene::closeCallBack,this));

	closeItem->setPosition(Point(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
		origin.y + closeItem->getContentSize().height/2));

	//!¿ªÊ¼°´Å¥
	auto  startItem =MenuItemImage::create("ready.png","go.png",
											CC_CALLBACK_1(WelcomeScene::nextSceneCallBack,this));
	startItem->setScale(0.5);
	startItem->setPosition(240,350);

	auto menu = Menu::create(closeItem,startItem, NULL);
	menu->setPosition(Point::ZERO);
	this->addChild(menu, 1);




	return true;
}

void   WelcomeScene::update(float dt){

	
	//!¹ö¶¯Í¼Æ¬1
	auto  b1=dynamic_cast<Sprite*>(this->getChildByTag(1));
	auto  yOffset=b1->getPositionY();

	if(yOffset<=-800){
		b1->setPositionY(796);
	}else{
		yOffset-=1.5;
		b1->setPositionY(yOffset);
	}
	//!¹ö¶¯Í¼Æ¬2
	auto  b2=dynamic_cast<Sprite*>(this->getChildByTag(2));
	auto  yOffset1=b2->getPositionY();
	if(yOffset1<=-800){
		b2->setPositionY(796);
	}else{
		yOffset1-=1.5;
		b2->setPositionY(yOffset1);
	}


}


void  WelcomeScene::closeCallBack(Ref* pSender){

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
	return;
#endif

	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif


}

void  WelcomeScene::nextSceneCallBack(Ref* pSender){

	Director::getInstance()->replaceScene(TransitionFade::create(1.2,
											HelloWorld::createScene()));


}