#include "HelloWorldScene.h"
#include <math.h>

//#include "DataUtil.h"
#include "ResolvePicture.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}
static int timeNumber=60;static char Nmuber[10]="60";
// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();
    
    log("xxx= %f   yyy= %f",visibleSize.width,visibleSize.height);
//    gengUp=ResolvePicture::createResolvePicture();
//    duoUp=ResolvePicture::createResolvePicture();
//    youUp=ResolvePicture::createResolvePicture();
//    xiUp=ResolvePicture::createResolvePicture();
//    gengUp->initResolvePicture("tupian/1.png", 1111);
//    duoUp->initResolvePicture("duo.png", 1112);
//    youUp->initResolvePicture("you.png", 1113);
//    xiUp->initResolvePicture("xi.png", 1114);
//    spriteVector.pushBack(gengUp);
//    spriteVector.pushBack(duoUp);
//    spriteVector.pushBack(youUp);
//    spriteVector.pushBack(xiUp);

    for (int i=0; i<4; i++) {
        for (int j=0; j<3; j++) {
            ResolvePicture* rp=ResolvePicture::createResolvePicture();
            char name[20];
            sprintf(name, "tupian/%d.png",i*3+j+1);
            rp->initResolvePicture(name, i*3+j+1);
            rp->setPicturePosition(origin.x + rp->getContentSize().width*2*(i+1), origin.y + visibleSize.height*9/10-rp->getContentSize().height*2*(j+1));
            this->addChild(rp, 1);
            spriteVector.pushBack(rp);
        }
            
    }
    
    //倒计时
    label = LabelTTF::create(Nmuber, "fonts/Marker Felt.ttf", 24);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));
    this->addChild(label, 1);

//    auto sprite = Sprite::create("HelloWorld.png");
//
//    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
//
//    // add the sprite as a child to this layer
//    this->addChild(sprite, 0);
    
    this->schedule(schedule_selector(HelloWorld::updateTime), 1.0);
    this->scheduleUpdate();
    
    spriteTiao=Sprite::create("tiao1.png");
    spriteTiao->setRotation(45);
    spriteTiao->setTag(1);
    spriteTiao->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/4 + origin.y));
    spriteTiao->setAnchorPoint(Vec2(0.5,0));
    // add the sprite as a child to this layer
    this->addChild(spriteTiao, 0);
    
    //旋转
    auto rotate1= RotateTo::create(5.0f,-45.0);
    auto rotate2= RotateTo::create(5.0f,45.0);
    auto sequenceBG=Sequence::create(rotate1, rotate2, NULL);
    auto repeatBG=RepeatForever::create(sequenceBG);

    spriteTiao->runAction(repeatBG);
    
    //添加进度条
    powerProgress=ProgressTimer::create(Sprite::create("tiao2.png"));
    powerProgress->setTag(2);
    powerProgress->setRotation(45);
    
    powerProgress->setAnchorPoint(Vec2(0.5,0));
    powerProgress->setBarChangeRate(Point(0,1));
    powerProgress->setType(ProgressTimer::Type::BAR);
    powerProgress->setMidpoint(Point(0,0));
    powerProgress->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/4 + origin.y));
    powerProgress->setPercentage(0.0f);
    this->addChild(powerProgress,0);
    powerProgress->setVisible(false);
    
    //添加圈
    spriteQuan=Sprite::create("quan.png");
    spriteQuan->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/4 + origin.y));
    this->addChild(spriteQuan,1);
    
    //添加圈数
    quanNumber=10;
    
    numberLabel = LabelTTF::create("10", "fonts/Marker Felt.ttf", 24);

    numberLabel->setPosition(Vec2(origin.x + visibleSize.width*8/9,
                            origin.y + visibleSize.height/6));
    this->addChild(numberLabel, 1);
    //添加不动圈
    auto noMoveSprite = Sprite::create("quan.png");
    
    noMoveSprite->setPosition(Vec2(origin.x + visibleSize.width*8/9, origin.y + visibleSize.height/8 - numberLabel->getContentSize().height));
    this->addChild(noMoveSprite, 1);
    //添加大图
    /*bigPicture = Sprite::create("gdyx.png");
    
    bigPicture->setPosition(Vec2(origin.x + visibleSize.width/8+bigPicture->getContentSize().width/2, origin.y + visibleSize.height/8 + bigPicture->getContentSize().height));
    this->addChild(bigPicture, 1);
    
    gengDown=ResolvePicture::createResolvePicture();
    duoDown=ResolvePicture::createResolvePicture();
    youDown=ResolvePicture::createResolvePicture();
    xiDown=ResolvePicture::createResolvePicture();
    gengDown->initResolvePicture("geng.png", 1111);
    gengDown->setPicturePosition(origin.x + visibleSize.width/8, origin.y + visibleSize.height/8 - numberLabel->getContentSize().height);
    this->addChild(gengDown,1);
    gengDown->setVisible(false);
    bigPictureVector.pushBack(gengDown);
    
    duoDown->initResolvePicture("duo.png", 1112);
    duoDown->setPicturePosition(origin.x + visibleSize.width/8+duoDown->getContentSize().width, origin.y + visibleSize.height/8 - numberLabel->getContentSize().height);
    this->addChild(duoDown,1);
    duoDown->setVisible(false);
    bigPictureVector.pushBack(duoDown);
    
    youDown->initResolvePicture("you.png", 1113);
    youDown->setPicturePosition(origin.x + visibleSize.width/8, origin.y + visibleSize.height/8 - numberLabel->getContentSize().height-youDown->getContentSize().height);
    this->addChild(youDown,1);
    youDown->setVisible(false);
    bigPictureVector.pushBack(youDown);
    
    
    
    xiDown->initResolvePicture("xi.png", 1114);
    xiDown->setPicturePosition(origin.x + visibleSize.width/8+xiDown->getContentSize().width, origin.y + visibleSize.height/8 - numberLabel->getContentSize().height-youDown->getContentSize().height);
    this->addChild(xiDown,1);
    xiDown->setVisible(false);
    bigPictureVector.pushBack(xiDown);*/
    
    Sprite* quantu1 = Sprite::create("tupian/quantu1.png");
    quantu1->setScale(0.5);
    quantu1->setPosition(Vec2(origin.x + visibleSize.width/5, origin.y + visibleSize.height/5 + quantu1->getContentSize().height/2));
    this->addChild(quantu1, 1);
    
    ResolvePicture* sanjiao12=ResolvePicture::createResolvePicture();
    sanjiao12->initResolvePicture("tupian/12.png", 12);
    sanjiao12->setPicturePosition(origin.x + visibleSize.width/5, origin.y + visibleSize.height/5);
    this->addChild(sanjiao12,1);
    sanjiao12->setVisible(false);
    bigPictureVector.pushBack(sanjiao12);
    
    ResolvePicture* fang3=ResolvePicture::createResolvePicture();
    fang3->initResolvePicture("tupian/3.png", 3);
    fang3->setPicturePosition(origin.x + visibleSize.width/5, origin.y + visibleSize.height/5-fang3->getContentSize().height);
    this->addChild(fang3,1);
    fang3->setVisible(false);
    bigPictureVector.pushBack(fang3);
    
    
    ResolvePicture* sanjiao11=ResolvePicture::createResolvePicture();
    sanjiao11->initResolvePicture("tupian/11.png", 11);
    sanjiao11->setRotation(180);
    sanjiao11->setPicturePosition(origin.x + visibleSize.width/5, origin.y + fang3->getPositionY()-sanjiao11->getContentSize().height);
    this->addChild(sanjiao11,1);
    sanjiao11->setVisible(false);
    bigPictureVector.pushBack(sanjiao11);
    
    
    ResolvePicture* sanjiao2=ResolvePicture::createResolvePicture();
    sanjiao2->initResolvePicture("tupian/2.png", 2);
    sanjiao2->setRotation(135);
    sanjiao2->setPicturePosition(origin.x + visibleSize.width/5+sanjiao2->getContentSize().width, origin.y + visibleSize.height/5);
    this->addChild(sanjiao2,1);
    sanjiao2->setVisible(false);
    bigPictureVector.pushBack(sanjiao2);
    
    
    ResolvePicture* sanjiao10=ResolvePicture::createResolvePicture();
    sanjiao10->initResolvePicture("tupian/10.png", 10);
    sanjiao10->setRotation(-135);
    sanjiao10->setPicturePosition(origin.x + visibleSize.width/5-sanjiao10->getContentSize().width, origin.y + visibleSize.height/5);
    this->addChild(sanjiao10,1);
    sanjiao10->setVisible(false);
    bigPictureVector.pushBack(sanjiao10);
    
    
    
    //数据库测试
   // DataUtil::initDB("ok.db");
    
    //string sqlssss = "drop table user";
    //DataUtil::deleteData(sqlssss);
    
    //数据库中美有表格的话就先创建一个表格先
    //string sqlsss = "create table picture(id integer,name text,x integer,y integer,isCover bool)";
   // DataUtil::createTable(sqlsss,"picture");
    
    
    
    //像表格中插入数据
   // string sqlss = "insert into picture values(1,'1.png',200,300,'false')";
   // DataUtil::insertData(sqlss);
    /*string sqls = "delete from user where id=1";
     DataUtil::deleteData(sqls);*/
    /*string sqls = "update user set username='小猪猪猪猪' where id=1";
     DataUtil::updateData(sqls);*/
    
    
    /*string sqlsssss = "select count(*) from user";
     int a = DataUtil::getDataCount(sqlsssss);*/
//    string sqlssssss = "select * from picture where id=1";
//    Sprite *pp = Sprite::create();
//    DataUtil::getDataInfo(sqlssssss,pp);
//    //最后别忘了关闭数据库哦
//    
//    DataUtil::closeDB();
    
    
    
    auto _eventDispatcher=Director::getInstance()->getEventDispatcher();
    auto listener=EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchMoved=CC_CALLBACK_2(HelloWorld::onTouchMoved, this);
    listener->onTouchBegan=CC_CALLBACK_2(HelloWorld::onTouchBegan,this);
    listener->onTouchEnded=CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    return true;
}

void HelloWorld::updateTime(float dt)
{
    if (timeNumber>0) {
        timeNumber--;
        
        sprintf(Nmuber, "%d s",timeNumber);
        log("%s",Nmuber);
        label->setString(Nmuber);
    }
    log("-----Began-------jiaodu= %f baifenbi=%f ",spriteTiao->getRotation(),powerProgress->getPercentage());
}

bool HelloWorld::onTouchBegan(Touch *touch, Event *event)
{
    Director* director=Director::sharedDirector();
    director->getActionManager()->pauseTarget(HelloWorld::spriteTiao);
    
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

void HelloWorld::onTouchMoved(Touch *touch, Event *event)
{
    log("-----Move-------");
}

void HelloWorld::onTouchEnded(Touch *touch, Event *event)
{
    Director* director=Director::sharedDirector();
    director->getActionManager()->resumeTarget(HelloWorld::spriteTiao);
    //director->getActionManager()->resumeTarget(HelloWorld::powerProgress);
    powerProgress->setVisible(false);
    //移除进度条
    //this->removeChildByTag(2);
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
        MoveTo* quanMove=MoveTo::create(2.0f, Vec2(x, y));
        spriteQuan->runAction(quanMove);
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
        MoveTo* quanMove=MoveTo::create(2.0f, Vec2(x, y));
        spriteQuan->runAction(quanMove);
    
        quanNumber--;
        sprintf(quanNumberLabel, "%d",quanNumber);
        numberLabel->setString(quanNumberLabel);
        log("-----End-------x= %f y=%f ",x,y);
    }
    
}

void HelloWorld::onTouchCancelled(Touch *touch, Event *event)
{}

void HelloWorld::update(float dt)
{
    
    if (spriteQuan->getPositionX()==x&&spriteQuan->getPositionY()==y) {
        log("weizhi");
        spriteQuan->runAction(DelayTime::create(1.0f));
        if (quanNumber>0) {
            
            spriteQuan->setPosition(Vec2(visibleSize.width/2, visibleSize.height/4));
        }else{
            spriteQuan->setVisible(false);
        }
        
        
        for (int i=0; i<spriteVector.size(); i++) {
            ResolvePicture* menuItem=spriteVector.at(i);
            if (sqrt((x-menuItem->getPositionX())*(x-menuItem->getPositionX())+(y-menuItem->getPositionY())*(y-menuItem->getPositionY()))<=50.0) {
                log("***套住");
                
                Blink* menuItemBlink=Blink::create(2.0f, 5);
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


void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
