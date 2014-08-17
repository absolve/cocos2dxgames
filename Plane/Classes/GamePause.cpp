#include "GamePause.h"
#include "HelloWorldScene.h"
#include "PlayerLayer.h"
#include "EnemyLayer.h"

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

void	GamePause::exit(HelloWorld *s){

	//!»Ö¸´·É»úµÄ¶¯»­
	auto   player=s->playerlayer;
	for(auto i=player->bullets.begin();i!=player->bullets.end();++i){
		(*i)->resumeSchedulerAndActions();
	}
	auto  s1=player->getPlayer();
	s1->resumeSchedulerAndActions();

	auto	 enemy=s->enemylayer;
	for(auto  i=enemy->enemyNum.begin();i!=enemy->enemyNum.end();++i){
		(*i)->resumeSchedulerAndActions();
	}

}

void	GamePause::handleEvent(HelloWorld *){


}

