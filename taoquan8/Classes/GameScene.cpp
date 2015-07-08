 //
//  GameScene.cpp
//  TaoQuan
//
//  Created by yongxinwan on 15/6/16.
//
//

#include "GameScene.h"
#include "SelectLevel.h"
#include "ShadeLayer.h"
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
static int timeNumber=60;static char Nmuber[10];
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
                                           "gamescene/backButton1.png",
                                           "gamescene/backButton1.png",
                                           CC_CALLBACK_1(GameScene::menuCloseCallback, this));
    
    backItem->setPosition(Vec2(origin.x + backItem->getContentSize().width ,
                                origin.y+ visibleSize.height - backItem->getContentSize().height/2-30));
    
    //帮助按钮
    auto helpItem = MenuItemImage::create(
                                          "gamescene/H.png",
                                          "gamescene/H.png",
                                          CC_CALLBACK_1(GameScene::menuCloseCallback, this));
    
    helpItem->setPosition(Vec2(origin.x + helpItem->getContentSize().width+ backItem->getContentSize().width ,
                               origin.y+ visibleSize.height - helpItem->getContentSize().height/2-30));
    //30 高度下调
    

    
//    //重新开始按钮
    auto pauseItem = MenuItemImage::create(
                                          "gamescene/pauseButton1.png",
                                          "gamescene/pauseButton1.png",
                                          CC_CALLBACK_1(GameScene::menuCloseCallback, this));
    
    pauseItem->setPosition(Vec2(origin.x + visibleSize.width- pauseItem->getContentSize().width ,
                               origin.y+ visibleSize.height - pauseItem->getContentSize().height/2-30));
    //30 高度下调
    
    
    
    
    //重新开始按钮
    auto restartItem = MenuItemImage::create(
                                             "gamescene/restartButton.png",
                                             "gamescene/restartButton.png",
                                             CC_CALLBACK_1(GameScene::menuCloseCallback, this));
    
    restartItem->setPosition(Vec2(origin.x + visibleSize.width- restartItem->getContentSize().width -pauseItem->getContentSize().width,
                                  origin.y+ visibleSize.height - restartItem->getContentSize().height/2-30));
    //30 高度下调
    
    auto menu = Menu::create(backItem,helpItem,restartItem,pauseItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    
    
   
    
    
    
    //添加圈
    spriteQuan=Sprite::create("gamescene/quan1.png");
    spriteQuan->setScale(0.7*visibleSize.width/640);
    spriteQuan->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/6 + origin.y));
    this->addChild(spriteQuan,3);
    //上
    Sprite* up=Sprite::create("gamescene/Up1.png");
    up->setScale(0.7*visibleSize.width/640);
    up->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/6 + origin.y));
    this->addChild(up,2);
    //下
    Sprite* down=Sprite::create("gamescene/Down1.png");
    down->setScale(0.7*visibleSize.width/640);
    down->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/6 + origin.y));
    this->addChild(down,1);
    
    /*
    for (int i=0; i<4; i++) {
        for (int j=0; j<3; j++) {
            
            //添加图片
            ResolvePicture* rp=ResolvePicture::createResolvePicture();
            rp->setScale(0.7*visibleSize.width/640);
            char name[20];
            
            int randNumber=random(1, 6);
            sprintf(name, "gamescene/%d.png",randNumber);
            rp->initResolvePicture(name, randNumber);
            rp->setPicturePosition(origin.x+visibleSize.width*0.2+visibleSize.width*0.2*i, origin.y + visibleSize.height*8/10-visibleSize.height*0.13*j);
            this->addChild(rp, 2);
            spriteVector.pushBack(rp);
            //底座
            auto dizuoTouying=Sprite::create("gamescene/foundationProjection.png");
            dizuoTouying->setScale(0.7*visibleSize.width/640);
            dizuoTouying->setPosition(Vec2(origin.x+visibleSize.width*0.2+visibleSize.width*0.2*(i), origin.y + visibleSize.height*8/10-visibleSize.height*0.13*j));
            //dizuoTouying->setScale(0.7);
            this->addChild(dizuoTouying,1);
            auto dizuo=Sprite::create("gamescene/foundation.png");
            dizuo->setScale(0.7*visibleSize.width/640);
            dizuo->setPosition(Vec2(origin.x+visibleSize.width*0.2+visibleSize.width*0.2*(i), origin.y + visibleSize.height*8/10-visibleSize.height*0.13*j));
            this->addChild(dizuo, 1);
        }
        
    }*/
    positionNumber.push_back(Value(2085));
    positionNumber.push_back(Value(8085));
    positionNumber.push_back(Value(2045));
    positionNumber.push_back(Value(8045));
    positionNumber.push_back(Value(5065));
    positionNumber.push_back(Value(5578));
    positionNumber.push_back(Value(4552));
    positionNumber.push_back(Value(3068));
    positionNumber.push_back(Value(7062));
    
    for (int i=0; i<9; i++) {
        
        int pX=positionNumber.at(i).asInt()/100;
        int pY=positionNumber.at(i).asInt()%100;
        
        //添加图片
        ResolvePicture* rp=ResolvePicture::createResolvePicture();
        rp->setScale(0.7*visibleSize.width/640);
        char name[20];
        int randNumber=random(1, 6);
        sprintf(name, "gamescene/%d.png",randNumber);
        rp->initResolvePicture(name, randNumber);
        rp->setPicturePosition(origin.x+visibleSize.width*pX*0.01, origin.y + visibleSize.height*pY*0.01);
        this->addChild(rp, 2);
        spriteVector.pushBack(rp);
        //底座
        auto dizuoTouying=Sprite::create("gamescene/foundationProjection1.png");
        dizuoTouying->setScale(0.7*visibleSize.width/640,0.9*visibleSize.width/640);
        dizuoTouying->setPosition(Vec2(origin.x+visibleSize.width*pX*0.01, origin.y + visibleSize.height*pY*0.01-40));
        //dizuoTouying->setScale(0.7);
        this->addChild(dizuoTouying,1);
        auto dizuo=Sprite::create("gamescene/foundation.png");
        dizuo->setScale(0.7*visibleSize.width/640);
        dizuo->setPosition(Vec2(origin.x+visibleSize.width*pX*0.01, origin.y + visibleSize.height*pY*0.01));
        this->addChild(dizuo, 1);
    }

    
    //背景
    auto sprite = Sprite::create("gamescene/gameBG3.png");
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    sprite->setScale(visibleSize.width/sprite->getContentSize().width);
    this->addChild(sprite, 0);
    //倒计时
    labelTime=LabelAtlas::create("60:", "gamescene/shuzi.png", 37.0f, 59.0f, '0');//加:是为了显示字母，0是开始字符
    //labelTime->setColor(Color3B(249,194,111));
    labelTime->setScale(visibleSize.width/640.0);
    labelTime->setPosition(Vec2(origin.x + visibleSize.width/2,origin.y + visibleSize.height - labelTime->getContentSize().height));
    
    this->addChild(labelTime, 1);
    
    this->schedule(schedule_selector(GameScene::updateTime), 1.0);
    this->scheduleUpdate();
    //指针
    spriteTiao=Sprite::create("gamescene/zhizhenBG.png");
    spriteTiao->setScale(0.7*visibleSize.width/640);
    spriteTiao->setRotation(45);
    spriteTiao->setTag(1);
    spriteTiao->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/5.4 + origin.y));
    spriteTiao->setAnchorPoint(Vec2(0.5,0));
    // add the sprite as a child to this layer
    this->addChild(spriteTiao, 0);
    
    //旋转
    auto rotate1= RotateTo::create(2.0f,-45.0);
    auto rotate2= RotateTo::create(2.0f,45.0);
    auto sequenceBG=Sequence::create(rotate1, rotate2, NULL);
    auto repeatBG=RepeatForever::create(sequenceBG);
    
    spriteTiao->runAction(repeatBG);
    
    //添加进度条
    powerProgress=ProgressTimer::create(Sprite::create("gamescene/powerBar.png"));
    powerProgress->setScale(0.7*visibleSize.width/640);
    powerProgress->setTag(2);
    powerProgress->setRotation(45);
    
    powerProgress->setAnchorPoint(Vec2(0.5,0));
    powerProgress->setBarChangeRate(Point(0,1));
    powerProgress->setType(ProgressTimer::Type::BAR);
    powerProgress->setMidpoint(Point(0,0));
    powerProgress->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/5.4 + origin.y));
    powerProgress->setPercentage(0.0f);
    this->addChild(powerProgress,0);
    powerProgress->setVisible(false);
    
    
    //添加圈数
    quanNumber=10;
    
    
    labelNumber = LabelAtlas::create(":10", "gamescene/shuzi2.png", 26.0f, 41.0f, '0');
    labelNumber->setScale(visibleSize.width/640.0);
    labelNumber->setPosition(Vec2(origin.x + visibleSize.width*0.8,origin.y + visibleSize.height/6));
    this->addChild(labelNumber, 1);
    //添加不动圈
    auto noMoveSprite = Sprite::create("gamescene/huan.png");
    noMoveSprite->setScale(visibleSize.width/640.0);
    noMoveSprite->setPosition(Vec2(origin.x + visibleSize.width*0.8, origin.y + visibleSize.height/8 - labelNumber->getContentSize().height));
    this->addChild(noMoveSprite, 1);
    
    
    //添加大图
    Sprite* quantu1 = Sprite::create("gamescene/11a.png");
    quantu1->setScale(quantu1->getContentSize().width*2/visibleSize.width);
    quantu1->setPosition(Vec2(origin.x + visibleSize.width/5, origin.y + visibleSize.height/6));
    this->addChild(quantu1, 1);
    //添加隐藏图
    ResolvePicture* sanjiaoUp=ResolvePicture::createResolvePicture();
    sanjiaoUp->setScale(spriteQuan->getContentSize().width*1.5/visibleSize.width);
    sanjiaoUp->initResolvePicture("gamescene/111.png", 1);
    sanjiaoUp->setPicturePosition(origin.x + visibleSize.width/5, origin.y + visibleSize.height/6+spriteQuan->getContentSize().height/4);
    this->addChild(sanjiaoUp,1);
    sanjiaoUp->setVisible(false);
    bigPictureVector.pushBack(sanjiaoUp);
    
    ResolvePicture* fang=ResolvePicture::createResolvePicture();
    fang->setScale(spriteQuan->getContentSize().width*1.5/visibleSize.width);
    fang->initResolvePicture("gamescene/333.png", 3);
    fang->setPicturePosition(origin.x + visibleSize.width/5, origin.y + visibleSize.height/6);
    this->addChild(fang,1);
    fang->setVisible(false);
    bigPictureVector.pushBack(fang);
    
    ResolvePicture* sanjiaoDown=ResolvePicture::createResolvePicture();
    sanjiaoDown->setScale(spriteQuan->getContentSize().width*1.5/visibleSize.width);
    sanjiaoDown->initResolvePicture("gamescene/111.png", 1);
    sanjiaoDown->setRotation(180);
    sanjiaoDown->setPicturePosition(origin.x + visibleSize.width/5, origin.y + visibleSize.height/7);
    this->addChild(sanjiaoDown,1);
    sanjiaoDown->setVisible(false);
    bigPictureVector.pushBack(sanjiaoDown);
    

//    ShadeLayer* layer=ShadeLayer::create();
//    layer->init();
//    this->addChild(layer,100);
    
    
    
    
    //添加监听
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
//设置图片的摆放位置
void GameScene::setPicturePosition(int num)
{
    
    positionNumber.push_back(Value(2060));
    positionNumber.push_back(Value(8060));
    positionNumber.push_back(Value(2020));
    positionNumber.push_back(Value(8020));
    positionNumber.push_back(Value(5010));
    positionNumber.push_back(Value(3030));
    positionNumber.push_back(Value(5010));
    positionNumber.push_back(Value(7030));
    positionNumber.push_back(Value(5030));
    
    for (int i=0; i<9; i++) {
        
        int pX=positionNumber.at(i).asInt()/100;
        int pY=positionNumber.at(i).asInt()%100;

            //添加图片
            ResolvePicture* rp=ResolvePicture::createResolvePicture();
            rp->setScale(0.7*visibleSize.width/640);
            char name[20];
            int randNumber=random(1, 6);
            sprintf(name, "gamescene/%d.png",randNumber);
            rp->initResolvePicture(name, randNumber);
            rp->setPicturePosition(origin.x+visibleSize.width*pX*0.01, origin.y + visibleSize.height*0.01);
            this->addChild(rp, 2);
            spriteVector.pushBack(rp);
            //底座
            auto dizuoTouying=Sprite::create("gamescene/foundationProjection.png");
            dizuoTouying->setScale(0.7*visibleSize.width/640);
            dizuoTouying->setPosition(Vec2(origin.x+visibleSize.width*pX*0.01, origin.y + visibleSize.height*0.01));
            //dizuoTouying->setScale(0.7);
            this->addChild(dizuoTouying,1);
            auto dizuo=Sprite::create("gamescene/foundation.png");
            dizuo->setScale(0.7*visibleSize.width/640);
            dizuo->setPosition(Vec2(origin.x+visibleSize.width*pX*0.01, origin.y + visibleSize.height*0.01));
            this->addChild(dizuo, 1);

        
    }

}

void GameScene::updateTime(float dt)
{
    if (timeNumber>0) {
        timeNumber--;
        
        sprintf(Nmuber, "%d:",timeNumber);
        log("%s",Nmuber);
        labelTime->setString(Nmuber);
        
    }
    
}

bool GameScene::onTouchBegan(Touch *touch, Event *event)
{
    
    
    
    Director* director=Director::sharedDirector();
    director->getActionManager()->pauseTarget(GameScene::spriteTiao);
    
    powerProgress->setVisible(true);
    auto rotate3= RotateTo::create(0.01f,spriteTiao->getRotation());
    
    powerProgress->runAction(rotate3);
    ProgressFromTo* ptUp=ProgressFromTo::create(1, 0.0f, 100.0f);
    ProgressFromTo* ptDown=ProgressFromTo::create(1, 100.0f, 0.0f);
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
            MoveTo* quanMove=MoveTo::create(s/400.0f, Vec2(x, y));
            auto ease=EaseSineOut::create(quanMove);
            spriteQuan->runAction(ease);
            quanNumber--;
            sprintf(quanNumberLabel, ":%d",quanNumber);
            labelNumber->setString(quanNumberLabel);
            
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
            MoveTo* quanMove=MoveTo::create(s/400.0f, Vec2(x, y));
            auto ease=EaseSineOut::create(quanMove);
            spriteQuan->runAction(ease);
            
            quanNumber--;
            sprintf(quanNumberLabel, ":%d",quanNumber);
            labelNumber->setString(quanNumberLabel);
            log("-----End-------x= %f y=%f ",x,y);
        }
        isTouch=false;
        
    }
    
    
    
}

void GameScene::onTouchCancelled(Touch *touch, Event *event)
{}


void GameScene::update(float dt)
{
    //判断圈是否到达目的地
    if (spriteQuan->getPositionX()==x&&spriteQuan->getPositionY()==y) {
        
        for (int i=0; i<spriteVector.size(); i++) {
            
            //判断是否套住
            ResolvePicture* menuItem=spriteVector.at(i);
            if (sqrt((x-menuItem->getPositionX())*(x-menuItem->getPositionX())+(y-menuItem->getPositionY())*(y-menuItem->getPositionY()))<=50.0) {

                menuItem->isCover=true;
                Blink* menuItemBlink=Blink::create(1.0f, 2);
                menuItem->runAction(menuItemBlink);
                spriteQuan->setPosition(Vec2(visibleSize.width/2, visibleSize.height/4));
                isTouch=true;

                if (menuItem->isCover) {
                
                    for (int j=0; j<bigPictureVector.size(); j++) {
                        ResolvePicture* rp=bigPictureVector.at(j);
                        if (rp->ID==menuItem->ID) {
                            //添加帧动画
                            Animation* animation=Animation::create();
                            for (int i=0; i<3; i++) {
                                char name[30];
                                sprintf(name, "gamescene/dizuo%d.png",i+1);
                                animation->addSpriteFrameWithFileName(name);
                            }
                            animation->setDelayPerUnit(1.0f / 3.0f); // 这个动画包含14帧，将会持续2.8秒.
                            animation->setRestoreOriginalFrame(true); // 14帧播放完之后返回到第一帧
                            
                            Animate *action = Animate::create(animation);
                            auto dizuo=Sprite::create("gamescene/dizuo1.png");
                            dizuo->setPosition(Vec2(menuItem->getPositionX(),menuItem->getPositionY()));
                            
                            this->addChild(dizuo,0);
                            dizuo->runAction(action);  // 运行精灵对象
                            //dizuo->setVisible(false);
                            //换图片
                            menuItem->changPicture();
                            //显示套住的图片
                            rp->setVisible(true);
                            bigPictureVector.eraseObject(rp);
                            break;
                        }
                        
                        
                    }
                }
                menuItem->isCover=false;
                spriteQuan->setPosition(Vec2(visibleSize.width/2, visibleSize.height/6));
                isTouch=true;
                break;
            }else{
                log("没套住");
                if(i==8)
                {
                    spriteQuan->runAction(Sequence::create(Blink::create(1.0f, 2),MoveTo::create(0.01f, Vec2(visibleSize.width/2, visibleSize.height/6)), NULL));
                }
                isTouch=true;
            }

        }
        x=0.0;y=0.0;
        
        
//        if (quanNumber>0) {
//            
//            spriteQuan->setPosition(Vec2(visibleSize.width/2, visibleSize.height/6));
//            isTouch=true;
//        }else{
//            spriteQuan->setVisible(false);
//        }
    }
    //套完所有图片执行
    if (bigPictureVector.size()==0) {
        ShadeLayer* layer=ShadeLayer::create();
        layer->init();
        this->addChild(layer,100);
        log("%%%%%%%%%%%%");
    }
}

void GameScene::menuCloseCallback(Ref* pSender)
{
    Scene* selectScene=SelectLevel::createScene();
    Director::getInstance()->replaceScene(selectScene);
}
