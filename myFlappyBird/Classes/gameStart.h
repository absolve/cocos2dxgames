#ifndef  __GAME_START_H__
#define  __GAME_START_H__

#include "state.h"
class   HelloWorld;

class gameStart:public state<HelloWorld>
{
public:
	static gameStart*  getInstance();
	static void        destroy();

	void   enter(HelloWorld*);
	void   exit(HelloWorld*);
	void   execute(HelloWorld*);
	void   handleEvent(HelloWorld*);
private:
	static  gameStart *  instance;
};

#endif