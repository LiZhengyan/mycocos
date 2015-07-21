﻿#include "SettingScene.h"

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


Scene* Setting::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = Setting::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool Setting::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

	log("Setting init");
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    Sprite *bg = Sprite::create("setting-back.png");
    
    // position the label on the center of the screen
    bg->setPosition(Vec2(origin.x + visibleSize.width/2,
                             origin.y + visibleSize.height /2));
    this->addChild(bg);

	//音效
    auto soundOnMenuItem = MenuItemImage::create(
                             "on.png",
                             "on.png");
    auto soundOffMenuItem = MenuItemImage::create(
                             "off.png",
                             "off.png");
    
    auto soundToggleMenuItem = MenuItemToggle::createWithCallback(CC_CALLBACK_1(Setting::menuSoundToggleCallback, this), 
												soundOffMenuItem,
												soundOnMenuItem, 
												NULL);
	soundToggleMenuItem->setPosition(Director::getInstance()->convertToGL(Vec2(818, 220)));
    
    //音乐
    auto musicOnMenuItem  = MenuItemImage::create(
                             "on.png",
                             "on.png");
	auto musicOffMenuItem  = MenuItemImage::create(
                             "off.png",
                             "off.png");
    auto musicToggleMenuItem = MenuItemToggle::createWithCallback(CC_CALLBACK_1(Setting::menuMusicToggleCallback, this),
                                                    musicOffMenuItem,
                                                    musicOnMenuItem,
                                                    NULL );
	musicToggleMenuItem->setPosition(Director::getInstance()->convertToGL(Vec2(818, 362)));

    //Ok按钮
	auto okMenuItem  = MenuItemImage::create( 
                             "ok-down.png",
                             "ok-up.png",
							 CC_CALLBACK_1(Setting::menuOkCallback, this));

	okMenuItem->setPosition(Director::getInstance()->convertToGL(Vec2(600, 510)));

    Menu* mn = Menu::create(soundToggleMenuItem, musicToggleMenuItem,okMenuItem, NULL);
	mn->setPosition(Vec2::ZERO);
    this->addChild(mn);

    return true;
}

void Setting::menuOkCallback(Ref* pSender)
{
	Director::getInstance()->popScene();
	if (isEffect) {
		SimpleAudioEngine::getInstance()->playEffect(sound_1);
	}
}

void Setting::menuSoundToggleCallback(Ref* pSender)
{
	auto soundToggleMenuItem = (MenuItemToggle*)pSender;
	log("soundToggleMenuItem %d", soundToggleMenuItem->getSelectedIndex());

	if (isEffect) {
		SimpleAudioEngine::getInstance()->playEffect(sound_1);
	}

	if (soundToggleMenuItem->getSelectedIndex() == 1) {//选中状态Off -> On
		isEffect = false;
	} else {
		isEffect = true;
		SimpleAudioEngine::getInstance()->playEffect(sound_1);
	}
}


void Setting::menuMusicToggleCallback(Ref* pSender)
{
   	auto musicToggleMenuItem = (MenuItemToggle*)pSender;
	log("musicToggleMenuItem %d", musicToggleMenuItem->getSelectedIndex());
	
	if (musicToggleMenuItem->getSelectedIndex() == 1) {//选中状态Off -> On
		SimpleAudioEngine::getInstance()->stopBackgroundMusic(bg_music_2);
	} else {
		SimpleAudioEngine::getInstance()->playBackgroundMusic(bg_music_2);
	}
	if (isEffect) {
		SimpleAudioEngine::getInstance()->playEffect(sound_1);
	}
}


void Setting::onEnter()
{
	Layer::onEnter();
	log("Setting onEnter");
}

void Setting::onEnterTransitionDidFinish()
{
	Layer::onEnterTransitionDidFinish();
	log("Setting onEnterTransitionDidFinish");	
	isEffect = true;
	//播放
	SimpleAudioEngine::getInstance()->playBackgroundMusic(bg_music_2, true);
}

void Setting::onExit()
{
	Layer::onExit();
	log("Setting onExit");	
}

void Setting::onExitTransitionDidStart()
{
	Layer::onExitTransitionDidStart();
	log("Setting onExitTransitionDidStart");
}

void Setting::cleanup()
{
	Layer::cleanup();
	log("Setting cleanup");	
	//停止
	SimpleAudioEngine::getInstance()->stopBackgroundMusic(bg_music_2);
}