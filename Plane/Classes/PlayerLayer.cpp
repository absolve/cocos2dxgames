#include "PlayerLayer.h"

USING_NS_CC;

bool   PlayerLayer::init(){

	if(!Layer::init()){
		return  false;
	}


	//!添加精灵动画
	Vector<SpriteFrame*> animFrames(2);
	auto    plane1=SpriteFrameCache::getInstance()->getSpriteFrameByName("hero01.png");
	auto    plane2=SpriteFrameCache::getInstance()->getSpriteFrameByName("hero02.png");
	animFrames.pushBack(plane1);
	animFrames.pushBack(plane2);

	auto    planeAni=Animation::createWithSpriteFrames(animFrames,0.15);
	//!创建精灵
	auto    plane=Sprite::createWithSpriteFrame(plane1);
	//plane->setPosition(240,100);
	plane->runAction(RepeatForever::create(Animate::create(planeAni)));
	//!添加到层里
	this->addChild(plane,1,1);
	//!添加爆炸图片
	auto    ex=Sprite::createWithSpriteFrameName("explosion_02.png");
	ex->setAnchorPoint(Point(-0.4,-0.5));
	/*ex->setVisible(false);*/
	plane->addChild(ex,1,1);

	//!设置子弹的类型
	bstyle=_bullet1;
	//!添加定时器
	/*schedule(schedule_selector(PlayerLayer::update,this),0.15);*/
	time=0;
	delayTime=0.15;

	return  true;
}

void	PlayerLayer::setPlanePos(float x,float y){
	   getPlayer()->setPosition(x,y);
}

Node*   PlayerLayer::getPlayer(){

	auto   sprite=this->getChildByTag(1);
	return  sprite;
}

void   PlayerLayer::update(float  dt){

	/*shoot();*/
	time+=dt;
	if(time>=delayTime){
		shoot();
		time=0;
	}
}

Rect   PlayerLayer::getPlaneRect(){
		
	auto    s1=getPlayer();
	auto    r1=s1->getBoundingBox();
	r1.setRect(r1.origin.x+r1.size.width*0.4,r1.origin.y+r1.size.height*0.4,
					r1.size.width*0.2,r1.size.height*0.2);
	return  r1;

}

void   PlayerLayer::shoot(){

	auto   bullet=Sprite::createWithSpriteFrameName("bullet01.png");
	auto   plane=dynamic_cast<Sprite*>(getPlayer());
	auto   point=plane->getPosition();
	if(bstyle==1){
		float   time=(820-point.y)/400;
		bullet->setPosition(point.x,point.y+20);
		bullet->runAction(MoveTo::create(time,Point(point.x,820)));
		this->addChild(bullet,1);
		bullets.pushBack(bullet);

	}else{


	}
	
}
