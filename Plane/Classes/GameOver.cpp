#include "GameOver.h"
#include "HelloWorldScene.h"

GameOver*   GameOver::singleton=0;

GameOver*   GameOver::getInstance(){

	if(singleton==0){
		singleton =new GameOver();
	}

	return  singleton;
}

void     GameOver::destroy(){

	if(singleton!=0){
		delete singleton;
		singleton=NULL;
	}
}

void     GameOver::enter(HelloWorld *s){
	   //!显示最后得分面板
	  auto   fscore=s->fscore;
	  s->updateLastScore();
	  //!判断玩家分数是否超过最高分
	  if(s->getScore()>s->getHS()){
		  s->updateHighScore();
		  s->saveHighScore();
	  }

	  fscore->setVisible(true);
}

void	 GameOver::execute(HelloWorld*){

}

void	 GameOver::exit(HelloWorld *s){

	   auto   fscore=s->fscore;
	   fscore->setVisible(false);
	   s->setScore(0);
	   s->updateScore();

}

void	 GameOver::handleEvent(HelloWorld *){

}





