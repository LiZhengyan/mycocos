//
//  MenuScene.cpp
//  ctaoquan5
//
//  Created by lizhengyan on 15/6/29.
//
//

#include "MenuScene.h"
#include "MenuCtrlLayer.h"


bool MenuScene::init()
{
    
    
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin
    = Director::getInstance()->getVisibleOrigin();
    
    auto sprite = Sprite::create("HelloWorld.png");
    
//     position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    
//     add the sprite as a child to this layer
    this->addChild(sprite, 0);
    
    this->addChild(MenuCtrlLayer::create());

    
    return true;
}
