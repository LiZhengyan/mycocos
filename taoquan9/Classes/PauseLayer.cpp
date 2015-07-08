//
//  PauseLayer.cpp
//  TaoQuan2
//
//  Created by yongxinwan on 15/7/3.
//
//

#include "PauseLayer.h"
PauseLayer* PauseLayer::create()
{
    PauseLayer* layer=new PauseLayer();
    
    if (layer) {
        return layer;
    }
    return NULL;
}
bool PauseLayer::init() {
    if ( !Layer::init() )
    {
        return false;
    }
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();

    //添加暂停按钮
    auto pauseItem = MenuItemImage::create("gamescene/pauseButton.png","gamescene/pauseButton.png",
                                      CC_CALLBACK_1(PauseLayer::menuResumeCallback, this));
    
    pauseItem->setScale(visibleSize.width/640);
    pauseItem->setPosition(Vec2(visibleSize.width*0.9,origin.y + visibleSize.height*0.94));
    auto resumeItem = MenuItemImage::create("gamescene/resumeButton.png","gamescene/resumeButton.png",
                                      CC_CALLBACK_1(PauseLayer::menuResumeCallback, this));
    resumeItem->setScale(visibleSize.width/640);
    resumeItem->setPosition(Vec2(visibleSize.width*0.9,origin.y + visibleSize.height*0.94-resumeItem->getContentSize().height));
    
    
    auto menu = Menu::create(resumeItem,pauseItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    
    //添加监听
    auto callback=[](Touch*,Event*)
    {
        return true;
    };
    auto listener1=EventListenerTouchOneByOne::create();
    listener1->onTouchBegan=callback;
    listener1->setSwallowTouches(true);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener1,this);
    //_eventDispatcher->addEventListenerWithFixedPriority(listener1, -1);
    
    return true;
}

void PauseLayer::menuResumeCallback(Ref* pSender)
{
    Director::getInstance()->resume();
    this->removeFromParent();
    
}