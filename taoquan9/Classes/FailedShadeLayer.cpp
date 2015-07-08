//
//  FailedShadeLayer.cpp
//  TaoQuan2
//
//  Created by yongxinwan on 15/6/30.
//
//

#include "FailedShadeLayer.h"
#include "GameScene.h"
#include "SelectLevel.h"

USING_NS_CC;


FailedShadeLayer* FailedShadeLayer::create()
{
    FailedShadeLayer* layer=new FailedShadeLayer();
    
    if (layer) {
        return layer;
    }
    return NULL;
}
bool FailedShadeLayer::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    //添加失败
    Sprite* failSP=Sprite::create("shibai/shibaiSP.png");
    failSP->setPosition(Vec2(visibleSize.width/2, visibleSize.height/1.3));
    failSP->setScale(visibleSize.width/640);
    this->addChild(failSP,2);
    
    //添加背景
    Sprite* blackBG=Sprite::create("shibai/blackBG.png");
    blackBG->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2));
    blackBG->setScale(visibleSize.width/blackBG->getContentSize().width,visibleSize.height/blackBG->getContentSize().height);
    this->addChild(blackBG);
    Sprite* whiteBG=Sprite::create("shibai/whiteBG.png");
    whiteBG->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2));
    whiteBG->setScale(visibleSize.width*2/3/whiteBG->getContentSize().width,visibleSize.height*2/3/whiteBG->getContentSize().height);
    this->addChild(whiteBG);
    
    //重新开始按钮
    auto restartItem = MenuItemImage::create(
                                           "shibai/restartBtn.png",
                                           "shibai/restartBtn.png",
                                           CC_CALLBACK_1(FailedShadeLayer::menuRestartCallback, this));
    
    restartItem->setPosition(Vec2(origin.x + visibleSize.width/2,
                                origin.y +visibleSize.height /3+ restartItem->getContentSize().height/2));
    auto selectLevelItem = MenuItemImage::create(
                                             "shibai/selectLevelBtn.png",
                                             "shibai/selectLevelBtn.png",
                                             CC_CALLBACK_1(FailedShadeLayer::menuSelectLevelCallback, this));
    
    selectLevelItem->setPosition(Vec2(origin.x + visibleSize.width/2,
                                  origin.y +visibleSize.height /2+ selectLevelItem->getContentSize().height/2));
    
    // create menu, it's an autorelease object
    auto menu = Menu::create(restartItem,selectLevelItem, NULL);
    menu->setPosition(Vec2::ZERO);
    menu->setScale(visibleSize.width/640);
    this->addChild(menu, 1);
    
    return true;
}

void FailedShadeLayer::menuRestartCallback(Ref* pSender)
{
    //MoveBy* my=MoveBy::create(0.1, Vec2(0,visibleSize.height));
    //this->runAction(my);
    //currentLevel++;
    //UserDefault::getInstance()->setIntegerForKey("CurrentLevel", currentLevel);
    
    this->removeFromParent();
    //Scene* gameScene=GameScene::createScene();
    //Director::getInstance()->replaceScene(gameScene);
    

    EventCustom _event("failedUI");
    _eventDispatcher->dispatchEvent(&_event);
}

void FailedShadeLayer::menuSelectLevelCallback(Ref* pSender)
{
    //MoveBy* my=MoveBy::create(0.1, Vec2(0,visibleSize.height));
    //this->runAction(my);
    //currentLevel++;
    //UserDefault::getInstance()->setIntegerForKey("CurrentLevel", currentLevel);
    
    this->removeFromParent();
    
    Scene* selectLevel=SelectLevel::createScene();
    Director::getInstance()->replaceScene(selectLevel);
}
