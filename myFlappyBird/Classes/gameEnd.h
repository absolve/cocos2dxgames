#ifndef  __GAME_END_H__
#define  __GAME_END_H__

#include "state.h"
class  HelloWorld;

class gameEnd:public  state<HelloWorld>
{
public:
	static  gameEnd*  getInstance();
	static  void      destroy();

	void    enter(HelloWorld *);
	void    execute(HelloWorld*);
	void    exit(HelloWorld *);
	void    handleEvent(HelloWorld *);
private:
	static  gameEnd*  instance;
};

#endif