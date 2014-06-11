#include "pipe.h"
#include "HelloWorldScene.h"

pipe*  pipe::instance=NULL;

pipe*  pipe::getInstance(){

	if(instance==NULL){
		instance =new pipe();
	}
	return  instance;

}

void   pipe::destroy(){

	if(instance!=NULL){
		delete  instance;
	}
}

void pipe::createPipeTop(float x,float y,HelloWorld *s){

	//!水管的上半部分
	auto   pipetop =Sprite::create("images/pipe.png");
	pipetop->setAnchorPoint(Point(0,0));
	pipetop->setPosition(x,y);
	pipetop->setScaleX(2.2);
	pipetop->setScaleY(2.2);
	//用这个标记来判断小鸟是否飞过一对水管
	int    i=1992;
	pipetop->setUserData((void*)i);

	//!水管的头部
	auto   pipe1=Sprite::create("images/pipetop.png");
	pipe1->setAnchorPoint(Point(0,0));
	pipe1->setScaleX(2.3);
	pipe1->setScaleY(2.3);

	auto  rect=pipe1->getBoundingBox();
	pipe1->setPosition(x-3,y-rect.getMaxY());

	s->addChild(pipetop,1);
	s->addChild(pipe1,1);


	//!添加动作
	auto   move=MoveTo::create(time,Point(-60,y));
	pipetop->runAction(move);
	pipe1->runAction(MoveTo::create(time,Point(-60-3,y-rect.getMaxY())));


	//!将水管的两个部分添加到容器中
	s->pipes.push_back(pipetop);
	s->pipes.push_back(pipe1);

	//!添加向上的水管
	createPipeBottom(x,y-rect.getMaxY()-100,s);

}

void pipe::createPipeBottom(float  x,float y,HelloWorld * s){

	auto   pipebottom =Sprite::create("images/pipe.png");
	pipebottom->setAnchorPoint(Point(0,0));
	pipebottom->setScaleX(2.2);
	pipebottom->setScaleY(2.2);


	auto   pipe1= Sprite::create("images/pipetop.png");
	pipe1->setAnchorPoint(Point(0,0));
	pipe1->setScaleX(2.3);
	pipe1->setScaleY(2.3);

	auto  rect=pipe1->getBoundingBox();
	pipe1->setPosition(x-3,y-rect.getMaxY());

	auto  rect1=pipebottom->getBoundingBox();

	pipebottom->setPosition(x,y-rect.getMaxY()-rect1.getMaxY());


	//!添加动作
	auto   move =MoveTo::create(time,Point(-60,y-rect.getMaxY()-rect1.getMaxY()));
	pipebottom->runAction(move);
	pipe1->runAction(MoveTo::create(time,Point(-60-3,pipe1->getPositionY())));

	//!将水管的两个部分添加到容器中
	s->pipes.push_back(pipebottom);
	s->pipes.push_back(pipe1);



	s->addChild(pipebottom,1);
	s->addChild(pipe1,1);

}








