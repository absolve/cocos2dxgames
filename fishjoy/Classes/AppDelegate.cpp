#include "AppDelegate.h"
#include "HelloWorldScene.h"
#include "WelcomeScene.h"
#include "Control.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
	Control::destroy();

}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLView::create("My Game");

		//!设置观察窗口大小
		glview->setFrameSize(960,540);
		
        director->setOpenGLView(glview);
    }

	/*glview->setFrameZoomFactor(0.9f);*/
	//!设置目标分辨率
	glview->setDesignResolutionSize(960.0f,540.0f,ResolutionPolicy::EXACT_FIT );
	//glview->setDesignResolutionSize(512.0f,384.0f,kResolutionNoBorder);
    // turn on display FPS
    director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
    /*auto scene = HelloWorld::createScene();*/
	auto   scene=WelcomeScence::createScene();

    // run
    director->runWithScene(scene);

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
