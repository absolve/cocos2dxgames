#include "gameStart.h"
#include "HelloWorldScene.h"
#include "PlayerLayer.h"
#include "EnemyLayer.h"
#include "GameOver.h"
#include "GoodsLayer.h"

USING_NS_CC;

GameStart*   GameStart::singleton=NULL;

GameStart*   GameStart::getInstance(){

		if(singleton==NULL){

			singleton=new GameStart;
		}
		return  singleton;
}

void        GameStart::destory(){

		if(singleton!=NULL){
			delete  singleton;
			singleton=NULL;
		}
		
}

void		GameStart::enter(HelloWorld *s){


}

void		GameStart::execute(HelloWorld* s){

	//!清除超过屏幕的子弹
	auto    layer=s->playerlayer;
	for(auto  i=layer->bullets.begin();i!=layer->bullets.end();){
			if((*i)->getPositionY()>810){
				(*i)->removeFromParent();
				i=layer->bullets.erase(i);
			}else{

				i++;
			}
	}
	//!清除超过屏幕的敌机
	auto    layer1=s->enemylayer;
	for(auto i=layer1->enemyNum.begin();i!=layer1->enemyNum.end();){
		if((*i)->getPositionY()<-15){
			(*i)->removeFromParent();
			i=layer1->enemyNum.erase(i);
		}else{
			i++;
		}
	}
	//!消灭生命值低于零的死亡敌机
	for(auto  i=layer1->deadEnemy.begin();i!=layer1->deadEnemy.end();){
			auto  life=(int)(*i)->getUserData();
			if(life<0){
				(*i)->removeFromParent();
				i=layer1->deadEnemy.erase(i);
			}else{
				i++;
			}
	}
	//!滚动背景图片
	s->updateBackGround();
	////
	layer1->addTime(Director::getInstance()->getDeltaTime());
	//!添加敌机
	if(layer1->onTime()){
		layer1->createEnemy();
		layer1->setTime(0);
	}

	//!检测炸弹是否启动
	auto   goodslayer=s->goodslayer;
	if(goodslayer->getIsEexplosion()){
		//!计算所有被消灭的敌机分数
		int score1=0;
		for(auto i=layer1->enemyNum.begin();i!=layer1->enemyNum.end();){
					auto  point1=(*i)->getPositionY();
					if(point1<800){
						int  life=(int)(*i)->getUserData();
						score1+=life;
						//!设置死亡敌机消失时间
						life=50;
						(*i)->setUserData((void*)life);
						(*i)->stopAllActions();
						(*i)->getChildByTag(1)->setVisible(true);
						//!将死亡的敌机放到死亡容器中
						layer1->deadEnemy.pushBack(*i);
						i=layer1->enemyNum.erase(i);
					}else{
						i++;
					}
		}
		score1+=s->getScore();
		s->setScore(score1);
		goodslayer->setExplosion(false);
	}

	//!添加子弹
	layer->update(Director::getInstance()->getDeltaTime());
	/////////////////////////////////////////////////////
	////////////////////////////////////////////////////
	//!碰撞检测
	//先判断玩家是否与敌机相撞
	auto     es=layer1->enemyNum;
	for(auto  i=es.begin();i!=es.end();++i){
		  auto  rect1=(*i)->getBoundingBox();
		  auto  rect2=layer->getPlaneRect();
		  if(rect1.intersectsRect(rect2)){
			  //!跳转到游戏结束状态
			  layer->getPlayer()->getChildByTag(1)->setVisible(true);
			  s->changeState(GameOver::getInstance());
			  return;
		  }

	}
	//!子弹与敌机的碰撞检测
	for(auto  i=layer1->enemyNum.begin();i!=layer1->enemyNum.end();++i){
		for(auto y=layer->bullets.begin();y!=layer->bullets.end();){
				auto   rect1=(*i)->getBoundingBox();
				auto   rect2=(*y)->getBoundingBox();
				int    life=(int)(*i)->getUserData();
				if(rect1.intersectsRect(rect2)){
					(*y)->removeFromParent();
					y=layer->bullets.erase(y);
					life--;
					(*i)->setUserData((void*)life);
					s->scorePlus();
					s->updateScore();
				}else{
					y++;
				}

		}
	}
	//!将生命值为0的敌机添加到死亡列表里
	for(auto i=layer1->enemyNum.begin();i!=layer1->enemyNum.end();){
			int   life=(int)(*i)->getUserData();
			if(life<=0){
				life=50;
				(*i)->stopAllActions();
				(*i)->setUserData((void*)life);
				(*i)->getChildByTag(1)->setVisible(true);
				layer1->deadEnemy.pushBack(*i);
				i=layer1->enemyNum.erase(i);
			}else{
				i++;
			}
	}
	//!更新所有死亡的敌机集合
	for (auto i=layer1->deadEnemy.begin();i!=layer1->deadEnemy.end();++i){
				int  life=(int)(*i)->getUserData();
				life--;
				(*i)->setUserData((void*)life);
	}
}

void		GameStart::exit(HelloWorld * s){

	  //!暂停玩家层的定时器,停止所有的敌机动作,隐藏当前分数
	  auto   player=s->playerlayer;
	  //!清除所有的子弹
	  for(auto i=player->bullets.begin();i!=player->bullets.end();++i){
		  (*i)->pauseSchedulerAndActions();
	  }
	  //!停止飞机的动画
	  auto  s1=player->getPlayer();
	  s1->pauseSchedulerAndActions();
	  auto	 enemy=s->enemylayer;
	  for(auto  i=enemy->enemyNum.begin();i!=enemy->enemyNum.end();++i){
			(*i)->pauseSchedulerAndActions();
	  }
	  for(auto  i=enemy->deadEnemy.begin();i!=enemy->deadEnemy.end();++i){
			(*i)->removeFromParent();	
	  }
	  enemy->deadEnemy.clear();

}

void		GameStart::handleEvent(HelloWorld * s){

		auto   playerlayer1=s->playerlayer;
		auto   sprite=playerlayer1->getPlayer();
		auto   playerSprite=dynamic_cast<Sprite*>(sprite);
		//!获取坐标并判断是否超出屏幕
		auto   point1=playerSprite->getPosition();

		if(point1.x+s->XOffset<0 || point1.x+s->XOffset>480 
			|| point1.y+s->YOffset<0 || point1.y+s->YOffset>800){
				return;
		}
		point1.x+=s->XOffset;
		point1.y+=s->YOffset;
		playerSprite->setPosition(point1);

}