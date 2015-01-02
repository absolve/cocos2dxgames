#ifndef   __PIPE_H__
#define   __PIPE_H__

#include "CCSprite.h"

USING_NS_CC;

class  HelloWorld;
//!创建水管类

class pipe 
{
public:
		 static  pipe*   getInstance() ;
		 static  void    destroy();

		 //!创建一对水管
		 //!创建上水管
	     void createPipeTop(float,float,HelloWorld*);
		 //!创建下水管
		 void createPipeBottom(float,float,HelloWorld*);

private:
		   pipe(){ time=3.5f;   }
		   static   pipe*  instance;
		   //!水管移动的时间
		   float    time;
};

#endif