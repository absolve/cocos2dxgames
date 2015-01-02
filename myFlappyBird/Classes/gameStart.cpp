#include "gameStart.h"
#include "HelloWorldScene.h"
#include "bird.h"
#include "pipe.h"

gameStart*  gameStart::instance=NULL;

gameStart*  gameStart::getInstance(){
	if(instance==NULL){
		instance =new gameStart;
		return  instance;
	}
	return   instance;
}

void     gameStart::destroy(){
	if(instance!=NULL){
		delete  instance;
		instance=NULL;
	}
}

void    gameStart::enter(HelloWorld*  s){
}

void    gameStart::execute(HelloWorld* s){

	auto   delaytime=Director::getInstance()->getDeltaTime();
	bird::getInstance()->update(delaytime);
	//!滚动图片1
	auto    s1=dynamic_cast<Sprite*>(s->getChildByTag(20));
	auto    xoffset=s1->getPositionX();
	if(xoffset<-360){
		s1->setPositionX(360);
	}else{
		xoffset-=1.6;
		s1->setPositionX(xoffset);
	}
	//!滚动图片2
	auto    s2=dynamic_cast<Sprite*>(s->getChildByTag(21));
	auto    x1offset=s2->getPositionX();
	if(x1offset<-360){
		s2->setPositionX(360);
	}else{
		x1offset-=1.6;
		s2->setPositionX(x1offset);
	}
	//!碰撞检测
	s->checkCollision();
	//!间断时间添加水管
	if(s->_time>1.8f){
		pipe::getInstance()->createPipeTop(350,620-rand()%200,s);
		s->_time=0.0f;
	}
	//!检查小鸟是否飞过水管
	for(auto i=s->pipes.begin();i!=s->pipes.end();++i){
			auto  flags=(int)(*i)->getUserData();
			if(flags==1992){
				if((*i)->getPositionX()<10){
					//!分数加一
					s->score++;
					//!将标志清除
					(*i)->setUserData(NULL);
					sprintf(s->a,"scores:%d",s->score);
					auto  label=	dynamic_cast<LabelTTF*>(s->getChildByTag(10));
					label->setString(s->a);
				}
			}
	}
	//！清除超出屏幕的水管
	for(auto i=s->pipes.begin();i!=s->pipes.end();){		
		auto  xpos=(*i)->getPositionX();
		if(xpos<=-45){
			(*i)->removeFromParent();
			i=s->pipes.erase(i);
		}else{
			i++;
		}
	}
}

void    gameStart::exit(HelloWorld*  s){
}

void    gameStart::handleEvent(HelloWorld* ){
	bird::getInstance()->setflying(true);
	bird::getInstance()->setFlySpeed(275.0f);
}


