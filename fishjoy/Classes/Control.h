#pragma once

class  HelloWorld;

//!保存helloworld的内存地址

class Control
{
public:


	static   Control*   getInstance();
	static   void       destroy();
	void     init(HelloWorld*);
	HelloWorld*   getScene(){return  ower;}

	~Control(){}
private:

	Control(){}
	static   Control*   instance;
	HelloWorld   *  ower;
};

