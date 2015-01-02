#include "AppDelegate.h"
#include "HelloWorldScene.h"
#include "welcomeScene.h"
#include "pipe.h"
#include "bird.h"
#include "gameReady.h"
#include "gameStart.h"
#include "gameEnd.h"

USING_NS_CC;

AppDelegate::AppDelegate() {
	
}

AppDelegate::~AppDelegate() 
{
	bird::destory();
	pipe::destroy();
	gameReady::destroy();
	gameStart::destroy();
	gameEnd::destroy();

}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLView::create("My Game");

		//设置调试窗口的大小
		glview->setFrameSize(360,640);

        director->setOpenGLView(glview);
    }

	
	//设置目标的分辨率
	glview->setDesignResolutionSize(360.0f,640.0f,ResolutionPolicy::EXACT_FIT);

    // turn on display FPS
    director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
   /* auto scene = HelloWorld::createScene();*/
	auto s1 =welcomeScene::createScene();
    // run
    director->runWithScene(s1);
    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
