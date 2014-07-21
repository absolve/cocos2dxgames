#ifndef  __GAME_PAUSE_H__
#define  __GAME_PAUSE_H__

#include "State.h"
class   HelloWorld;


class GamePause:public  state<HelloWorld>
{
public:

	virtual ~GamePause(){}
	static   GamePause*   getInstance();
	static   void		  destory();

	virtual void   enter(HelloWorld *);
	virtual void   execute(HelloWorld*);
	virtual void   exit(HelloWorld *);
	virtual void   handleEvent(HelloWorld *);


private:
	GamePause(){}
	static   GamePause*    singleton;
};

#endif