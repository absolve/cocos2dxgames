#include "GoodsLayer.h"


USING_NS_CC;


bool   GoodsLayer::init(){

	if(!Layer::init()){
		return  false;
	}

	auto   listener=EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan=CC_CALLBACK_2(GoodsLayer::touch,this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener,this);

	//!Õ¨µ¯¾«ÁéÍ¼Æ¬
    bomb1=Sprite::createWithSpriteFrameName("bomb.png");
	bomb1->setScale(1.5);
	bomb1->setPosition(480-bomb1->getContentSize().width/2,300+bomb1->getContentSize().height/2);
	//!ÉèÖÃÕ¨µ¯Î´Æô¶¯
	explosion=false;

	this->addChild(bomb1,1);



	return   true;
}


bool   GoodsLayer::touch(Touch *touch,Event * event){

	//!Õ¨µ¯°´Å¥±»´¥·¢
	auto target = static_cast<Sprite*>(event->getCurrentTarget());

	Point locationInNode = target->convertToNodeSpace(touch->getLocation());
	Size s = target->getContentSize();
	Rect rect = Rect(0, 0, s.width, s.height);

	if (rect.containsPoint(locationInNode))
	{
		target->setVisible(false);
		setExplosion(true);
		return true;
	}

	return  true;
}