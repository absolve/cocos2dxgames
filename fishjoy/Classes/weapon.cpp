#include "weapon.h"
#include "Bullet.h"


USING_NS_CC;


bool   Weapon::init(){


	//!添加炮弹
	b1=Bullet::create();

	this->addChild(b1,1,20);

	//!添加各种炮台
	auto   spriteFrame=SpriteFrameCache::getInstance();
	spriteFrame->addSpriteFramesWithFile("cannon-ipadhd.plist");


	//!创建各种炮台 1
	auto   s1=Sprite::createWithSpriteFrameName("actor_cannon1_11.png");
	s1->setScale(0.5);
	s1->setVisible(false);
	this->addChild(s1,1,1);

	auto   s2=Sprite::createWithSpriteFrameName("actor_cannon1_21.png");
	s2->setScale(0.5);
	s2->setVisible(false);
	this->addChild(s2,1,2);

	auto   s3=Sprite::createWithSpriteFrameName("actor_cannon1_31.png");
	s3->setScale(0.5);
	s3->setVisible(false);
	this->addChild(s3,1,3);

	auto   s4=Sprite::createWithSpriteFrameName("actor_cannon1_41.png");
	s4->setScale(0.5);
	s4->setVisible(false);
	this->addChild(s4,1,4);

	auto   s5=Sprite::createWithSpriteFrameName("actor_cannon1_51.png");
	s5->setScale(0.5);
	s5->setVisible(false);
	this->addChild(s5,1,5);

	auto   s6=Sprite::createWithSpriteFrameName("actor_cannon1_61.png");
	s6->setScale(0.5);
	s6->setVisible(false);
	this->addChild(s6,1,6);

	auto   s7=Sprite::createWithSpriteFrameName("actor_cannon1_71.png");
	s7->setScale(0.5);
	s7->setVisible(false);
	this->addChild(s7,1,7);

	auto   s8=Sprite::createWithSpriteFrameName("actor_cannon_jiguang_01.png");
	s8->setScale(0.5);
	s8->setVisible(false);
	this->addChild(s8,1,8);


	//!设置当前炮台等级
	currCannon=cannon_1;
	currRange=range_1;
	currHit=hit_1;

	//!将当前的炮台设置为显示
	auto    s=dynamic_cast<Sprite*>(this->getChildByTag(currCannon));
	s->setVisible(true);

	//!设置渔网生命时间
	lifetime=1.8f;




	return   true;
}

void   Weapon::change(int  i){

	int s=currCannon+i;
	auto    s1=dynamic_cast<Sprite*>(this->getChildByTag(currCannon));
	auto    r=s1->getRotation();
	s1->setVisible(false);

	//!设置当前炮台的属性
	currCannon=(_cannon)s;
	currRange=(_range)s;

	if(s>cannon_7){
		currCannon=cannon_1;
		currRange=range_1;
	}
	if(s<cannon_1){
		currCannon=cannon_7;
		currRange=range_7;

	}
	
	auto    s2=dynamic_cast<Sprite*>(this->getChildByTag(currCannon));
	s2->setRotation(r);
	s2->setVisible(true);

}

void    Weapon::shoot(float x,float y){

	//log("x=%f,y=%f",x,y);

	auto    x1=this->getPositionX();
	auto    y1=this->getPositionY();

	auto    s1=dynamic_cast<Sprite*>(this->getChildByTag(currCannon));

	

	if(x>x1){
		auto   result=(x-x1)*(x-x1)+(y-y1)*(y-y1);
		auto   lo=sqrt(result);
		auto   time=lo/100*0.3;

		s1->setRotation(55*atan(abs(x-x1)/abs(y-y1)));

		auto  point=this->convertToNodeSpace(Point(x,y));
		//!炮台发射子弹
		b1->fly(55*atan(abs(x-x1)/abs(y-y1)),point.x,point.y,time);
	
	}
	if(x<x1){
		auto   result=(x-x1)*(x-x1)+(y-y1)*(y-y1);
		auto   lo=sqrt(result);
		auto   time=lo/100*0.3;

		s1->setRotation(-abs(55*atan(abs(x-x1)/abs(y-y1))));
		auto  point=this->convertToNodeSpace(Point(x,y));
		//!炮台发射子弹
		b1->fly(-abs(55*atan(abs(x-x1)/abs(y-y1))),point.x,point.y,time);
	}
	if(x==x1){
		auto   result=(x-x1)*(x-x1)+(y-y1)*(y-y1);
		auto   lo=sqrt(result);
		auto   time=lo/100*0.3;

		s1->setRotation(0);
		auto  point=this->convertToNodeSpace(Point(x,y));
		//!炮台发射子弹
		b1->fly(0,point.x,point.y,time);
	}
	
	

}

void   Weapon::checkColloisn(Sprite*){


}

void   Weapon::addFishNet(float x,float y){

	auto   fishnet=Sprite::createWithSpriteFrameName("weapon_net_001.png");
	Vector<SpriteFrame*> ani(7);
	char   name[20]={0};
	for(int i=1;i<=7;i++){
		sprintf(name,"weapon_net_00%d.png",i);
		auto   spritef=SpriteFrameCache::getInstance()->getSpriteFrameByName(name);
		ani.pushBack(spritef);
	}
	//!添加动画
	auto   anm=Animation::createWithSpriteFrames(ani,0.1f);
	fishnet->setScale(0.5);
	fishnet->setPosition(x,y);
	fishnet->runAction(Animate::create(anm));

	//!fishnet设置消除时间
	int    lifetime=90;
	
	fishnet->setUserData((void*)lifetime);

	this->addChild(fishnet);
	fishnets.pushBack(fishnet);

}

void   Weapon::update(){

	//!将所有的渔网的生命减一
	for(auto  i=fishnets.begin();i!=fishnets.end();++i){
		auto  time=(int)(*i)->getUserData();
		time--;
		(*i)->setUserData((void*)time);
	}

	//!清除所有生命<0的渔网
	for(auto  i=fishnets.begin();i!=fishnets.end();){
		auto  time=(int)(*i)->getUserData();
		if(time<=0){
			(*i)->removeFromParent();
			i=fishnets.erase(i);
		}else{
			i++;
		}
	}


}