#ifndef  __GAME_OVER_H__
#define  __GAME_OVER_H__

#include "State.h"
class   HelloWorld;

//!ÓÎÏ·½áÊø×´Ì¬¿ØÖÆ

class GameOver:public  state<HelloWorld>
{
public:
		~GameOver(){}
		static   GameOver*  getInstance();
		static   void    destroy();

		virtual void   enter(HelloWorld *);
		virtual void   execute(HelloWorld*);
		virtual void   exit(HelloWorld *);
		virtual void   handleEvent(HelloWorld *);

private :
	static   GameOver *  singleton;
	GameOver(){}
};

#endif