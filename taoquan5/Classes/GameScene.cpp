//
//  GameScene.cpp
//  TaoQuan
//
//  Created by yongxinwan on 15/6/16.
//
//

#include "GameScene.h"
#include "SelectLevel.h"
USING_NS_CC;

Scene* GameScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = GameScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}
static int timeNumber=60;static char Nmuber[10]="60";
// on "init" you need to initialize your instance
bool GameScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();
    
    isTouch=true;
    
    //返回按钮
    auto backItem = MenuItemImage::create(
                                           "gamescene/backButton.png",
                                           "gamescene/backButton.png",
                                           CC_CALLBACK_1(GameScene::menuCloseCallback, this));
    
    backItem->setPosition(Vec2(origin.x + backItem->getContentSize().width ,
                                origin.y+ visibleSize.height - backItem->getContentSize().height/2));
    
    // create menu, it's an autorelease object
    auto menu = Menu::create(backItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    
    //添加圈
    spriteQuan=Sprite::create("gamescene/quan.png");
    spriteQuan->setScale(spriteQuan->getContentSize().width*8/visibleSize.width);
    spriteQuan->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/4+visibleSize.height/100 + origin.y));
    this->addChild(spriteQuan,2);
    
    Sprite* spriteQuan2=Sprite::create("gamescene/cankaoxian.png");
    spriteQuan2->setScale(spriteQuan2->getContentSize().width*8/visibleSize.width);
    spriteQuan2->setPosition(Vec2(visibleSize.width/2+5 + origin.x, visibleSize.height/3.8 + origin.y));
    this->addChild(spriteQuan2,2);
    
//摆放物品
    for (int i=0; i<4; i++) {
        for (int j=0; j<3; j++) {
            ResolvePicture* rp=ResolvePicture::createResolvePicture();
            rp->setScale(spriteQuan->getContentSize().width*8/visibleSize.width);
            //log("xxx= %f   yyy= %f",visibleSize.width,rp->getContentSize().width);
            char name[20];
            sprintf(name, "gamescene/%d.png",i*3+j+1);
            rp->initResolvePicture(name, i*3+j+1);
            rp->setPicturePosition(origin.x+visibleSize.width/16+rp->getContentSize().width*2*(i+1), origin.y + visibleSize.height*9/10-rp->getContentSize().height*2*(j+1));
            this->addChild(rp, 1);
            spriteVector.pushBack(rp);
        }
        
    }
    
    //倒计时
    label = LabelTTF::create(Nmuber, "fonts/Marker Felt.ttf", 24);
    label->setColor(Color3B(249,194,111));
    label->setPosition(Vec2(origin.x + visibleSize.width/2,origin.y + visibleSize.height - label->getContentSize().height));
    this->addChild(label, 1);
    
    
    
    auto sprite = Sprite::create("gamescene/gameBG.png");
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    this->addChild(sprite, 0);
    
    
    this->schedule(schedule_selector(GameScene::updateTime), 1.0);
    this->scheduleUpdate();
    
    spriteTiao=Sprite::create("gamescene/zhizhenBG.png");
    spriteTiao->setScale(spriteTiao->getContentSize().width*8/visibleSize.width);
    spriteTiao->setRotation(45);
    spriteTiao->setTag(1);
    spriteTiao->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/4-spriteTiao->getContentSize().width/4 + origin.y));
    spriteTiao->setAnchorPoint(Vec2(0.5,0));
    // add the sprite as a child to this layer
    this->addChild(spriteTiao, 0);
    
    //旋转
    auto rotate1= RotateTo::create(3.0f,-45.0);
    auto rotate2= RotateTo::create(3.0f,45.0);
    auto sequenceBG=Sequence::create(rotate1, rotate2, NULL);
    auto repeatBG=RepeatForever::create(sequenceBG);
    
    spriteTiao->runAction(repeatBG);
    
    //添加进度条
    powerProgress=ProgressTimer::create(Sprite::create("gamescene/powerBar.png"));
    powerProgress->setScale(powerProgress->getContentSize().width*8/visibleSize.width);
    powerProgress->setTag(2);
    powerProgress->setRotation(45);
    
    powerProgress->setAnchorPoint(Vec2(0.5,0));
    powerProgress->setBarChangeRate(Point(0,1));
    powerProgress->setType(ProgressTimer::Type::BAR);
    powerProgress->setMidpoint(Point(0,0));
    powerProgress->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/4-powerProgress->getContentSize().width/4 + origin.y));
    powerProgress->setPercentage(0.0f);
    this->addChild(powerProgress,0);
    powerProgress->setVisible(false);
    
    
    //添加圈数
    quanNumber=100;
    
    numberLabel = LabelTTF::create("10", "fonts/Marker Felt.ttf", 24);
    
    numberLabel->setPosition(Vec2(origin.x + visibleSize.width*8/9,origin.y + visibleSize.height/6));
    this->addChild(numberLabel, 1);
    //添加不动圈
    auto noMoveSprite = Sprite::create("gamescene/quan.png");
    noMoveSprite->setScale(noMoveSprite->getContentSize().width*8/visibleSize.width);
    noMoveSprite->setPosition(Vec2(origin.x + visibleSize.width*8/9, origin.y + visibleSize.height/8 - numberLabel->getContentSize().height));
    this->addChild(noMoveSprite, 1);
    //添加大图
    
    Sprite* quantu1 = Sprite::create("quantu.png");
    quantu1->setScale(quantu1->getContentSize().width*2/visibleSize.width);
    quantu1->setPosition(Vec2(origin.x + visibleSize.width/5, origin.y + visibleSize.height/5 + quantu1->getContentSize().height/2));
    this->addChild(quantu1, 1);
    
    
  
    ResolvePicture* sanjiao12=ResolvePicture::createResolvePicture();
    sanjiao12->setScale(spriteQuan->getContentSize().width*8/visibleSize.width);
    sanjiao12->initResolvePicture("gamescene/4.png", 4);
    sanjiao12->setPicturePosition(origin.x + visibleSize.width/5, origin.y + visibleSize.height/5);
    this->addChild(sanjiao12,1);
    sanjiao12->setVisible(false);
    bigPictureVector.pushBack(sanjiao12);
    
    ResolvePicture* fang3=ResolvePicture::createResolvePicture();
    fang3->setScale(spriteQuan->getContentSize().width*8/visibleSize.width);
    fang3->initResolvePicture("gamescene/1.png", 1);
    fang3->setPicturePosition(origin.x + visibleSize.width/5, origin.y + visibleSize.height/5-fang3->getContentSize().height);
    this->addChild(fang3,1);
    fang3->setVisible(false);
    bigPictureVector.pushBack(fang3);
    
    
    ResolvePicture* sanjiao11=ResolvePicture::createResolvePicture();
    sanjiao11->setScale(spriteQuan->getContentSize().width*8/visibleSize.width);
    sanjiao11->initResolvePicture("gamescene/11.png", 11);
    sanjiao11->setRotation(180);
    sanjiao11->setPicturePosition(origin.x + visibleSize.width/5, origin.y + fang3->getPositionY()-sanjiao11->getContentSize().height);
    this->addChild(sanjiao11,1);
    sanjiao11->setVisible(false);
    bigPictureVector.pushBack(sanjiao11);
    
    
    ResolvePicture* sanjiao2=ResolvePicture::createResolvePicture();
    sanjiao2->setScale(spriteQuan->getContentSize().width*8/visibleSize.width);
    sanjiao2->initResolvePicture("gamescene/2.png", 2);
    sanjiao2->setRotation(180);
    sanjiao2->setPicturePosition(origin.x + visibleSize.width/5+sanjiao2->getContentSize().width, origin.y + visibleSize.height/5);
    this->addChild(sanjiao2,1);
    sanjiao2->setVisible(false);
    bigPictureVector.pushBack(sanjiao2);
    
    
    ResolvePicture* sanjiao10=ResolvePicture::createResolvePicture();
    sanjiao10->setScale(spriteQuan->getContentSize().width*8/visibleSize.width);
    sanjiao10->initResolvePicture("gamescene/7.png", 7);
    sanjiao10->setRotation(-135);
    sanjiao10->setPicturePosition(origin.x + visibleSize.width/5-sanjiao10->getContentSize().width, origin.y + visibleSize.height/5);
    this->addChild(sanjiao10,1);
    sanjiao10->setVisible(false);
    bigPictureVector.pushBack(sanjiao10);
    
    
    
    auto _eventDispatcher=Director::getInstance()->getEventDispatcher();
    auto listener=EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchMoved=CC_CALLBACK_2(GameScene::onTouchMoved, this);
    listener->onTouchBegan=CC_CALLBACK_2(GameScene::onTouchBegan,this);
    listener->onTouchEnded=CC_CALLBACK_2(GameScene::onTouchEnded, this);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    //_eventDispatcher->removeAllEventListeners();
    return true;
}

void GameScene::updateTime(float dt)
{
    if (timeNumber>0) {
        timeNumber--;
        
        sprintf(Nmuber, "%d s",timeNumber);
        log("%s",Nmuber);
        label->setString(Nmuber);
        
//        int t=timeNumber/50;
//        Sprite * sprite = CCSprite::create("gamescene/shuzi.png",Rect(0, 0, 59*t, 93));
//        sprite->setPosition(Vec2(origin.x + visibleSize.width/2,
//                                 origin.y + visibleSize.height*4/5));
//        this->addChild(sprite);
    }
    //log("-----Began-------jiaodu= %f baifenbi=%f ",spriteTiao->getRotation(),powerProgress->getPercentage());
    
    
    
}

bool GameScene::onTouchBegan(Touch *touch, Event *event)
{
    
    
    
    Director* director=Director::sharedDirector();
    director->getActionManager()->pauseTarget(GameScene::spriteTiao);
    
    powerProgress->setVisible(true);
    auto rotate3= RotateTo::create(0.01f,spriteTiao->getRotation());
    
    powerProgress->runAction(rotate3);
    ProgressFromTo* ptUp=ProgressFromTo::create(2, 0.0f, 100.0f);
    ProgressFromTo* ptDown=ProgressFromTo::create(2, 100.0f, 0.0f);
    auto sequencePG=Sequence::create(ptUp, ptDown, NULL);
    auto repeatPG=RepeatForever::create(sequencePG);
    powerProgress->runAction(repeatPG);
    
    return true;
}

void GameScene::onTouchMoved(Touch *touch, Event *event)
{
    log("-----Move-------");
}

void GameScene::onTouchEnded(Touch *touch, Event *event)
{
    Director* director=Director::sharedDirector();
    director->getActionManager()->resumeTarget(GameScene::spriteTiao);
    //director->getActionManager()->resumeTarget(HelloWorld::powerProgress);
    powerProgress->setVisible(false);
    //移除进度条
    //this->removeChildByTag(2);
    if (isTouch) {
        
        if (spriteTiao->getRotation()>0) {
            float rr=sqrt(visibleSize.width/2*visibleSize.width/2+visibleSize.height*3/4*visibleSize.height*3/4);
            
            float r=powerProgress->getPercentage()*0.01*rr;
            float x1=r*cos((90-spriteTiao->getRotation())*3.1415926/180);
            float y1=r*sin((90-spriteTiao->getRotation())*3.1415926/180);
            if (y1<0) {
                y1=-y1;
            }
            y=y1+visibleSize.height/4;
            x=x1+visibleSize.width/2;
            
            float s=sqrtf((x*x+y*y)-(spriteQuan->getPositionX()*getPositionX()+getPositionY()*getPositionY()));
            MoveTo* quanMove=MoveTo::create(s/200.0f, Vec2(x, y));
            auto ease=EaseSineOut::create(quanMove);
            spriteQuan->runAction(ease);
            quanNumber--;
            sprintf(quanNumberLabel, "%d",quanNumber);
            numberLabel->setString(quanNumberLabel);
            
            log("-----End-------x= %f y=%f ",x,y);
        }else{
            float rr=sqrt(visibleSize.width/2*visibleSize.width/2+visibleSize.height*3/4*visibleSize.height*3/4);
            float r=powerProgress->getPercentage()*0.01*rr;
            float x1=r*cos((90+spriteTiao->getRotation())*3.1415926/180);
            float y1=r*sin((90+spriteTiao->getRotation())*3.1415926/180);
            if (y1<0) {
                y1=-y1;
            }
            y=y1+visibleSize.height/4;
            x=visibleSize.width/2-x1;
            float s=sqrtf((x*x+y*y)-(spriteQuan->getPositionX()*getPositionX()+getPositionY()*getPositionY()));
            MoveTo* quanMove=MoveTo::create(s/200.0f, Vec2(x, y));
            auto ease=EaseSineOut::create(quanMove);
            spriteQuan->runAction(ease);
            
            quanNumber--;
            sprintf(quanNumberLabel, "%d",quanNumber);
            numberLabel->setString(quanNumberLabel);
            log("-----End-------x= %f y=%f ",x,y);
        }
        isTouch=false;
        
    }
    
    
    
}

void GameScene::onTouchCancelled(Touch *touch, Event *event)
{}

void GameScene::update(float dt)
{
    
    if (spriteQuan->getPositionX()==x&&spriteQuan->getPositionY()==y) {
        
        spriteQuan->runAction(DelayTime::create(1.0f));
        if (quanNumber>0) {
            
            spriteQuan->setPosition(Vec2(visibleSize.width/2, visibleSize.height/4));
            isTouch=true;
        }else{
            spriteQuan->setVisible(false);
        }
        
        
        for (int i=0; i<spriteVector.size(); i++) {
            ResolvePicture* menuItem=spriteVector.at(i);
            if (sqrt((x-menuItem->getPositionX())*(x-menuItem->getPositionX())+(y-menuItem->getPositionY())*(y-menuItem->getPositionY()))<=50.0) {
                log("***套住");
                
                Blink* menuItemBlink=Blink::create(1.0f, 3);
                menuItem->runAction(menuItemBlink);
                
                menuItem->isCover=true;
                if (menuItem->isCover) {
                    for (int j=0; j<bigPictureVector.size(); j++) {
                        ResolvePicture* rp=bigPictureVector.at(j);
                        if (rp->ID==menuItem->ID) {
                            rp->setVisible(true);
                        }
                    }
                }
                
            }else{
                log("没套住");
            }
            
            
            float juli=sqrt((x-menuItem->getPositionX())*(x-menuItem->getPositionX())+(y-menuItem->getPositionY())*(y-menuItem->getPositionY()));
            log("-----End-------liangdianjianjuli= %f liangbanjingzhicha=%f ",juli,(spriteQuan->getContentSize().width/2-menuItem->getContentSize().width/2));
        }
        
        
    }
    
    
}

void GameScene::menuCloseCallback(Ref* pSender)
{
    Scene* selectScene=SelectLevel::createScene();
    Director::getInstance()->replaceScene(selectScene);
}
