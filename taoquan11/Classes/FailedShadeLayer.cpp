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
    
    int level=UserDefault::getInstance()->getIntegerForKey("comeInLevel");
    char getUserSql[100];
    sprintf(getUserSql, "select * from User where level=%d",level);
    cocos2d::Value cv=DataUtil::getRow(getUserSql);
    _isFile=cv.asValueMap()["isFile"].asBool();//从数据库取出是否存档的值
    
    //添加失败
    Sprite* failSP=Sprite::create("shibai/shibaiSP.png");
    failSP->setPosition(Vec2(visibleSize.width/2, visibleSize.height/1.3));
    failSP->setScale(visibleSize.width/640);
    this->addChild(failSP,2);
    //添加提示
//    if (!_isFile) {
        Sprite* xiaohaoTishi=Sprite::create("shibai/xiaohaoSP.png");
        xiaohaoTishi->setPosition(Vec2(visibleSize.width/2, visibleSize.height/1.5));
        xiaohaoTishi->setScale(visibleSize.width/640);
        this->addChild(xiaohaoTishi,2);
//    }
   
    //添加背景
    Sprite* blackBG=Sprite::create("shibai/blackBG.png");
    blackBG->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2));
    blackBG->setScale(visibleSize.width/blackBG->getContentSize().width,visibleSize.height/blackBG->getContentSize().height);
    this->addChild(blackBG);
//    Sprite* whiteBG=Sprite::create("shibai/whiteBG.png");
//    whiteBG->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2));
//    whiteBG->setScale(visibleSize.width*2/3/whiteBG->getContentSize().width,visibleSize.height*2/3/whiteBG->getContentSize().height);
//    this->addChild(whiteBG);
    
    //重新开始按钮
    auto restartItem = MenuItemImage::create(
                                           "shibai/restartBtn.png",
                                           "shibai/selectedRestartBtn.png",
                                           CC_CALLBACK_1(FailedShadeLayer::menuRestartCallback, this));
    
    restartItem->setPosition(Vec2(origin.x + visibleSize.width/2,
                                  origin.y +visibleSize.height *0.52));
    //主界面按钮
    auto selectLevelItem = MenuItemImage::create(
                                             "shibai/selectLevelBtn.png",
                                             "shibai/selectedSelectLevelBtn.png",
                                             CC_CALLBACK_1(FailedShadeLayer::menuSelectLevelCallback, this));
    
    selectLevelItem->setPosition(Vec2(origin.x + visibleSize.width/2,
                                      origin.y +visibleSize.height *smartRes_restartBtnHigh));
    
    // create menu, it's an autorelease object
    auto menu = Menu::create(restartItem,selectLevelItem, NULL);
    menu->setPosition(Vec2::ZERO);
    menu->setScale(visibleSize.width/640);
    this->addChild(menu, 1);
    
    return true;
}

void FailedShadeLayer::alertPropNotEnoughFunction()
{
    _propNotEnoughBG=Sprite::create("guoguan/whiteBG.png");
    _propNotEnoughBG->setScale(visibleSize.height*0.2/_propNotEnoughBG->getContentSize().height);
    _propNotEnoughBG->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2));
    this->addChild(_propNotEnoughBG,3);
    //是按钮
    _yesButton = MenuItemImage::create("selectlevel/Yes.png","selectlevel/Yes.png",
                                       CC_CALLBACK_1(FailedShadeLayer::menupropNotEnoughCallback, this));
    _yesButton->setTag(744);
    _yesButton->setPosition(Vec2(visibleSize.width*0.5 -_yesButton->getContentSize().width ,visibleSize.height/2-_yesButton->getContentSize().height));
    _yesButton->setScale(visibleSize.width*0.08/_yesButton->getContentSize().width);
    
    //否按钮
    _noButton = MenuItemImage::create("selectlevel/No.png","selectlevel/No.png",
                                      CC_CALLBACK_1(FailedShadeLayer::menupropNotEnoughCallback, this));
    _noButton->setTag(66);
    _noButton->setPosition(Vec2(visibleSize.width*0.5+_noButton->getContentSize().width ,visibleSize.height/2-_yesButton->getContentSize().height));
    _noButton->setScale(visibleSize.width*0.08/_noButton->getContentSize().width);
    
    _menu = Menu::create(_yesButton,_noButton, NULL);
    _menu->setPosition(Vec2::ZERO);
    this->addChild(_menu, 3);
}

void FailedShadeLayer::menupropNotEnoughCallback(Ref*pSender)
{
    MenuItemImage* button=(MenuItemImage*)pSender;
    if (button->getTag()==744) {
        log("进入商城");
    }else{
        this->removeChild(_propNotEnoughBG);
        this->removeChild(_menu);
    }
    
}

void FailedShadeLayer::menuRestartCallback(Ref* pSender)
{
    //MoveBy* my=MoveBy::create(0.1, Vec2(0,visibleSize.height));
    //this->runAction(my);
    //currentLevel++;
    //UserDefault::getInstance()->setIntegerForKey("CurrentLevel", currentLevel);
    
    if (!_isFile) {
        char getPropSql[100];
        sprintf(getPropSql, "select * from Prop ");
        Value avm=DataUtil::getRow(getPropSql);
        int filePropNumber=avm.asValueMap()["fileProp"].asInt();
        
        if (filePropNumber>1) {
            this->removeFromParent();
            DataUtil::updatePropData("fileProp", filePropNumber-1);
            
            EventCustom _event("failedUI");
            _eventDispatcher->dispatchEvent(&_event);
        }else{
            alertPropNotEnoughFunction();
        }
    }else{
        this->removeFromParent();
        EventCustom _event("failedUI");
        _eventDispatcher->dispatchEvent(&_event);
    }
    
    
}

void FailedShadeLayer::menuSelectLevelCallback(Ref* pSender)
{
    int level =UserDefault::getInstance()->getIntegerForKey("comeInLevel");
    DataUtil::updateIsFileData(true, level);//本关是否存档
    this->removeFromParent();
    
    EventCustom _event("backSelectLevel");
    _eventDispatcher->dispatchEvent(&_event);
    //Scene* selectLevel=SelectLevel::createScene();
    //Director::getInstance()->replaceScene(selectLevel);
}
