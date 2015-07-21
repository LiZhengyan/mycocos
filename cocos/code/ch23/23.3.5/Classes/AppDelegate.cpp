#include "AppDelegate.h"
#include "HelloWorldScene.h"

USING_NS_CC;


#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

#define bg_music_1   "sound/Jazz.aifc"
#define bg_music_2  "sound/Synth.aifc"
#define sound_1   "sound/Blip.caf"

#else

#define bg_music_1   "sound/Jazz.mp3"
#define bg_music_2  "sound/Synth.mp3"
#define sound_1   "sound/Blip.wav"

#endif


AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLView::create("My Game");
        director->setOpenGLView(glview);
    }
	
    // turn on display FPS
    director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
    auto scene = HelloWorld::createScene();

    // run
    director->runWithScene(scene);
	
	//初始化 音乐
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic(bg_music_1);
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic(bg_music_2);
	//初始化 音效
	SimpleAudioEngine::getInstance()->preloadEffect(sound_1);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
