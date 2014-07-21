#include "GamePause.h"
#include "HelloWorldScene.h"


GamePause * GamePause::singleton=NULL;

GamePause*  GamePause::getInstance(){

	if(singleton==NULL){
		singleton=new GamePause;

	}
	return  singleton;
}

void    GamePause::destory(){

	if(singleton!=NULL){
		delete  singleton;
		singleton=NULL;
	}
}


void	GamePause::enter(HelloWorld *){

}

void	GamePause::execute(HelloWorld*){


}

void	GamePause::exit(HelloWorld *){

}

void	GamePause::handleEvent(HelloWorld *){


}

