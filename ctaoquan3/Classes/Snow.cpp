//
//  Snow.cpp
//  ctaoquan3
//
//  Created by lizhengyan on 15/7/6.
//
//

#include "Snow.h"
#include "cocos2d.h"
USING_NS_CC;
#define MAX_COUNT 100

bool Snow::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    Size visibleSize=Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    list=__Array::createWithCapacity(MAX_COUNT);
    list->retain();
    
    for (int i=0; i<MAX_COUNT; ++i) {
        Sprite* sprite=Sprite::create("gamescene/starLight.png");
        this->list->addObject(sprite);
//        log("tid=%d",sprite->getch
    }

    log("list->count()=%zd",list->count());
    Ref* obj=nullptr;
    CCARRAY_FOREACH(list, obj){
        Sprite* sprite = (Sprite* )obj;
        int x =CCRANDOM_0_1()*visibleSize.width;
        int y=CCRANDOM_0_1()*visibleSize.height;
        
        int x1 =CCRANDOM_0_1()*visibleSize.width;
        int y1=CCRANDOM_0_1()*visibleSize.height;
        
        
        sprite->setPosition(Vec2(x, y));
        this->removeChild(sprite);
        auto moveto = MoveTo::create(10*CCRANDOM_0_1(), Vec2(x1,y1));
        sprite->runAction(moveto);
        this->addChild(sprite);
        
    }
    
    return true;
}

Snow::~Snow()
{
    this->list->removeAllObjects();
    CC_SAFE_RELEASE_NULL(this->list);
    
}
