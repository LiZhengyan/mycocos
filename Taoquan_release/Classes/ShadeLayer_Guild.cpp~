//
//  ShadeLayer.cpp
//  TaoQuan
//
//  Created by yongxinwan on 15/6/23.
//
//

#include "ShadeLayer.h"
#include "DataUtil.h"
#include "SelectLevel.h"
USING_NS_CC;
#include"SimpleAudioEngine.h"
using namespace CocosDenshion;

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
    visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    //添加过关
    Sprite* guoguanSP=Sprite::create("guoguan/guoguanSP.png");
    guoguanSP->setPosition(Vec2(visibleSize.width/2, visibleSize.height*0.764));
    guoguanSP->setScale(visibleSize.width/640);
    this->addChild(guoguanSP,2);
    
    //添加背景
    Sprite* blackBG=Sprite::create("guoguan/blackBG.png");
    blackBG->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2));
    blackBG->setScale(visibleSize.width/blackBG->getContentSize().width,visibleSize.height/blackBG->getContentSize().height);
    this->addChild(blackBG);
    
    _level=UserDefault::getInstance()->getIntegerForKey("cLevel");
    //取出数据库所有
    char getUserSql[100];
    sprintf(getUserSql, "select * from User where level=%d",_level);
    Value avm=DataUtil::getRow(getUserSql);
    //添加星星
    int starNum=UserDefault::getInstance()->getIntegerForKey("cLevelXingNumber");
    int pattern=avm.asValueMap()["pattern"].asInt();
    for (int i=0; i<3; i++) {
        
        Sprite* starL=Sprite::create("guoguan/starNoLight.png");
        if (i==1)
            starL->setPosition(Vec2(visibleSize.width/2, visibleSize.height/1.6));
        else
            starL->setPosition(Vec2(visibleSize.width/2-visibleSize.width/5+i*visibleSize.width/5, visibleSize.height/1.7));
        this->addChild(starL,2);
        starL->setScale(visibleSize.width/640);
        starVector.pushBack(starL);
    }
    if (pattern==1) {
        for (int j=0; j<starNum; j++) {
            Sprite* star=(Sprite*)starVector.at(j);
            Texture2D* texture = TextureCache::sharedTextureCache()->addImage("shibai/yinXing.png");
            star->setTexture(texture);
        }

    }else{
        for (int j=0; j<starNum; j++) {
            Sprite* star=(Sprite*)starVector.at(j);
            Texture2D* texture = TextureCache::sharedTextureCache()->addImage("guoguan/starLight.png");
            star->setTexture(texture);
        }

    }
    //下一关银星按钮
    MenuItemImage* nextLevelItem;
    //本关金星模式按钮
    MenuItemImage* nextLevelGoldItem;
    //重新开始按钮
    MenuItemImage* restartItem;

    if (pattern==1&&starNum==3) {
        //下一关银星按钮
        nextLevelItem = MenuItemImage::create("guoguan/nextLevel.png",
                                                   "guoguan/selectedNextLevel.png",
                                                   CC_CALLBACK_1(ShadeLayer::menuNextCallback, this));
        
        nextLevelItem->setPosition(Vec2(origin.x + visibleSize.width*0.5,
                                        origin.y +visibleSize.height*0.382));
        //进入金星模式按钮
        nextLevelGoldItem = MenuItemImage::create(
                                              "guoguan/tiaozhanMoshi.png",
                                              "guoguan/selectedTiaozhanMoshi.png",
                                              CC_CALLBACK_1(ShadeLayer::menuThisLevelCallback, this));
        
        nextLevelGoldItem->setPosition(Vec2(origin.x + visibleSize.width*0.5,
                                        origin.y +visibleSize.height*0.46));
        auto menu = Menu::create(nextLevelItem,nextLevelGoldItem, NULL);
        menu->setPosition(Vec2::ZERO);
        menu->setScale(visibleSize.width/640);
        this->addChild(menu, 1);
    }else if((pattern==1&&starNum<3)||(pattern==2&&starNum<3)) {
        
        if (pattern==1&&starNum<3) {
            //添加提示
            Sprite* prompt=Sprite::create("guoguan/tishi.png");
            prompt->setPosition(Vec2(visibleSize.width/2,visibleSize.height*0.14));
            prompt->setScale(visibleSize.width*0.75/640.0);
            this->addChild(prompt);
        }
        
        //下一关银星按钮
        nextLevelItem = MenuItemImage::create(
                                              "guoguan/nextLevel.png",
                                              "guoguan/selectedNextLevel.png",
                                              CC_CALLBACK_1(ShadeLayer::menuNextCallback, this));
        
        nextLevelItem->setPosition(Vec2(origin.x + visibleSize.width*0.5,
                                        origin.y +visibleSize.height*0.382));

        
        //重新开始按钮
        restartItem = MenuItemImage::create(
                                              "shibai/restartBtn1.png",
                                              "shibai/selectedRestartBtn1.png",
                                              CC_CALLBACK_1(ShadeLayer::menuResatrtCallback, this));
        
        restartItem->setPosition(Vec2(origin.x + visibleSize.width*0.5,
                                        origin.y +visibleSize.height*0.46));
        auto menu = Menu::create(nextLevelItem,restartItem, NULL);
        menu->setPosition(Vec2::ZERO);
        menu->setScale(visibleSize.width/640);
        this->addChild(menu, 1);
        
    }else{
        //下一关银星按钮
        nextLevelItem = MenuItemImage::create(
                                              "guoguan/nextLevel.png",
                                              "guoguan/selectedNextLevel.png",
                                              CC_CALLBACK_1(ShadeLayer::menuNextCallback, this));
        
        nextLevelItem->setPosition(Vec2(origin.x + visibleSize.width*0.5,
                                        origin.y +visibleSize.height*0.382));
        auto menu = Menu::create(nextLevelItem, NULL);
        menu->setPosition(Vec2::ZERO);
        menu->setScale(visibleSize.width/640);
        this->addChild(menu, 1);
        
        

    }
   
    
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    
    listener->onTouchBegan = CC_CALLBACK_2(ShadeLayer::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(ShadeLayer::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(ShadeLayer::onTouchEnded, this);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    return true;
}

void ShadeLayer::menuResatrtCallback(Ref* pSender)
{
    bool isSound=UserDefault::getInstance()->getBoolForKey("isSound");
    if (isSound) {
        SimpleAudioEngine::getInstance()->playEffect("musicAndeffect/buttonEffect.wav");
    }
    Director::getInstance()->resume();//继续游戏
    
    this->removeFromParent();
    EventCustom _event("succeedResatrt");
    _eventDispatcher->dispatchEvent(&_event);
}

void ShadeLayer::menuNextCallback(Ref* pSender)
{
    bool isSound=UserDefault::getInstance()->getBoolForKey("isSound");
    if (isSound) {
        SimpleAudioEngine::getInstance()->playEffect("musicAndeffect/buttonEffect.wav");
    }
    
    
    //判断是否是最后一关
    if (_level==18) {
        Director::getInstance()->resume();
        Scene* selectScene=SelectLevel::createScene();
        Director::getInstance()->replaceScene(selectScene);
    }else{
        EventCustom _event("succeefulUI");
        char getPropSql[100];
        sprintf(getPropSql, "select * from Prop ");
        Value avm=DataUtil::getRow(getPropSql);
        int cieclePropNumber=avm.asValueMap()["circleProp"].asInt();
        char* buf=new char[10];
        sprintf(buf, "%d",cieclePropNumber);
        _event.setUserData(buf);
        _eventDispatcher->dispatchEvent(&_event);
        CC_SAFE_DELETE_ARRAY(buf);
    }
    
    
    this->removeFromParentAndCleanup(true);
   
}

void ShadeLayer::menuThisLevelCallback(Ref* pSender)
{
    bool isSound=UserDefault::getInstance()->getBoolForKey("isSound");
    if (isSound) {
        SimpleAudioEngine::getInstance()->playEffect("musicAndeffect/buttonEffect.wav");
    }
    DataUtil::updatePatternData(2,_level);//更新游戏模式
    UserDefault::getInstance()->setBoolForKey("isGengxin", true);
    
    EventCustom _event("ThisLevelGold");
    char getPropSql[100];
    sprintf(getPropSql, "select * from Prop ");
    Value avm=DataUtil::getRow(getPropSql);
    int cieclePropNumber=avm.asValueMap()["circleProp"].asInt();
    char* buf=new char[10];
    sprintf(buf, "%d",cieclePropNumber);
    _event.setUserData(buf);
    _eventDispatcher->dispatchEvent(&_event);
    CC_SAFE_DELETE_ARRAY(buf);
    this->removeFromParentAndCleanup(true);
}



bool ShadeLayer::onTouchBegan( Touch* touch, Event* event )
{
    log("**began");
    //自定义监听
    

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