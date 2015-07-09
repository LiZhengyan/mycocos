//
//  Setting.cpp
//  ctaoquan7
//
//  Created by lizhengyan on 15/7/8.
//
//

#include "Setting.h"
#include "SystemHeader.h"
#include "cocos2d.h";
USING_NS_CC;

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


bool Setting::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();
    
    Sprite *bg = Sprite::create("setting-back.png");
    bg->setPosition(Point(origin.x + visibleSize.width/2,
                          origin.y +visibleSize.height /2));
    this->addChild(bg);
    
    //音效
    auto soundOnMenuItem = MenuItemImage::create(
                                                 "on.png",
                                                 "on.png");
    auto soundOffMenuItem = MenuItemImage::create(
                                                  "off.png",
                                                  "off.png");
    
    auto soundToggleMenuItem = MenuItemToggle::createWithCallback(
                                                                  CC_CALLBACK_1(Setting::menuSoundToggleCallback,this),
                                                                  soundOnMenuItem,
                                                                  soundOffMenuItem,
                                                                  NULL);
    soundToggleMenuItem->setPosition(Director::getInstance()->convertToGL(Point(818,220)));
    
    //音乐
    auto musicOnMenuItem =MenuItemImage::create(
                                                "on.png",
                                                "on.png");
    auto musicOffMenuItem =MenuItemImage::create(
                                                 "off.png",
                                                 "off.png");
    auto musicToggleMenuItem = MenuItemToggle::createWithCallback(
                                                                  CC_CALLBACK_1(Setting::menuMusicToggleCallback,this),
                                                                  musicOnMenuItem,
                                                                  musicOffMenuItem,
                                                                  NULL);
    musicToggleMenuItem->setPosition(Director::getInstance()->convertToGL(Point(818,362)));
    
    //Ok按钮
    auto okMenuItem = MenuItemImage::create(
                                            "ok-down.png",
                                            "ok-up.png",
                                            CC_CALLBACK_1(Setting::menuOkCallback, this));
    
    okMenuItem->setPosition(Director::getInstance()->convertToGL(Point(600,510)));
    
    Menu* mn = Menu::create(soundToggleMenuItem,
                            musicToggleMenuItem,okMenuItem,NULL);
    mn->setPosition(Point::ZERO);
    this->addChild(mn);
    
    auto defaults=UserDefault::getInstance();
    defaults->getBoolForKey(MUSIC_KEY)?musicToggleMenuItem->setSelectedIndex(0):
                                        musicToggleMenuItem->setSelectedIndex(1);
    
    defaults->getBoolForKey(SOUND_KEY)?musicToggleMenuItem->setSelectedIndex(0):
    musicToggleMenuItem->setSelectedIndex(1);
    
    
    
    
    
    return true;
}

Setting::~Setting(void)
{
    log("GameScene destructor");
}

void Setting::menuOkCallback(Ref*pSender)
{
    Director::getInstance()->popScene();
}



void Setting::menuSoundToggleCallback(Ref*pSender)
{
    auto  soundToggleMenuItem = (MenuItemToggle*) pSender;
    log("soundToggleMenuItem %d", soundToggleMenuItem->getSelectedIndex());
    
    UserDefault* defaults = UserDefault::getInstance();
    defaults->getBoolForKey(SOUND_KEY)?defaults->setBoolForKey(SOUND_KEY, false):defaults->setBoolForKey(SOUND_KEY,true);
    
    
}
void Setting::menuMusicToggleCallback(Ref*pSender)
{
    MenuItem* item = (MenuItem*)pSender;
    log("TouchMusic %p", item);
}


void Setting::menuCallback(Ref* pSender)
{
    Director::getInstance()->replaceScene(Setting::createScene());
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