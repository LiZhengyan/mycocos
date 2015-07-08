//
//  ShadeLayer.cpp
//  TaoQuan
//
//  Created by yongxinwan on 15/6/23.
//
//

#include "ShadeLayer.h"
#include "DataUtil.h"

USING_NS_CC;


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
    
    //currentLevel=1;//当前关卡
    
//    LayerColor* layerColor = LayerColor::create();
//    
//    layerColor->setColor(Color3B(0, 0, 0));
//    
//    layerColor->setOpacity(150);
//    
//    layerColor->setContentSize(CCSizeMake(visibleSize.width, visibleSize.height));
//    
//    this->addChild(layerColor);
    //添加过关
    Sprite* guoguanSP=Sprite::create("guoguan/guoguanSP.png");
    guoguanSP->setPosition(Vec2(visibleSize.width/2, visibleSize.height/1.3));
    guoguanSP->setScale(visibleSize.width/640);
    this->addChild(guoguanSP,2);
    
    //添加背景
    Sprite* blackBG=Sprite::create("guoguan/blackBG.png");
    blackBG->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2));
    blackBG->setScale(visibleSize.width/blackBG->getContentSize().width,visibleSize.height/blackBG->getContentSize().height);
    this->addChild(blackBG);
    Sprite* whiteBG=Sprite::create("guoguan/whiteBG.png");
    whiteBG->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2));
    whiteBG->setScale(visibleSize.width*2/3/whiteBG->getContentSize().width,visibleSize.height*2/3/whiteBG->getContentSize().height);
    this->addChild(whiteBG);
    
    
    //添加用时
    std::string sqlssssss = "select * from User where level=1";
    //取出数据库所有
    Sprite* yong=Sprite::create("guoguan/yongshi.png",Rect(0, 0, 58, 57));
    yong->setAnchorPoint(Vec2(0.5, 0.5));
    yong->setScale(visibleSize.width/640);
    yong->setPosition(Vec2(visibleSize.width/2-yong->getContentSize().width*1.7, visibleSize.height/2));
    this->addChild(yong,2);
    Sprite* shi=Sprite::create("guoguan/yongshi.png",Rect(58, 0, 58, 57));
    shi->setPosition(Vec2(visibleSize.width/2-yong->getContentSize().width*0.6, visibleSize.height/2));
    shi->setAnchorPoint(Vec2(0.5, 0.5));
    shi->setScale(visibleSize.width/640);
    this->addChild(shi,2);
    Sprite* miao=Sprite::create("guoguan/yongshi.png",Rect(116, 0, 58, 57));
    miao->setPosition(Vec2(visibleSize.width/2+yong->getContentSize().width*1.6, visibleSize.height/2));
    miao->setAnchorPoint(Vec2(0.5, 0.5));
    miao->setScale(visibleSize.width/640);
    this->addChild(miao,2);
    
    Value avm=DataUtil::getRow(sqlssssss);
    int time=avm.asValueMap()["useTime"].asInt();
    char timeChar[10];
    sprintf(timeChar, ":%d", time);
    
    
    LabelAtlas* labelTime = LabelAtlas::create(timeChar, "guoguan/shuzi.png", 28.0f, 41.0f, '0');
    //labelTime->setScale(visibleSize.width/640.0);
    labelTime->setAnchorPoint(Vec2(0.5,0.5));
    labelTime->setScale(visibleSize.width/640);
    labelTime->setPosition(Vec2(shi->getPositionX()+labelTime->getContentSize().width/2, visibleSize.height/2));
    this->addChild(labelTime, 2);
    //添加星星
    int starNum=0;
    if (time>=40) {
        starNum=3;
    }
    else if(time>=20&&time<40)
    {
        starNum=2;
    }else{
        starNum=1;
    }
    for (int i=0; i<3; i++) {
        
        Sprite* starL=Sprite::create("guoguan/starNoLight.png");
        if (i==1)
            starL->setPosition(Vec2(visibleSize.width/2-starL->getContentSize().width+i*(starL->getContentSize().width), visibleSize.height/1.6));
        else
            starL->setPosition(Vec2(visibleSize.width/2-starL->getContentSize().width+i*(starL->getContentSize().width), visibleSize.height/1.7));
        this->addChild(starL,2);
        starL->setScale(visibleSize.width/640);
        starVector.pushBack(starL);
    }
    for (int j=0; j<starNum; j++) {
        Sprite* star=(Sprite*)starVector.at(j);
        Texture2D* texture = TextureCache::sharedTextureCache()->addImage("guoguan/starLight.png");
        star->setTexture(texture);
    }

    
    //下一关按钮
    auto closeItem = MenuItemImage::create(
                                           "guoguan/nextLevel.png",
                                           "guoguan/nextLevel.png",
                                           CC_CALLBACK_1(ShadeLayer::menuNextCallback, this));
    
    closeItem->setPosition(Vec2(origin.x + visibleSize.width/2,
                                origin.y +visibleSize.height /4+ closeItem->getContentSize().height/2));
    
    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    menu->setScale(visibleSize.width/640);
    this->addChild(menu, 1);
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    
    listener->onTouchBegan = CC_CALLBACK_2(ShadeLayer::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(ShadeLayer::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(ShadeLayer::onTouchEnded, this);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    return true;
}



void ShadeLayer::menuNextCallback(Ref* pSender)
{
    //MoveBy* my=MoveBy::create(0.1, Vec2(0,visibleSize.height));
    //this->runAction(my);
    //currentLevel++;
    //UserDefault::getInstance()->setIntegerForKey("CurrentLevel", currentLevel);
    
    EventCustom _event("succeefulUI");
    char* buf=new char[10];
    sprintf(buf, "%d",10);
    _event.setUserData(buf);
    _eventDispatcher->dispatchEvent(&_event);
    CC_SAFE_DELETE_ARRAY(buf); 
    //this->removeFromParent();
    //this->removeAllChildrenWithCleanup(true);
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