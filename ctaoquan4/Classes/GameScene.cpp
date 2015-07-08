//
//  GameScene.cpp
//  ctaoquan4
//
//  Created by lizhengyan on 15/6/18.
//
//

#include "GameScene.h"
#include "HelloWorldScene.h"

USING_NS_CC;

static int timeNumber=60;static char Nmuber[10]="60";
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



bool GameScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();
    
    isTouch=true;
    
    auto gameNode = CSLoader::createNode("Scene.csb");
    addChild(gameNode);
    Button* g_fanghui_1 = dynamic_cast<Button*>(gameNode->getChildByName("G_fanghui_1"));
    
    g_fanghui_1->addTouchEventListener(CC_CALLBACK_1(GameScene::menufanghui, this));
    
//跑秒的
    label = LabelTTF::create(Nmuber, "fonts/Marker Felt.ttf", 24);
    label->setColor(Color3B(249,194,111));
    label->setPosition(Vec2(origin.x + visibleSize.width/2,origin.y + visibleSize.height - label->getContentSize().height));
    this->addChild(label, 1);
    
    this->schedule(schedule_selector(GameScene::updateTime), 1.0);
    this->scheduleUpdate();

    
//下面是通过读取关卡来让某个图层内的元素进行比较
    
//    auto gamelay1 = dynamic_cast<Node*>(gameNode->getChildByName("game1Node"));
    auto gamelay_node = gameNode->getChildByName("game1Node"); //获取
//    auto game1_sp1 = dynamic_cast<Layer*>(gamelay1->getChildByName("game_1_layer"));
    game1_lay = gamelay_node->getChildByName("game_1_layer"); //获取图层
    game1_lay->setVisible(true);
    
    game1_sp1_list = game1_lay->getChildren();   //获取图层内元素列表
//    game1_sp1_1->setVisible(false);
    
    for(auto sp : game1_sp1_list)
    {
        log("sprite tag = %d", sp->getTag());
    }
    
    
    //旋转
//    auto g_zhizheng_1 = gameNode->getChildByName("zhizheng_16");
    g_zhizheng_1 = dynamic_cast<Sprite*>(gameNode->getChildByName("zhizheng_16"));
//    auto g_zhizheng_1 = gameNode->getChildByName("zhizheng_16") ;
//这里不可以重新设置新变量g_zhizheng_1
    
    g_zhizheng_1->setVisible(true);
    auto rotate1= RotateTo::create(2.0f,-45.0);
    auto rotate2= RotateTo::create(2.0f,45.0);
    auto sequenceBG=Sequence::create(rotate1, rotate2, NULL);
    auto repeatBG=RepeatForever::create(sequenceBG);
    
    g_zhizheng_1->runAction(repeatBG);
    
    
    
//    添加进度条
//    Sprite* g_zhizheng_2 = dynamic_cast<Sprite*>(gameNode->getChildByName("zhizhengtouyin1_25"));
    auto g_zhizheng_2= gameNode->getChildByName("zhizhengtouyin1_25");
    powerProgress=ProgressTimer::create(dynamic_cast<Sprite*>(g_zhizheng_2));
//这里吧node转为sprite
    
//    powerProgress->setScale(powerProgress->getContentSize().width*8/visibleSize.width);
    powerProgress->setTag(2);
//    powerProgress->setRotation(45);
    
    powerProgress->setAnchorPoint(Vec2(0.5,0));
    powerProgress->setBarChangeRate(Point(0,1));
    powerProgress->setType(ProgressTimer::Type::BAR);
    powerProgress->setMidpoint(Point(0,0));
    powerProgress->setPosition(g_zhizheng_1->getPosition());
    powerProgress->setPercentage(0.0f);
    g_zhizheng_2->setVisible(false);
    this->addChild(powerProgress,0);
   

//剩余游戏次数
    quanNumber=100;
    
//
//quan1_26
    spriteQuan = dynamic_cast<Sprite*>(gameNode->getChildByName("quan1_26"));
    
//    numberLabel= gameNode->getChildByName("zhizhengtouyin1_25");
    numberLabel=dynamic_cast<Text*>(gameNode->getChildByName("Text_1"));

//    auto moveBy = MoveTo::create(2, Vec2(500,10));
//    spriteQuan->runAction(moveBy);

    
    
    
    
    
    
    
    
    
    
    auto _eventDispatcher=Director::getInstance()->getEventDispatcher();
    auto listener=EventListenerTouchOneByOne::create();
    
    listener->setSwallowTouches(true);
    listener->onTouchMoved=CC_CALLBACK_2(GameScene::onTouchMoved, this);
    listener->onTouchBegan=CC_CALLBACK_2(GameScene::onTouchBegan,this);
    listener->onTouchEnded=CC_CALLBACK_2(GameScene::onTouchEnded, this);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    return true;
}



bool GameScene::onTouchBegan(Touch *touch, Event *event)
{
    
    log("Touch this !!!!");
    
    
//    CCDirector* director = CCDirector::sharedDirector();
    auto director = Director::getInstance();
    director->getActionManager()->pauseTarget(g_zhizheng_1);
    if(isTouch==false){
        powerProgress->setVisible(false);
    }else{
        powerProgress->setVisible(true);
    }
    auto rotate3= RotateTo::create(0.01f,g_zhizheng_1->getRotation());

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
    log("-----Move-------");
    auto listener=EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(false);
    powerProgress->setVisible(false);
    if (isTouch) {
        if (g_zhizheng_1->getRotation()>0) {
            float rr=sqrt(visibleSize.width/2*visibleSize.width/2+visibleSize.height*3/4*visibleSize.height*3/4);
            
            float r=powerProgress->getPercentage()*0.01*rr;
            float x1=r*cos((90-g_zhizheng_1->getRotation())*3.1415926/180);
            float y1=r*sin((90-g_zhizheng_1->getRotation())*3.1415926/180);
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
            float x1=r*cos((90+g_zhizheng_1->getRotation())*3.1415926/180);
            float y1=r*sin((90+g_zhizheng_1->getRotation())*3.1415926/180);
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
        auto director = Director::getInstance();
        director->getActionManager()->pauseTarget(g_zhizheng_1);
        
    }
    
    
}

void GameScene::onTouchCancelled(Touch *touch, Event *event)
{
    log("-----Move-------");
}


void GameScene::update(float dt)
{
    
    if (spriteQuan->getPositionX()==x&&spriteQuan->getPositionY()==y)
    {
        
        spriteQuan->runAction(DelayTime::create(1.0f));
        if (quanNumber>0)
        {
            
            spriteQuan->setPosition(Vec2(visibleSize.width/2, visibleSize.height/4));
            isTouch=true;
        }else{
            spriteQuan->setVisible(false);
            isTouch=false;

            
        }
        auto director = Director::getInstance();
        director->getActionManager()->resumeTarget(GameScene::g_zhizheng_1);
        
        log("layer:%f,%f",game1_lay->getPositionX(),game1_lay->getPositionY());
        for(auto sp : game1_sp1_list)
        {
            auto sp_x=game1_lay->getPositionX()+sp->getPositionX();
            auto sp_y=game1_lay->getPositionY()+sp->getPositionY();
            
            log("sprite tag = %d", sp->getTag());
            auto flag = GameScene::collisionWithCircle(Vec2(sp_x,sp_y),30.0,Vec2(x, y), 30.0);
            auto mypost=sp->getPosition();
            log("%s",flag==false?"没有套住":"套住了");
            log("[%f,%f][%f,%f]",sp_x,sp_y,x,y);
            
            
            if(flag)
            {
                Blink* spBlink=Blink::create(1.0f, 3);
                sp->runAction(spBlink);
            }
        }
        
        
        
    }else{
        
        }
//    log("%s",isTouch==false?"FALSE":"TRUE");






}

void GameScene::menufanghui(Ref* pSender)
{
    auto helloworld=HelloWorld::createScene();
    Director::getInstance()->replaceScene(helloworld);
//    Director::getInstance()->
    
}


void GameScene::updateTime(float dt)
{
    if (timeNumber>0) {
        timeNumber--;
        
        sprintf(Nmuber, "%d s",timeNumber);
        log("%s",Nmuber);
        label->setString(Nmuber);
    }
    //log("-----Began-------jiaodu= %f baifenbi=%f ",spriteTiao->getRotation(),powerProgress->getPercentage());
    
    
}



bool GameScene::collisionWithCircle(cocos2d::Vec2 circlePoint,float radius,cocos2d::Vec2 circlePointTwo, float radiusTwo)
{
    //2点间距离公式计算
    
    //判断2个圆点是否靠近
    //circlePoint:第一个圆点坐标
    //radius:第一个圆半径
    //circlePointTwo:第二个圆点坐标
    //radiusTwo:第二个圆半径)
    float xdif = circlePoint.x - circlePointTwo.x;
    float ydif = circlePoint.y - circlePointTwo.y;
    log("#%f|%f",xdif,ydif);
    float distance = sqrt(xdif * xdif + ydif * ydif);
    
    if(distance <= radius + radiusTwo)
    {
        return true;
    }
    return false;
}
