#include "Bullet.h"
#include "weapon.h"

USING_NS_CC;

bool   Bullet::init(){


	auto  sf=SpriteFrameCache::getInstance();
	sf->addSpriteFramesWithFile("Item-chaojiwuqi-ipadhd.plist");


	auto  s=Sprite::createWithSpriteFrameName("weapon_bullet_001.png");
	
	/*s->setVisible(false);*/
	

	this->addChild(s,1,1);

	flyState=false;

	return true;
}


void    Bullet::fly(float angel,float x,float y,float time){

	//!每次只能发射一颗炮弹
	if(!flyState){
		flyState=true;
		auto  s=dynamic_cast<Sprite*>(this->getChildByTag(1));
		s->setVisible(true);
		s->setRotation(angel);

		auto   move1=MoveTo::create(time,Point(x,y));
		auto   smove=Sequence::create(move1,
			CallFunc::create(this,callfunc_selector(Bullet::over)),NULL);
		s->runAction(smove);
	}

}

void    Bullet::over(){

	
	auto  s=dynamic_cast<Sprite*>(this->getChildByTag(1));
	s->setVisible(false);
	s->removeAllChildren();
	
	//!添加渔网
	auto   weapon1=dynamic_cast<Weapon*>(this->getParent());
	weapon1->addFishNet(s->getPositionX(),s->getPositionY());

	s->setPosition(0,0);
	flyState=false;

}