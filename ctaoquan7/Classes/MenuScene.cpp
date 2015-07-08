//
//  MenuScene.cpp
//  ctaoquan7
//
//  Created by lizhengyan on 15/7/8.
//
//

#include "MenuScene.h"
#include "Setting.h"
USING_NS_CC;

bool MenuScene::init()
{
    if(! Scene::init())
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();
    
    Sprite *bg = Sprite::create("background.png");
    bg->setPosition(Point(origin.x + visibleSize.width/2,
                          origin.y +visibleSize.height /2));
    this->addChild(bg);
    
    //开始精灵
    Sprite *startSpriteNormal = Sprite::create("start-up.png");
    Sprite *startSpriteSelected =Sprite::create("start-up.png");
    
    MenuItemSprite*startMenuItem = MenuItemSprite::create(startSpriteNormal,
                                                          startSpriteSelected,
                                                          CC_CALLBACK_1(MenuScene::menuItemStartCallback,this));
    startMenuItem->setPosition(Director::getInstance()->convertToGL(Point(700,170)));
    
    //设置图片菜单
    MenuItemImage *settingMenuItem = MenuItemImage::create(
                                                           "setting-up.png",
                                                           "setting-up.png",
                                                           CC_CALLBACK_1(MenuScene::menuItemSettingCallback,this));
    settingMenuItem->setPosition(Director::getInstance()->convertToGL(Point(480,400)));
    
    //帮助图片菜单
    MenuItemImage *helpMenuItem = MenuItemImage::create(
                                                        "help-up.png",
                                                        "help-up.png",
                                                        CC_CALLBACK_1(MenuScene::
                                                                      menuItemHelpCallback,this));
    helpMenuItem->setPosition(Director::getInstance()->convertToGL(Point(860,480)));
    
    Menu*mu = Menu::create(startMenuItem, settingMenuItem, helpMenuItem, NULL);
    mu->setPosition(Point::ZERO);
    this->addChild(mu);
    return true;
}

void MenuScene::menuItemSettingCallback(Ref* pSender)
{
    auto sc = Setting::create();
    //Director::getInstance()->replaceScene(sc);
    Director::getInstance()->pushScene(sc);
}

void MenuScene::menuItemHelpCallback(Ref*pSender)
{
    MenuItem* item = (MenuItem*)pSender;
    log("TouchHelp %p", item);
}

void MenuScene::menuItemStartCallback(Ref*pSender)
{
    MenuItem* item = (MenuItem*)pSender;
    log("TouchStart %p", item);
}



