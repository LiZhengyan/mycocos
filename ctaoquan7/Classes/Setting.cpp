//
//  Setting.cpp
//  ctaoquan7
//
//  Created by lizhengyan on 15/7/8.
//
//

#include "Setting.h"
USING_NS_CC;

bool Setting::init()
{
    if ( !Scene::init() )
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
    
    return true;
}

void Setting::menuOkCallback(Ref*pSender)
{
    Director::getInstance()->popScene();
}
void Setting::menuSoundToggleCallback(Ref*pSender)
{
    
}
void Setting::menuMusicToggleCallback(Ref*pSender)
{}


void Setting::menuCallback(Ref* pSender)
{
    Director::getInstance()->replaceScene(HelloWorld::createScene());
}

void Setting::onEnter()
{
    Layer::onEnter();
    log("GameScene onEnter");
}

void Setting::onEnterTransitionDidFinish()
{
    Layer::onEnterTransitionDidFinish();
    log("GameScene onEnterTransitionDidFinish");
}

void Setting::onExit()
{
    Layer::onExit();
    log("GameScene onExit");
}

void Setting::onExitTransitionDidStart()
{
    Layer::onExitTransitionDidStart();
    log("GameScene onExitTransitionDidStart");
