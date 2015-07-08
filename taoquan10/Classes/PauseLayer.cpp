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

    //添加背景
    Sprite* blackBG=Sprite::create("guoguan/blackBG.png");
    blackBG->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2));
    blackBG->setScale(visibleSize.width/blackBG->getContentSize().width,visibleSize.height/blackBG->getContentSize().height);
    this->addChild(blackBG);
    
    //添加暂停按钮
    //auto pauseItem = MenuItemImage::create("gamescene/pauseButton.png","gamescene/pauseButton.png",
                                      //CC_CALLBACK_1(PauseLayer::menuResumeCallback, this));
    
    //pauseItem->setScale(visibleSize.width/640);
    //pauseItem->setPosition(Vec2(visibleSize.width*0.9,origin.y + visibleSize.height*0.94));
    //auto resumeItem = MenuItemImage::create("gamescene/resumeButton.png","gamescene/resumeButton.png",CC_CALLBACK_1(PauseLayer::menuResumeCallback, this));
    //resumeItem->setScale(visibleSize.width*0.9/640);
    //resumeItem->setPosition(Vec2(visibleSize.width*0.5,origin.y + visibleSize.height*0.5));
    
    
    //auto menu = Menu::create(resumeItem, NULL);
   // menu->setPosition(Vec2::ZERO);
    //this->addChild(menu, 1);
    
    //添加监听
    auto listener1=EventListenerTouchOneByOne::create();
    listener1->onTouchMoved=CC_CALLBACK_2(PauseLayer::onTouchMoved, this);
    listener1->onTouchBegan=CC_CALLBACK_2(PauseLayer::onTouchBegan,this);
    listener1->onTouchEnded=CC_CALLBACK_2(PauseLayer::onTouchEnded, this);
    listener1->setSwallowTouches(true);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener1,this);
    //_eventDispatcher->addEventListenerWithFixedPriority(listener1, -1);
    
    return true;
}

bool PauseLayer::onTouchBegan(Touch* touch, Event* event)
{
    return true;
}
void PauseLayer::onTouchMoved(Touch* touch, Event* event)
{
    
}
void PauseLayer::onTouchEnded(Touch* touch, Event* event)
{
    Director::getInstance()->resume();
    this->removeFromParent();

}
