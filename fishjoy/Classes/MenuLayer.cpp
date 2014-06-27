#include "MenuLayer.h"
#include "Control.h"
#include "HelloWorldScene.h"
#include "PaneLayer.h"
#include "CannonLayer.h"

USING_NS_CC;

bool    MenuLayer::init(){

	if(!Layer::init()){
		return  false;
	}

	//!菜单背景
	auto   sf=SpriteFrameCache::getInstance();
	sf->addSpriteFramesWithFile("UI_GamePauseLayer-ipadhd.plist");
	auto   s=Sprite::createWithSpriteFrameName("btn_pause_1.png");
	s->setScale(0.4);
	this->addChild(s);

	//!继续游戏
	auto   s1=Sprite::createWithSpriteFrameName("ui_button_box03_01.png");
	auto   s2=Sprite::createWithSpriteFrameName("ui_button_box03_02.png");
	auto   continues=MenuItemSprite::create(s1,s2,
			CC_CALLBACK_1(MenuLayer::menuContinueCallback,this));
	//!重新开始
	auto   s3=Sprite::createWithSpriteFrameName("ui_button_box03_01.png");
	auto   s4=Sprite::createWithSpriteFrameName("ui_button_box03_02.png");
	auto   resatrt=MenuItemSprite::create(s3,s4,
			CC_CALLBACK_1(MenuLayer::menuRestartCallBack,this));

	auto   restartSprite=Sprite::create("ui_2p_021_cn-ipadhd.png");
	restartSprite->setAnchorPoint(Point(-0.3,-0.5));
	resatrt->addChild(restartSprite);

	//!退出
	auto   s5=Sprite::createWithSpriteFrameName("ui_button_box03_01.png");
	auto   s6=Sprite::createWithSpriteFrameName("ui_button_box03_02.png");
	auto   gameExit=MenuItemSprite::create(s5,s6,
			CC_CALLBACK_1(MenuLayer::menuExitCallBack,this));

	auto    exitSprite=Sprite::create("ui_closeText_cn-ipadhd.png");
	exitSprite->setAnchorPoint(Point(-0.8,-0.5));
	gameExit->addChild(exitSprite);
	
	auto   sname=Sprite::create("ui_button_13_cn-ipadhd.png");
	sname->setAnchorPoint(Point(-0.3,-0.5));
	continues->addChild(sname);


	auto   menu1=Menu::create(continues,resatrt,gameExit,NULL);
	menu1->setScale(0.4);
	menu1->setPosition(Point(-280,-250));
	menu1->alignItemsVerticallyWithPadding(50);
	this->addChild(menu1,1,1);



	return  true;
}

void    MenuLayer::menuContinueCallback(Ref* pSender){

	auto    scene=Control::getInstance()->getScene();
	this->setVisible(false);
	auto    paneLayer=scene->getPaneLayer();
	paneLayer->setVisible(true);
	auto    cannonLayer=scene->getCannonLayer();
	cannonLayer->setVisible(true);

}

void    MenuLayer::menuRestartCallBack(Ref* pSender){


}

void    MenuLayer::menuExitCallBack(Ref* pSender){



}
