//
//  PauseLayer.cpp
//  TaoQuan2
//
//  Created by yongxinwan on 15/7/3.
//
//

#include "PauseLayer.h"
#include "SelectLevel.h"
#include"SimpleAudioEngine.h"
using namespace CocosDenshion;
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
    blackBG=Sprite::create("guoguan/blackBG.png");
    blackBG->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2));
    blackBG->setScale(visibleSize.width/blackBG->getContentSize().width,visibleSize.height/blackBG->getContentSize().height);
    this->addChild(blackBG);
    
    //添加继续按钮和主菜单按钮
    restartItem = MenuItemImage::create("shibai/restartBtn1.png",
                                            "shibai/selectedRestartBtn1.png",CC_CALLBACK_1(PauseLayer::menuRestartCallback, this));
    restartItem->setScale(visibleSize.width/640);
    restartItem->setPosition(Vec2(visibleSize.width*0.5,origin.y + visibleSize.height*0.5));

    
    
    resumeItem = MenuItemImage::create("guoguan/resumeGame.png",
                                            "guoguan/selectedResumeGame.png",CC_CALLBACK_1(PauseLayer::menuResumeCallback, this));
    resumeItem->setScale(visibleSize.width/640);
    resumeItem->setPosition(Vec2(visibleSize.width*0.5,origin.y + visibleSize.height*0.6));
    
    backSelectLevelItem = MenuItemImage::create("shibai/selectLevelBtn.png","shibai/selectedSelectLevelBtn.png",
                                      CC_CALLBACK_1(PauseLayer::menuSelectLevelCallback, this));
    
    backSelectLevelItem->setScale(visibleSize.width/640);
    backSelectLevelItem->setPosition(Vec2(visibleSize.width*0.5,origin.y + visibleSize.height*0.4));
    

    auto menu = Menu::create(resumeItem,backSelectLevelItem,restartItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    
    
    
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

void PauseLayer::menuSelectLevelCallback(Ref* pSender)
{
    MenuItemImage* button=(MenuItemImage*)pSender;
    bool isSound=UserDefault::getInstance()->getBoolForKey("isSound");
    if (isSound) {
        SimpleAudioEngine::getInstance()->playEffect("musicAndeffect/buttonEffect.wav");
    }
    Director::getInstance()->resume();
    int cLevel=UserDefault::getInstance()->getIntegerForKey("cLevel");
    bool isGengxin=UserDefault::getInstance()->getBoolForKey("isGengxin");
    if(isGengxin)
    {
        DataUtil::updatePatternData(1,cLevel);
        UserDefault::getInstance()->setBoolForKey("isGengxin",false);
    }
    
    
    bool isReduceEnergy=UserDefault::getInstance()->getBoolForKey("isReduceEnergy");
    if (isReduceEnergy) {
        //减少体力
        char getUserSql[100];
        sprintf(getUserSql, "select * from Prop ");
        Value avm=DataUtil::getRow(getUserSql);
        int energyNumber=avm.asValueMap()["energy"].asInt();
        DataUtil::updatePropData("energy", energyNumber-1);
        
        UserDefault::getInstance()->setBoolForKey("isReduceEnergy", false);
    }
    
    auto btnSprite = Sprite::create("shibai/selectedSelectLevelBtn.png");
    button->setNormalSpriteFrame(btnSprite->getDisplayFrame());
    
    Scene* selectScene=SelectLevel::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(0.3, selectScene));
    

}

void PauseLayer::menuRestartCallback(Ref* pSender)
{
    MenuItemImage* button=(MenuItemImage*)pSender;
    bool isSound=UserDefault::getInstance()->getBoolForKey("isSound");
    if (isSound) {
        SimpleAudioEngine::getInstance()->playEffect("musicAndeffect/buttonEffect.wav");
    }
    
   
     //this->removeFromParent();
    auto btnSprite = Sprite::create("shibai/selectedRestartBtn1.png");
    button->setNormalSpriteFrame(btnSprite->getDisplayFrame());
    Director::getInstance()->resume();

    restartItem_Act=TargetedAction::create(restartItem,FadeTo::create(0.2, 0));
    resumeItem_Act=TargetedAction::create(resumeItem,FadeTo::create(0.2, 0));
    backSelectLevelItem_Act=TargetedAction::create(backSelectLevelItem,FadeTo::create(0.2, 0));
    blackBG->runAction( Sequence::create(Spawn::create(FadeTo::create(0.3, 0),
                                     restartItem_Act,
                                     resumeItem_Act,
                                                       backSelectLevelItem_Act,NULL),CallFunc::create(([=]{
        
                                                        this->removeFromParent();
        EventCustom _event("backRestartGame");_eventDispatcher->dispatchEvent(&_event);
                                                        })), NULL));

    
}


void PauseLayer::menuResumeCallback(Ref* pSender)
{
    MenuItemImage* button=(MenuItemImage*)pSender;
    bool isSound=UserDefault::getInstance()->getBoolForKey("isSound");
    if (isSound) {
        SimpleAudioEngine::getInstance()->playEffect("musicAndeffect/buttonEffect.wav");
    }
    Director::getInstance()->resume();
    auto btnSprite = Sprite::create("guoguan/selectedResumeGame.png");
    button->setNormalSpriteFrame(btnSprite->getDisplayFrame());
    Director::getInstance()->resume();
    
    restartItem_Act=TargetedAction::create(restartItem,FadeTo::create(0.2, 0));
    resumeItem_Act=TargetedAction::create(resumeItem,FadeTo::create(0.2, 0));
    backSelectLevelItem_Act=TargetedAction::create(backSelectLevelItem,FadeTo::create(0.2, 0));
    blackBG->runAction( Sequence::create(Spawn::create(FadeTo::create(0.3, 0),
                                                       restartItem_Act,
                                                       resumeItem_Act,
                                                       backSelectLevelItem_Act,NULL),CallFunc::create(([=]{this->removeFromParent();})), NULL));
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

}
