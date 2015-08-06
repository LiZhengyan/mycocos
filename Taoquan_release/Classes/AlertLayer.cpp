//
//  AlertLayer.cpp
//  TaoQuan2
//
//  Created by yongxinwan on 15/7/14.
//
//

#include "AlertLayer.h"
#include "DataUtil.h"
#include "GameScene.h"
#include"SimpleAudioEngine.h"
using namespace CocosDenshion;
AlertLayer* AlertLayer::create()
{
    AlertLayer* layer=new AlertLayer();
    
    if (layer) {
        return layer;
    }
    return NULL;
}
bool AlertLayer::init() {
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
    //添加中间底板
//    Sprite* centerBG=Sprite::create("alertlayer/centerBG.png");
//    centerBG->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2));
//    centerBG->setScale(visibleSize.width/centerBG->getContentSize().width,visibleSize.height/centerBG->getContentSize().height);
//    this->addChild(centerBG,2);
    //添加消耗提示
    Sprite* xiaohaoSP=Sprite::create("alertlayer/useFile.png");
    xiaohaoSP->setPosition(Vec2(visibleSize.width/2,visibleSize.height*0.145));
    xiaohaoSP->setScale(visibleSize.width/640.0);
    this->addChild(xiaohaoSP,3);
    
    //添加开始按钮
    auto startItem = MenuItemImage::create("alertlayer/startBtn.png","alertlayer/selectStartBtn.png",
                                                     CC_CALLBACK_1(AlertLayer::menuConfirmCallback, this));
    
    //startItem->setScale(visibleSize.width/640);
    startItem->setPosition(Vec2(visibleSize.width*0.5,origin.y + visibleSize.height*0.56));
    auto backLastItem = MenuItemImage::create("alertlayer/backLastFile.png","alertlayer/selectedBackLastFile.png",CC_CALLBACK_1(AlertLayer::menuCancelCallback, this));
    //backLastItem->setScale(visibleSize.width/640);
    backLastItem->setPosition(Vec2(visibleSize.width*0.5,origin.y + visibleSize.height*0.46));

    auto menu = Menu::create(backLastItem,startItem, NULL);
    menu->setPosition(Vec2::ZERO);
    menu->setScale(visibleSize.width/640);
    this->addChild(menu, 3);
    
    //添加监听
    auto listener1=EventListenerTouchOneByOne::create();
    listener1->onTouchMoved=CC_CALLBACK_2(AlertLayer::onTouchMoved, this);
    listener1->onTouchBegan=CC_CALLBACK_2(AlertLayer::onTouchBegan,this);
    listener1->onTouchEnded=CC_CALLBACK_2(AlertLayer::onTouchEnded, this);
    listener1->setSwallowTouches(true);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener1,this);
    //_eventDispatcher->addEventListenerWithFixedPriority(listener1, -1);
    
    return true;
}

void AlertLayer::menuConfirmCallback(Ref* pSender)
{
    
    bool isSound=UserDefault::getInstance()->getBoolForKey("isSound");
    if (isSound) {
        SimpleAudioEngine::getInstance()->playEffect("musicAndeffect/buttonEffect.wav");
    }

    this->removeFromParent();
    //Director::getInstance()->resume();
    EventCustom _event("alertUI");
    _eventDispatcher->dispatchEvent(&_event);
}

void AlertLayer::menuCancelCallback(Ref* pSender)
{
    bool isSound=UserDefault::getInstance()->getBoolForKey("isSound");
    if (isSound) {
        SimpleAudioEngine::getInstance()->playEffect("musicAndeffect/buttonEffect.wav");
    }
    //Director::getInstance()->resume();
    this->removeFromParent();
    //点击返回上一存档按钮进入上一次存档的关卡
    int level=UserDefault::getInstance()->getIntegerForKey("comeInLevel");
    bool isFile=false;
    while (!isFile) {
        level--;
        char getUserSql[100];
        sprintf(getUserSql, "select * from User where level=%d",level);
        
        //从数据库中取出用户信息
        cocos2d::Value cv=DataUtil::getRow(getUserSql);
        isFile=cv.asValueMap()["isFile"].asBool();//从数据库取出是否存档的
        
    }
    UserDefault::getInstance()->setIntegerForKey("comeInLevel", level);
    Scene* gameScene=GameScene::createScene();
    Director::getInstance()->replaceScene(gameScene);

    
}

bool AlertLayer::onTouchBegan(Touch* touch, Event* event)
{
    return true;
}
void AlertLayer::onTouchMoved(Touch* touch, Event* event)
{
    
}
void AlertLayer::onTouchEnded(Touch* touch, Event* event)
{
    
    
}