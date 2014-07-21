#include "EnemyLayer.h"


USING_NS_CC;

std::string   EnemyLayer::enemyStyle[3]={"enemy_01.png",
									    	"enemy_02.png",
											"enemy_03.png"};


bool   EnemyLayer::init(){

	if(!Layer::init()){
		return  false;
	}
	//!随机种子
	srand(time(0));

	//设置敌人出现的时间
	delayTime=0.8;
	startTime=0;

	return  true;
}


void   EnemyLayer::createEnemy(){
	
		//!随机创建敌人,初始化敌人的飞行速度和生命值
		int     flag=rand()%100;
		int     style;
		if(flag<=60){
			style=2;
		}else if(flag>60 &&flag<=90){
			style=1;
		}else
		{
			style=0;
		}
		//!创建敌机精灵
		auto    sprite=Sprite::createWithSpriteFrameName(enemyStyle[style]);
		auto    xpos=sprite->getContentSize().width/2+rand()%(480-(int)sprite->getContentSize().width/2);
		auto	ypos=sprite->getContentSize().height+800;
		sprite->setPosition(xpos,ypos);
		float   time=(ypos+20)/(rand()%160+100);
		sprite->runAction(MoveTo::create(time,Point(xpos,-20)));

		//!添加爆炸精灵
		if(style==0){
			auto    ex=Sprite::createWithSpriteFrameName("explosion_03.png");
			ex->setAnchorPoint(Point(-1,-0.8));
			ex->setVisible(false);
			sprite->addChild(ex,1,1);
		}else if(style==1){
			auto    ex=Sprite::createWithSpriteFrameName("explosion_02.png");
			ex->setAnchorPoint(Point(-0.5,-0.5));
			ex->setVisible(false);
			sprite->addChild(ex,1,1);
		}else{
			auto    ex=Sprite::createWithSpriteFrameName("explosion_01.png");
			ex->setAnchorPoint(Point(-0.3,-0.1));
			ex->setVisible(false);
			sprite->addChild(ex,1,1);
		}

		//!生命值随机
		int    life=0;
		if(style==0){
			life=6+rand()%20;
		}else if(style==1){
			life=5+rand()%15;
		}else{
			life=rand()%2+1;
		}

		//!设置敌机的生命值
		sprite->setUserData((void*)life);
		this->addChild(sprite,1);
		enemyNum.pushBack(sprite);

}
