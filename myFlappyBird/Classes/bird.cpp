#include "bird.h"
#include "HelloWorldScene.h"

bird* bird::instance=NULL;

bird::bird(){

	/*aspeed=-370.0f;
	flySpeed=0.0f;
	rotation=0.0f;
	isflying=false;*/
	pbird=NULL;
	srand(time(0));
}

bird*  bird::getInstance(){
	if(instance==NULL){
		instance =new bird();
		return instance;
	}
	return  instance;
}

void   bird::destory(){
	if(instance!=NULL){
		delete  instance;
		instance=NULL;
	}
}

float bird::getYpos(){
	if(pbird!=NULL){
		auto  ypos=pbird->getPositionY();
		return  ypos;
	}
	return   0;
}


void  bird::createBird(float x,float y,HelloWorld *h){
	//!初始化信息
	aspeed=-400.0f;
	flySpeed=0.0f;
	rotation=0.0f;
	isflying=false;
	//!随机化小鸟动画图片
	auto   bi=rand()%4;
	//!添加动画
	auto   cache=SpriteFrameCache::getInstance();
	cache->addSpriteFramesWithFile("images/birds.plist");
	cache->addSpriteFramesWithFile("images/mymedals.plist");

	Vector<SpriteFrame*> animFrames(4);
	char name[20]={0};

	for(int i=1;i<5;i++){
		sprintf(name,"bird_%d%d.png",bi,i);
		auto   frames=cache->getSpriteFrameByName(name);
		animFrames.pushBack(frames);

	}
	//!设置动画
	auto   anm=Animation::createWithSpriteFrames(animFrames,0.15f);

	char   aname[20]={0};
	sprintf(aname,"bird_%d1.png",bi);

	pbird =Sprite::createWithSpriteFrameName(aname);
	pbird->setScaleX(2.2);
	pbird->setScaleY(2.2);
	pbird->setPosition(x,y);
	h->addChild(pbird,3);
	pbird->runAction(RepeatForever::create(Animate::create(anm)));
}

void  bird::removeBird(){
	if(pbird!=NULL){
		pbird->removeFromParent();
		pbird=NULL;
	}
}

void  bird::stopAni(){
	if(pbird!=NULL)
		pbird->stopAllActions();
}


void  bird::update(float  dt){
	flySpeed+=aspeed*dt;
	auto   ypos=pbird->getPositionY();
	if(getflying()){	
		fly(dt);
	}else{
		/*if(ypos>=150){
			pbird->setPositionY(ypos+flySpeed*dt+aspeed*dt*dt/2);
		}*/
		pbird->setPositionY(ypos+flySpeed*dt+aspeed*dt*dt/2);

		if(rotation<100.0f && rotation>-90.0f){
			rotation -=aspeed*dt;
			pbird->setRotation(rotation);
		}
	}
}

void  bird::fly(float  dt){

	//!如果超过屏幕
	auto  ypos=pbird->getPositionY();
	if(ypos>=640){
		setflying(false);
		flySpeed=0;
		return;
	}
	//!设置初速度
	if(flySpeed>-120){
		flySpeed +=aspeed*dt; 
		auto  ypos=pbird->getPositionY()+flySpeed*dt+aspeed*dt*dt/2;
		pbird->setPositionY(ypos);
		if(rotation>-10.0f ){		
			rotation +=aspeed*dt*1.5;
			pbird->setRotation(rotation);
		}
	}else{
		setflying(false);	
	}
}


Rect  bird::getRect(){
	return  pbird->getBoundingBox();
}