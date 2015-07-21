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
#include "SmartRes.h"
#include "RemindLayer.h"
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
    
    _clevel=UserDefault::getInstance()->getIntegerForKey("cLevel");
    char getUserSql[100];
    
    sprintf(getUserSql, "select * from User where level=%d",_clevel);
    cocos2d::Value cv=DataUtil::getRow(getUserSql);
    _isFile=cv.asValueMap()["isFile"].asBool();//从数据库取出是否存档的值
    
    //添加失败
    Sprite* failSP=Sprite::create("shibai/shibaiSP.png");
    failSP->setPosition(Vec2(visibleSize.width/2, visibleSize.height*0.76));
    failSP->setScale(visibleSize.width/640);
    this->addChild(failSP,2);
    //添加星星
    for (int i=0; i<3; i++) {
        
        Sprite* starL=Sprite::create("guoguan/starNoLight.png");
        if (i==1)
            starL->setPosition(Vec2(visibleSize.width/2, visibleSize.height/1.60));
        else
            starL->setPosition(Vec2(visibleSize.width/2-visibleSize.width/5+i*visibleSize.width/5, visibleSize.height/1.70));
        this->addChild(starL,2);
        starL->setScale(visibleSize.width/640);
    }

    
    
    auto restartItem = MenuItemImage::create();
    //添加提示
    if (!_isFile) {
        Sprite* xiaohaoTishi=Sprite::create("shibai/xiaohaoSP.png");
        xiaohaoTishi->setPosition(Vec2(visibleSize.width/2, visibleSize.height*0.15));
        xiaohaoTishi->setScale(visibleSize.width/640*0.7);
        this->addChild(xiaohaoTishi,2);
        
        restartItem = MenuItemImage::create(
                                                 "shibai/restartBtn.png",
                                                 "shibai/selectedRestartBtn.png",
                                                 CC_CALLBACK_1(FailedShadeLayer::menuRestartCallback, this));
        
    }
    else{
        restartItem = MenuItemImage::create(
                                                 "shibai/restartBtn1.png",
                                                 "shibai/selectedRestartBtn1.png",
                                                 CC_CALLBACK_1(FailedShadeLayer::menuRestartCallback, this));
    }
   
    //添加背景
    Sprite* blackBG=Sprite::create("shibai/blackBG.png");
    blackBG->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2));
    blackBG->setScale(visibleSize.width/blackBG->getContentSize().width,visibleSize.height/blackBG->getContentSize().height);
    this->addChild(blackBG);
    //重新开始按钮
//    auto restartItem = MenuItemImage::create(
//                                           "shibai/restartBtn.png",
//                                           "shibai/selectedRestartBtn.png",
//                                           CC_CALLBACK_1(FailedShadeLayer::menuRestartCallback, this));
    
    restartItem->setPosition(Vec2(origin.x + visibleSize.width/2,origin.y +visibleSize.height *0.46));
    //主界面按钮
    auto selectLevelItem = MenuItemImage::create(
                                             "shibai/selectLevelBtn.png",
                                             "shibai/selectedSelectLevelBtn.png",
                                             CC_CALLBACK_1(FailedShadeLayer::menuSelectLevelCallback, this));
    
    selectLevelItem->setPosition(Vec2(origin.x + visibleSize.width/2,
                                      origin.y +visibleSize.height *0.38));
    
    // create menu, it's an autorelease object
    auto menu = Menu::create(restartItem,selectLevelItem, NULL);
    menu->setPosition(Vec2::ZERO);
    menu->setScale(visibleSize.width/640);
    this->addChild(menu, 1);
    
    //添加监听
    auto listener1=EventListenerTouchOneByOne::create();
    listener1->onTouchMoved=CC_CALLBACK_2(FailedShadeLayer::onTouchMoved, this);
    listener1->onTouchBegan=CC_CALLBACK_2(FailedShadeLayer::onTouchBegan,this);
    listener1->onTouchEnded=CC_CALLBACK_2(FailedShadeLayer::onTouchEnded, this);
    listener1->setSwallowTouches(true);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener1,this);

    
    return true;
}


void FailedShadeLayer::menuRestartCallback(Ref* pSender)
{
    //MoveBy* my=MoveBy::create(0.1, Vec2(0,visibleSize.height));
    //this->runAction(my);
    //currentLevel++;
    //UserDefault::getInstance()->setIntegerForKey("CurrentLevel", currentLevel);
    Director::getInstance()->resume();//继续游戏
    if (!_isFile) {
        char getPropSql[100];
        sprintf(getPropSql, "select * from Prop ");
        Value avm=DataUtil::getRow(getPropSql);
        int filePropNumber=avm.asValueMap()["fileProp"].asInt();
        
        if (filePropNumber>0) {
            this->removeFromParent();
            DataUtil::updatePropData("fileProp", filePropNumber-1);
            
            DataUtil::updateIsFileData(true, _clevel);
            EventCustom _event("failedUI");
            _eventDispatcher->dispatchEvent(&_event);
        }else{
            Director::getInstance()->pause();
            //跳出提示
            if (getChildByName("remindLayer")==NULL) {
                RemindLayer* remindLayer=RemindLayer::create();
                remindLayer->init();
                this->addChild(remindLayer,100,"remindLayer");
            }
        }
    }else{
        this->removeFromParent();
        EventCustom _event("failedUI");
        _eventDispatcher->dispatchEvent(&_event);
    }
    
    
}

void FailedShadeLayer::menuSelectLevelCallback(Ref* pSender)
{
    Director::getInstance()->resume();//继续游戏
    int level =UserDefault::getInstance()->getIntegerForKey("comeInLevel");
    DataUtil::updateIsFileData(true, level);//本关是否存档
    this->removeFromParent();
    
    EventCustom _event("backSelectLevel");
    _eventDispatcher->dispatchEvent(&_event);
}

bool FailedShadeLayer::onTouchBegan(Touch* touch, Event* event)
{
    return true;
}
void FailedShadeLayer::onTouchMoved(Touch* touch, Event* event)
{
    
}
void FailedShadeLayer::onTouchEnded(Touch* touch, Event* event)
{
    
    
}
