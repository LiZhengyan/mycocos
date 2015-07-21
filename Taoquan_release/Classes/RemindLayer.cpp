//
//  RemindLayer.cpp
//  TaoQuan2
//
//  Created by yongxinwan on 15/7/17.
//
//

#include "RemindLayer.h"
#include "ShoppingMall.h"
RemindLayer* RemindLayer::create()
{
    RemindLayer* layer=new RemindLayer();
    
    if (layer) {
        return layer;
    }
    return NULL;
}
bool RemindLayer::init() {
    if ( !Layer::init() )
    {
        return false;
    }
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();
    
    //添加背景
    Sprite* blackBG=Sprite::create("remindlayer/bg.jpg");
    blackBG->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2));
    blackBG->setScale(visibleSize.width/blackBG->getContentSize().width,visibleSize.height/blackBG->getContentSize().height);
    this->addChild(blackBG);
    
    //添加不足提示
    Sprite* notEnoughSP=Sprite::create("remindlayer/notEnough.png");
    notEnoughSP->setPosition(Vec2(visibleSize.width/2,visibleSize.height*0.6));
    notEnoughSP->setScale(visibleSize.width/640.0);
    this->addChild(notEnoughSP,3);
    
    //添加确定和取消按钮
    auto confirmItem = MenuItemImage::create("remindlayer/confirm.png","remindlayer/selectedConfirm.png",
                                           CC_CALLBACK_1(RemindLayer::menuConfirmCallback, this));
    
    confirmItem->setScale(visibleSize.width/640);
    confirmItem->setPosition(Vec2(visibleSize.width*0.5,origin.y + visibleSize.height*0.5));
    auto cancelItem = MenuItemImage::create("remindlayer/cancel.png","remindlayer/selectedCancel.png",CC_CALLBACK_1(RemindLayer::menuCancelCallback, this));
    cancelItem->setScale(visibleSize.width/640);
    cancelItem->setPosition(Vec2(visibleSize.width*0.5,origin.y + visibleSize.height*0.4));
    
    auto menu = Menu::create(cancelItem,confirmItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 3);
    
    //添加监听
    auto listener1=EventListenerTouchOneByOne::create();
    listener1->onTouchMoved=CC_CALLBACK_2(RemindLayer::onTouchMoved, this);
    listener1->onTouchBegan=CC_CALLBACK_2(RemindLayer::onTouchBegan,this);
    listener1->onTouchEnded=CC_CALLBACK_2(RemindLayer::onTouchEnded, this);
    listener1->setSwallowTouches(true);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener1,this);
    //_eventDispatcher->addEventListenerWithFixedPriority(listener1, -1);
    
    return true;
}

void RemindLayer::menuConfirmCallback(Ref* pSender)
{
    this->removeFromParent();
    //跳转到商城
    Scene* shopScene=ShoppingMall::createScene();
    Director::getInstance()->pushScene(shopScene);
}

void RemindLayer::menuCancelCallback(Ref* pSender)
{
    //Director::getInstance()->resume();
    this->removeFromParent();
    
}

bool RemindLayer::onTouchBegan(Touch* touch, Event* event)
{
    return true;
}
void RemindLayer::onTouchMoved(Touch* touch, Event* event)
{
    
}
void RemindLayer::onTouchEnded(Touch* touch, Event* event)
{
    
    
}