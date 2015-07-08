//
//  ShadeLayer.cpp
//  TaoQuan
//
//  Created by yongxinwan on 15/6/23.
//
//

#include "ShadeLayer.h"
USING_NS_CC;

ShadeLayer* ShadeLayer::create()
{
    ShadeLayer* layer=new ShadeLayer();
   
    if (layer) {
        return layer;
    }
    return NULL;
}
bool ShadeLayer::init() {
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto label = Label::createWithTTF("hello world", "fonts/Marker Felt.ttf", 24);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height /2));
    
    this->addChild(label, 1);
    
    auto sprite = Sprite::create("HelloWorld.png");
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    
    this->addChild(sprite, 0);
    this->setColor(Color3B(250, 250, 250));
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    
    listener->onTouchBegan = CC_CALLBACK_2(ShadeLayer::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(ShadeLayer::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(ShadeLayer::onTouchEnded, this);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    return true;
}
bool ShadeLayer::onTouchBegan( Touch* touch, Event* event )
{
    log("**began");
    
    return true;
}

void ShadeLayer::onTouchMoved( Touch* touch, Event* event )
{
    log("**move");
}

void ShadeLayer::onTouchEnded( Touch* touch, Event* event )
{
    
    log("**ended");
}