#ifndef  __GAME_START_H__
#define  __GAME_START_H__

#include "State.h"
class    HelloWorld;

class GameStart:public  state<HelloWorld>
{
public:
	
	virtual ~GameStart(){}
	static   GameStart*   getInstance();
	static   void		  destory();

	virtual void   enter(HelloWorld *);
	virtual void   execute(HelloWorld*);
	virtual void   exit(HelloWorld *);
	virtual void   handleEvent(HelloWorld *);

private:
	static  GameStart *  singleton;
	GameStart(){}

};

#endif