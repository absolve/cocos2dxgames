#include "Control.h"
#include "HelloWorldScene.h"



Control*   Control::instance=NULL;


Control*   Control::getInstance(){

	if(instance==NULL){
		instance=new  Control;
		return   instance;
	}
	return    instance;
}

void       Control::destroy(){

	if(instance!=NULL){
		delete  instance;
		instance=NULL;
	}

}

void       Control::init(HelloWorld*  h){
	ower=h;
}

