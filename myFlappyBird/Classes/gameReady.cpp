#include "gameReady.h"
#include "HelloWorldScene.h"
#include "bird.h"
#include "gameStart.h"

gameReady * gameReady::instance=NULL;


gameReady*  gameReady::getInstance(){
	if(instance==NULL){
		instance =new gameReady;
		return  instance;
	}
	return  instance;
}


void     gameReady::enter(HelloWorld *s){
	bird::getInstance()->createBird(100,400,s);
	auto    sprite=dynamic_cast<Sprite*>(s->getChildByTag(2));
	sprite->setVisible(true);

	auto   gl=sprite->getOpacity();
	if(gl==0.0f){
		sprite->setOpacity(255.0f);
	}
	sprite->removeAllChildren();
}

void     gameReady::execute(HelloWorld* s){
	//!滚动图片1
	auto    s1=dynamic_cast<Sprite*>(s->getChildByTag(20));
	auto    xoffset=s1->getPositionX();
	if(xoffset<-360){
		s1->setPositionX(360);
	}else{
		xoffset-=0.2;
		s1->setPositionX(xoffset);
	}
	//!滚动图片2
	auto    s2=dynamic_cast<Sprite*>(s->getChildByTag(21));
	auto    x1offset=s2->getPositionX();
	if(x1offset<-360){
		s2->setPositionX(360);
	}else{
		x1offset-=0.2;
		s2->setPositionX(x1offset);
	}
}

void     gameReady::exit(HelloWorld*  s){
	auto  sprite1=dynamic_cast<Sprite*>(s->getChildByTag(2));
	//sprite1->setVisible(false);
	auto   fadeout=FadeOut::create(1.0f);
	sprite1->runAction(fadeout);
	//!延长水管出现时间
	s->_time=-2.0f;
}

void     gameReady::handleEvent(HelloWorld*  s){

	//bird::getInstance()->setflying(true);
	//bird::getInstance()->setFlySpeed(320.0f);
	s->changeState(gameStart::getInstance());
}

void     gameReady::destroy(){
	if(instance!=NULL){
		delete  instance;
		instance=NULL;
	}
}



