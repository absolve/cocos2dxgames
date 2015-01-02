#ifndef __GAMEREADY_H__
#define __GAMEREADY_H__
#include "state.h"

class  HelloWorld;

class gameReady :public state<HelloWorld>
{
public:
	~gameReady(void){}

	static   gameReady*  getInstance();
	static   void   destroy();
	void   enter(HelloWorld *);
	void   execute(HelloWorld*);
	void   exit(HelloWorld*);
	void   handleEvent(HelloWorld*  s);
private:
	gameReady(void){}
	static  gameReady*   instance;
};

#endif