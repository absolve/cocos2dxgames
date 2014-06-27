#include "PaneLayer.h"
#include "HelloWorldScene.h"
#include "weapon.h"
#include "Control.h"
#include "CannonLayer.h"
#include "Control.h"
#include "MenuLayer.h"


USING_NS_CC;


bool   PaneLayer::init(){

	if(!Layer::init()){
		return  false;
	}

	//!Ìí¼ÓÓÎÏ·²Ëµ¥µ××ù
	auto    menu1=Sprite::create("images/UI_GameMenu.png");
	menu1->setPosition(480,31);
	this->addChild(menu1,2);

	//!Ìí¼ÓÓÎÏ·²Ëµ¥×°ÊÎ
	auto    ss=Sprite::create("energy_sp-ipadhd.png");
	ss->setPosition(460,65);
	this->addChild(ss,1);

	//!Ìí¼Ó×ó±ßÍ¼Æ¬
	auto    s1=Sprite::create("images/UI_GameMenu01.png");
	s1->setAnchorPoint(Point(0,0));
	s1->setPosition(0,0);
	this->addChild(s1,1);

	//!Ìí¼ÓÓÎÏ·²Ëµ¥¶¥²¿
	auto   menu2=Sprite::create("images/UI_GameMenu02.png");
	menu2->setPosition(460,510);
	this->addChild(menu2,1);

	//!Ìí¼ÓÔÝÍ£°´Å¥
	auto   pauseButton1=Sprite::create("images/button01.png");
	auto   pauseButton2=Sprite::create("images/button02.png");
	auto   pauseButton=MenuItemSprite::create(pauseButton1,pauseButton2,
		CC_CALLBACK_1(PaneLayer::pauseButtonCallBack,this));
	pauseButton->setPosition(850,26);

	//!Ìí¼ÓÉùÒô°´Å¥
	auto   musicButton1=Sprite::create("images/musicbutton01.png");
	auto   musicButton2=Sprite::create("images/musicbutton02.png");
	auto   musicButton=MenuItemSprite::create(musicButton1,musicButton2,
		CC_CALLBACK_1(PaneLayer::musicButtonCallBack,this));
	musicButton->setPosition(200,515);

	//!Ìí¼Ó½ØÆÁ°´Å¥
	auto   cameraButton1=Sprite::create("images/camera1.png");
	auto   cameraButton2=Sprite::create("images/camera2.png");
	auto   cameraButton=MenuItemSprite::create(cameraButton1,cameraButton2,
		CC_CALLBACK_1(PaneLayer::cameraButtonCallBack,this));
	cameraButton->setPosition(800,515);

	//!ÅÚÌ¨ÇÐ»»°´Å¥1
	auto   cannonButton1=Sprite::create("images/cannon1.png");
	auto   cannonButton2=Sprite::create("images/cannon2.png");
	auto   cannondec=MenuItemSprite::create(cannonButton1,cannonButton2,
		CC_CALLBACK_1(PaneLayer::cannondecCallBack,this));
	cannondec->setPosition(400,28);

	//!ÅÚÌ¨ÇÐ»»°´Å¥2
	auto   cannonButton3=Sprite::create("images/cannon3.png");
	auto   cannonButton4=Sprite::create("images/cannon4.png");
	auto   cannonadd=MenuItemSprite::create(cannonButton3,cannonButton4,
		CC_CALLBACK_1(PaneLayer::cannonaddCallBack,this));
	cannonadd->setPosition(520,28);

	//!Ìí¼Ó²Ëµ¥
	auto   mainmenu=Menu::create(pauseButton,musicButton,cameraButton,cannonadd
		,cannondec,NULL);
	mainmenu->setPosition(Point::ZERO);
	this->addChild(mainmenu,2);

	return   true;
}


void    PaneLayer::pauseButtonCallBack(Ref* pSender){

	auto   scene=Control::getInstance()->getScene();
	this->setVisible(false);
	//!Í£Ö¹ÏÔÊ¾ÆäËû²ã
	auto   menuLayer=scene->getMenuLayer();
	menuLayer->setVisible(true);
	auto   cannonLayer=scene->getCannonLayer();
	cannonLayer->setVisible(false);


}

void    PaneLayer::cameraButtonCallBack(Ref* pSender){


}

void    PaneLayer::musicButtonCallBack(Ref* pSender){

	

}

void    PaneLayer::cannondecCallBack(Ref* pSender){

	auto   s=Control::getInstance()->getScene();
	auto   s1=dynamic_cast<CannonLayer*>(s->getChildByTag(3));
	auto   weapon=dynamic_cast<Weapon*>(s1->getChildByTag(1));
	weapon->change(-1);

}

void    PaneLayer::cannonaddCallBack(Ref* pSender){

	auto   s=Control::getInstance()->getScene();
	auto   s1=dynamic_cast<CannonLayer*>(s->getChildByTag(3));
	auto   weapon=dynamic_cast<Weapon*>(s1->getChildByTag(1));
	weapon->change(1);

}