//
//  Userguide.cpp
//  Taoquan_release
//
//  Created by lizhengyan on 15/8/10.
//
//

#include "Userguide.h"
#include"SimpleAudioEngine.h"
#include "LevelData.h"
#include "SmartRes.h"
#include "SelectLevel.h"
#include "ShadeLayer_Guild.h"


using namespace CocosDenshion;

Scene* Userguide::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = Userguide::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}
static int cLevel=1;
static int num_touch=0;
// on "init" you need to initialize your instance
bool Userguide::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    //calculationSatrNumber(15,4);
    
    
    bool isSound=UserDefault::getInstance()->getBoolForKey("isSound");
    if (isSound) {
        SimpleAudioEngine::getInstance()->playBackgroundMusic("musicAndeffect/gameSceneMusic.mp3",true);
    }
    isTouch=false;
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();
    log("width===%f   height===%f",visibleSize.width,visibleSize.height);

    
    
    int comeInLevel=1;//从选关界面跳转
    cLevel=comeInLevel;
    UserDefault::getInstance()->setIntegerForKey("cLevel", cLevel);
    //添加暂停按钮
    MenuItemImage*pauseItem = MenuItemImage::create("gamescene/pauseButton.png","gamescene/pauseButton.png",
                                                    CC_CALLBACK_1(Userguide::menuPauseCallback, this));
    pauseItem->setScale(visibleSize.width*1.2/640);
    pauseItem->setPosition(Vec2(visibleSize.width*0.94,origin.y + visibleSize.height*0.94));
    auto menuP=Menu::create(pauseItem, NULL);
    menuP->setPosition(Vec2::ZERO);
    this->addChild(menuP,4);
    
    
    
    //增加圈按钮
    Sprite* addSprite=Sprite::create("selectlevel/jia.png");
    addSprite->setPosition(Vec2(origin.x + visibleSize.width*0.25, origin.y + visibleSize.height*0.94));
    addSprite->setScale(visibleSize.width*0.5/640);
    this->addChild(addSprite,2);
    
    auto addQuanItem = Sprite::create("selectlevel/jia.png");
    
    addQuanItem->setPosition(Vec2(origin.x + visibleSize.width*0.25, origin.y + visibleSize.height*0.935));
    addQuanItem->setScale(visibleSize.width*0.8/640);
    addQuanItem->setOpacity(0);
    addQuanItem->setContentSize(Size(80,80));
    this->addChild(addQuanItem, 1);

    
    //添加圈数
    int circlePropNumber=10;
    
    //剩余圈数
    auto _loopNumber=circlePropNumber;
    char circleNumberChar[10];
    sprintf(circleNumberChar, "%d",_loopNumber);
    auto labelNumber = LabelAtlas::create(circleNumberChar, "gamescene/shuzi2.png", 27.0f, 40.0f, '0');
    labelNumber->setScale(visibleSize.width*0.6/640.0);
    //labelNumber->setPosition(Vec2(origin.x + visibleSize.width*0.84,origin.y + visibleSize.height*0.062));
    labelNumber->setAnchorPoint(Vec2(0.5, 0.5));
    labelNumber->setPosition(Vec2(origin.x + visibleSize.width*0.12,origin.y + visibleSize.height*0.94));
    
    this->addChild(labelNumber, 1);
    //圈数斜杠
    Sprite* slash=Sprite::create("gamescene/xiegang.png");
    slash->setPosition(Vec2(origin.x + visibleSize.width*0.16,origin.y + visibleSize.height*0.94));
    slash->setScale(visibleSize.width*0.8/640.0);
    this->addChild(slash,1);
    //总圈数
    char totalCircleNumberChar[10];
    sprintf(totalCircleNumberChar, "%d",circlePropNumber);
    auto _totalQuanNumber = LabelAtlas::create(totalCircleNumberChar, "gamescene/shuzi2.png", 27.0f, 40.0f, '0');
    _totalQuanNumber->setScale(visibleSize.width*0.6/640.0);
    //labelNumber->setPosition(Vec2(origin.x + visibleSize.width*0.84,origin.y + visibleSize.height*0.062));
    _totalQuanNumber->setAnchorPoint(Vec2(0.5, 0.5));
    _totalQuanNumber->setPosition(Vec2(origin.x + visibleSize.width*0.19,origin.y + visibleSize.height*0.94));
    this->addChild(_totalQuanNumber, 1);
    
    //添加不动圈
    auto _noMoveSprite = Sprite::create("gamescene/huan1.png");

    
    _noMoveSprite->setScale(visibleSize.width*1.4/640.0);
    //noMoveSprite->setPosition(Vec2(origin.x + visibleSize.width*0.78, origin.y + visibleSize.height*0.08));
    _noMoveSprite->setPosition(Vec2(origin.x + visibleSize.width*0.06, origin.y + visibleSize.height*0.94));
    this->addChild(_noMoveSprite, 1);
    //关卡文字
    Sprite* levelLabel=Sprite::create("gamescene/level.png");
    levelLabel->setScale(visibleSize.width*1.1/640.0);
    levelLabel->setPosition(Vec2(origin.x + visibleSize.width*0.45, origin.y + visibleSize.height*0.915));
    this->addChild(levelLabel, 1);
    //关卡数字
    char levelNumberChar[20];
    sprintf(levelNumberChar, "%d:%d",1,1);
    auto _labelLevel = LabelAtlas::create(levelNumberChar, "gamescene/shuzi1.png", 18.0f, 24.0f, '0');
    _labelLevel->setScale(visibleSize.width*1.2/640.0);
    _labelLevel->setAnchorPoint(Vec2(0.5, 0.5));
    _labelLevel->setPosition(Vec2(origin.x + visibleSize.width*0.565,origin.y + visibleSize.height*0.915));
    this->addChild(_labelLevel, 1);
    
    
    
    _spriteQuan=Sprite::create("gamescene/quan2.png");
    auto _ruling=Sprite::create("gamescene/powerBarBG1.png");
    
    _spriteQuan->setScale(0.8*visibleSize.width/640);
    _spriteQuan->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height*0.1 + origin.y));
    this->addChild(_spriteQuan,3);
    
    _ruling->setScale(1.1*visibleSize.width/640);
    _ruling->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height*smartRes_jinDuTiaoHeigh  + origin.y));
    this->addChild(_ruling,2);
    
    int QUAN_SCA=0.8*visibleSize.width/640;
    
    
    //从json文件中随机取出一种图片摆放形状
    int randNum=1;
    //int randNum=1;
    ValueVector shapeVV=LevelData::paeseLevelShape(randNum).asValueVector();
    
    ValueVector picVV=LevelData::paeseLevelSmallPicture(comeInLevel).asValueVector();//从json文件中取出每关必须有小图片
    
    
    for (int i=0; i<9; i++) {
        char s[10];
        sprintf(s, "s%d", i+1);
        int ss =shapeVV.at(0).asValueMap()[s].asInt();
        int pX=ss/100;
        int pY=ss%100;
        //添加图片
        ResolvePicture* rp=ResolvePicture::createResolvePicture();
        rp->setScale(0.8*visibleSize.width/640);
        std::stringstream name; string color="";int randNumber;

            if (i<picVV.size()) {
                int mPicID =picVV.at(i).asValueMap()["id"].asInt();
                std::string mPicName =picVV.at(i).asValueMap()["pictureName"].asString();
                name<<mPicName;
                rp->initResolvePicture(name.str(), mPicID);
            }else{
                randNumber=random(1, 8);//随机图片
                name<<"gamescene/n"<<randNumber<<".png";
                rp->initResolvePicture(name.str(), -1);
            }

        rp->setPicturePosition(origin.x+visibleSize.width*pX*0.01, origin.y + visibleSize.height*pY*0.01);
        if(i==0){mubiao=rp;}   //保留第一个物体
        this->addChild(rp, 2);
        rp->savePicturePosition(rp->getPosition());   //保留一份老数据
        spriteVector.pushBack(rp);
        
        auto dizuoTouying=Sprite::create("gamescene/foundation.png");
        dizuoTouying->setScale(0.8*visibleSize.width/640);
        dizuoTouying->setPosition(Vec2(origin.x+visibleSize.width*pX*0.01, origin.y + visibleSize.height*pY*0.01-visibleSize.height*smartRes_dzty));
        this->addChild(dizuoTouying,1);
        

        auto _gameBG = Sprite::create("gamescene/gameBG1.png");
        
        _gameBG->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
        _gameBG->setScale(visibleSize.width/_gameBG->getContentSize().width);
        this->addChild(_gameBG, 0);
    }
    
    
    _spriteTiao=Sprite::create("gamescene/zhizhenBG1.png");
    _spriteTiao->setScale(0.7*visibleSize.width/640);
    _spriteTiao->setRotation(45);
    _spriteTiao->setTag(1);
    _spriteTiao->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height*0.1 + origin.y));
    _spriteTiao->setAnchorPoint(Vec2(0.5,0.5));
    this->addChild(_spriteTiao, 1);
    //添加进度条
    _powerProgress=ProgressTimer::create(Sprite::create("gamescene/powerBar.png"));
    _powerProgress->setScale(1.1*visibleSize.width/640);
    _powerProgress->setTag(2);
    _powerProgress->setAnchorPoint(Vec2(0.5,0.5));
    _powerProgress->setBarChangeRate(Point(1,0));
    _powerProgress->setType(ProgressTimer::Type::BAR);
    _powerProgress->setMidpoint(Point(0,0));
    _powerProgress->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height*smartRes_jinDuTiaoHeigh + origin.y));
    _powerProgress->setPercentage(0.0f);
    this->addChild(_powerProgress,2);
    _powerProgress->setVisible(false);
    

    _spriteTiao->setRotation(-45);
    
    ValueVector hiddenPic=LevelData::paeseXml(comeInLevel).asValueVector();
    
    for (int i=0; i<hiddenPic.size(); i++) {
        
        int _inttag =hiddenPic.at(i).asValueMap()["inttag"].asInt();
        int picId=_inttag;
        std::string name =hiddenPic.at(i).asValueMap()["picName"].asString();
        int px =hiddenPic.at(i).asValueMap()["positionX"].asInt();
        int py =hiddenPic.at(i).asValueMap()["positionY"].asInt();
        int rotation=hiddenPic.at(i).asValueMap()["rotation"].asInt();
        if (_inttag<1000) {
            ResolvePicture* rp=ResolvePicture::createResolvePicture();
            rp->setScale(visibleSize.width*smartRes_hiddenPicScale/58);
            rp->initResolvePicture(name, picId);
            rp->setPicturePosition(visibleSize.width*px*0.001, visibleSize.height*py*0.001);
            rp->setRotation(rotation);
            //rp->setVisible(false);
            //this->addChild(rp,3);
            hiddenPictureVector.pushBack(rp);
        }else{
            //添加整图
            _wholePicture = Sprite::create(name);
            _wholePicture->setScale(visibleSize.width*0.92/640.0);
            _wholePicture->setPosition(Vec2(origin.x + visibleSize.width*px*0.01, origin.y + visibleSize.height*py*0.01));
            this->addChild(_wholePicture, 1);
        }
        
    }
    if(UserDefault::getInstance()->getIntegerForKey("Userguide")==1)
    {
        z1=Sprite::create("xinshou/zhezhao2.png");
        w1=Sprite::create("xinshou/6.png");
        w1->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height*0.39 + origin.y));
        this->schedule(schedule_selector(Userguide::updateTime), 1.5);
        sprite_xxoo=true;
        RotateTo*rotate1= RotateTo::create(1.5,-45.0);
        
        RotateTo*rotate2 = RotateTo::create(1.5,45.0);
        Sequence* sequenceBG=Sequence::create(rotate1, rotate2, NULL);
        RepeatForever* repeatBG=RepeatForever::create(sequenceBG);
        //设置速度
        float _speedT=1.2;
        auto _spriteTiaoSpeed=Speed::create(repeatBG, _speedT);
        _spriteTiao->runAction(_spriteTiaoSpeed);
        num_touch=3;
        
        
    }else{
    z1=Sprite::create("xinshou/zhezhao0.png");
        w1=Sprite::create("xinshou/1.png");
        w1->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height*0.39 + origin.y));
        num_touch=1;
    }
    z1->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    z1->setScale(visibleSize.width/z1->getContentSize().width);
    this->addChild(z1, 4);
    
    
    
    w1->setScale(visibleSize.width/z1->getContentSize().width);
    this->addChild(w1, 5);
    
    auto _eventDispatcher=Director::getInstance()->getEventDispatcher();
    auto listener1=EventListenerTouchOneByOne::create();
//    listener1->setSwallowTouches(true);
    listener1->onTouchMoved=CC_CALLBACK_2(Userguide::onTouchMoved, this);
    listener1->onTouchBegan=CC_CALLBACK_2(Userguide::onTouchBegan,this);
    listener1->onTouchEnded=CC_CALLBACK_2(Userguide::onTouchEnded, this);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, this);
//    UserDefault::getInstance()->setIntegerForKey("Userguide",2);
    isTouch=true;
    return true;
}


void Userguide::onTouchEnded(Touch*touch, Event* event)
{
    log("你摸我了");
    isTouch?log("true"):log("false");
    if(isTouch)
    {
        switch (num_touch) {
            case 1:
                isTouch=false;
                num_touch+=1;
                Userguide::Touch_first();
                break;
            case 2:
                isTouch=false;
                num_touch+=1;
                Userguide::Touch_second();
                break;
            case 3:
                isTouch=false;
                num_touch+=1;
                Userguide::Touch_three();
                break;
            case 4:
                isTouch=false;
                num_touch+=1;
                Userguide::Touch_four();
                break;
                
            case 5:
                isTouch=false;
                num_touch+=1;
                Userguide::Touch_five();
                break;
            case 6:
                isTouch=false;
                num_touch+=1;
                Userguide::Touch_six();
                break;
                
            default:
                break;
        }
    }
    _powerProgress->setVisible(false);
    Director* director=Director::getInstance();
    director->getActionManager()->resumeTarget(_spriteTiao);
    director->getActionManager()->pauseTarget(_powerProgress);
    _powerProgress->setVisible(false);
    _powerProgress->setPercentage(0);
}


void Userguide::Touch_first()
{
    log("第一阶段");
    w1->removeFromParent();
    z1->removeFromParent();
    
    z2=Sprite::create("xinshou/zhezhao1.png");
    z2->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    z2->setScale(visibleSize.width/z2->getContentSize().width);
    z2->setOpacity(0);z2->runAction(FadeTo::create(0.5, 255));
    this->addChild(z2, 4);
    
    
    w2=Sprite::create("xinshou/2.png");
    w2->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height*0.39 + origin.y));
    w2->setScale(visibleSize.width/w2->getContentSize().width);
    w2->setOpacity(0);w2->runAction(FadeTo::create(0.5, 255));
    this->addChild(w2, 4);
    isTouch=true;
    
    log("%d",num_touch);
}

void Userguide::Touch_second()
{
    log("第二阶段");
    w2->removeFromParent();
    z2->removeFromParent();
    
    z3=Sprite::create("xinshou/zhezhao2.png");
    z3->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    z3->setScale(visibleSize.width/z3->getContentSize().width);
    z3->setOpacity(0);z3->runAction(FadeTo::create(0.5, 255));
    this->addChild(z3, 4);
    
    
    w3=Sprite::create("xinshou/3.png");
    w3->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height*0.39 + origin.y));
    w3->setScale(visibleSize.width/w3->getContentSize().width);
    w3->setOpacity(0);w3->runAction(FadeTo::create(0.5, 255));
    this->addChild(w3, 4);
    log("%d",num_touch);
    
    isTouch=true;
}

void Userguide::Touch_three()
{
    log("第三阶段");
    if(UserDefault::getInstance()->getIntegerForKey("Userguide")==0){
        w3->removeFromParent();
        z3->removeFromParent();
    }else{
        w1->removeFromParent();
        z1->removeFromParent();
    }
    z4=Sprite::create("xinshou/zhezhao3.png");
    z4->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    z4->setScale(visibleSize.width/z4->getContentSize().width);
    z4->setOpacity(0);z4->runAction(FadeTo::create(0.5, 255));
    this->addChild(z4, 4);
    
    
    w4=Sprite::create("xinshou/4.png");
    w4->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height*0.39 + origin.y));
    w4->setScale(visibleSize.width/w4->getContentSize().width);
    w4->setOpacity(0);w4->runAction(FadeTo::create(0.5, 255));
    this->addChild(w4, 4);
    _spriteTiao->runAction(RotateTo::create(0.5,-18));
    log("%d",num_touch);
    
        isTouch=true;
}

void Userguide::Touch_four()
{
    
    log("第四阶段");
    w5->removeFromParent();
    
    auto  _sp_action=Sequence::create(MoveTo::create(0.5, mubiao->getPosition()) , FadeTo::create(0.2, 0), NULL);
//    auto targetAct = TargetedAction::create(mubiao,Sequence::create(MoveBy::create(0.05, Vec2(-15,0)),MoveBy::create(0.1, Vec2(30,0)), MoveBy::create(0.05, Vec2(-15,0)),NULL));
    
    auto spriteQuan_return  = TargetedAction::create(_spriteQuan,Place::create(Vec2(visibleSize.width/2, visibleSize.height*0.1)));
    auto menuItemBlink=Spawn::create(JumpBy::create(0.6f, Vec2(0,50), 50, 1),FadeTo::create(0.6f, 0), NULL);
    auto targetAct = TargetedAction::create(mubiao,menuItemBlink);
    auto taozhong_heshi=hiddenPictureVector.at(0);
    ParticleSystem * p4=ParticleGalaxy::createWithTotalParticles(200);
    p4->setPosition(Vec2(mubiao->getPositionX(),mubiao->getPositionY()+50));
    p4->setStartColor(Color4F(1,1,1,1));
    this->addChild(p4,5);
    p4->setVisible(false);
    
    auto p5 = MotionStreak::create(0.2, 1, 100, Color3B::WHITE,"gamescene/start5.png" );
    p5->setPosition(Vec2(mubiao->getPositionX(),mubiao->getPositionY()+50));
    p5->setVisible(false);
    p5->isFastMode();
    this->addChild(p5,5);
    
    
    _spriteQuan->runAction(Sequence::create(_sp_action,CallFunc::create([=]{_spriteQuan->setZOrder(1);}),MoveBy::create(0.3, Vec2(0,-30)),FadeTo::create(0.2, 0),targetAct,spriteQuan_return,
                                            CallFunc::create([=]{_spriteQuan->setZOrder(3);}),
                                            CallFunc::create([=](){
        _spriteQuan->setOpacity(255);
//        _spriteQuan->setScale(QUAN_SCA);
        _spriteQuan->setRotation(0);
        mubiao->setPosition(mubiao->getPositionX(),mubiao->getPositionY()-50);
        
        p5->setVisible(true);
        p4->setVisible(true);
        p4->runAction(MoveTo::create(0.3, taozhong_heshi->getPosition()));
        p5->runAction(MoveTo::create(0.3, taozhong_heshi->getPosition()));
//        mubiao->changPicture(cLevel);
        
    }),DelayTime::create(0.5), //等p4结束哦 0.5秒
                                            CallFunc::create([=](){
        mubiao->setVisible(true);
        mubiao->setOpacity(255);
        addChild(taozhong_heshi,3);
        taozhong_heshi->setOpacity(0);
        
        taozhong_heshi->runAction(FadeTo::create(0.5, 255));
        removeChild(p4,p5);
        
        this->scheduleOnce(SEL_SCHEDULE(&Userguide::enterIntoSucceedUI), 1.0f);
        
    }),CallFunc::create([=](){isTouch=true; }),  NULL));
    log("回到这里来了");
    
}


void Userguide::Touch_five()
{
    log("第五阶段");
    hiddenPictureVector.at(0)->setOpacity(0);
    RotateTo*rotate1= RotateTo::create(1.5,-45.0);
    
    RotateTo*rotate2 = RotateTo::create(1.5,45.0);
    Sequence* sequenceBG=Sequence::create(rotate1, rotate2, NULL);
    RepeatForever* repeatBG=RepeatForever::create(sequenceBG);
    //设置速度
    float _speedT=1.2;
    auto _spriteTiaoSpeed=Speed::create(repeatBG, _speedT);
    _spriteTiao->runAction(_spriteTiaoSpeed);
    
    Vec2 v2=spriteVector.at(0)->PPOINT;
    this->runAction(Sequence::create( DelayTime::create(2), CallFunc::create([=]() { Userguide::spriteVectorMove();}),
                                     DelayTime::create(2), CallFunc::create([=]() { Userguide::spriteVectorMove();}),
                                     DelayTime::create(2), CallFunc::create([=]() { Userguide::spriteVectorMove();}),
                                     NULL));
    
    
    isTouch=true;
}


void Userguide::Touch_six()
{
    
}

void Userguide::onTouchMoved(Touch*touch, Event* event)
{
    log("moved");
}

void Userguide::spriteVectorMove()
{
    Vec2 v2=spriteVector.at(0)->PPOINT;
    for (int i=0; i<9; i++) {
        if (i!=8) {
            spriteVector.at(i)->runAction(MoveTo::create(0.2,spriteVector.at(i+1)->PPOINT));
            spriteVector.at(i)->savePicturePosition(spriteVector.at(i+1)->PPOINT);
        }else{
            spriteVector.at(i)->runAction(MoveTo::create(0.2,v2));
            spriteVector.at(i)->savePicturePosition(v2);
        }
        
        
    }
}

bool Userguide::onTouchBegan(Touch*touch, Event* event)
{
    log("begin");
    log("num_touch=%d",num_touch);
    if(num_touch==4)
    {
        w4->removeFromParent();
        z4->removeFromParent();

        w5=Sprite::create("xinshou/5.png");
        w5->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height*0.39 + origin.y));
        w5->setScale(visibleSize.width/w5->getContentSize().width);
        this->addChild(w5, 4);
        _powerProgress->setVisible(true);
        _powerProgress->runAction(ProgressFromTo::create(0.5, 0.0f, 80.0f));
        
        Director::getInstance()->getActionManager()->pauseTarget(_spriteTiao);
    }
    
    if(num_touch==5)
    {
        
        repeatPG=RepeatForever::create(Sequence::create(ProgressFromTo::create(1.0, 0.0f, 100.0f), ProgressFromTo::create(1.0, 100.0f, 0.0f), NULL));
        _progressTimerSpeed=Speed::create(repeatPG, 0.8);
        _powerProgress->runAction(_progressTimerSpeed);
    }
    
    if(num_touch==6)
    {
        Director* director=Director::getInstance();
        _powerProgress->setPercentage(0);
        log("百分比=%f",_powerProgress->getPercentage());
        _powerProgress->setVisible(true);
        director->getActionManager()->resumeTarget(_powerProgress);
        director->getActionManager()->pauseTarget(_spriteTiao);
        
        repeatPG=RepeatForever::create(Sequence::create(ProgressFromTo::create(1.0, 0.0f, 100.0f), ProgressFromTo::create(1.0, 100.0f, 0.0f), NULL));
        _progressTimerSpeed=Speed::create(repeatPG, 0.8);
        _powerProgress->runAction(_progressTimerSpeed);
        
    }
    
    return true;
}


void Userguide::menuPauseCallback(Ref* pSender)
{
    Scene* selectLevelScene=SelectLevel::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(1.2f, selectLevelScene));
}



void Userguide::enterIntoSucceedUI()
{
    int picNumber=(int)showPictureVector.size();
    for (int i=0; i<picNumber; i++) {
        ResolvePicture* rp=(ResolvePicture*)showPictureVector.at(i);
        this->removeChild(rp);
        
    }
    showPictureVector.clear();
    char getUserSql[100];
    sprintf(getUserSql, "select * from User where level=%d",cLevel);
    
    UserDefault::getInstance()->setBoolForKey("isReduceEnergy", false);//套圈成功，不减少体力
    
    //从数据库中取出用户信息
    cocos2d::Value cv=DataUtil::getRow(getUserSql);
    SimpleAudioEngine::getInstance()->stopBackgroundMusic();//停止背景音乐
    DataUtil::updateSuoData(false, cLevel+1);//下一关解锁
    int starNum=0;
    char getPropSql[100];
    sprintf(getPropSql, "select * from Prop ");
    
    starNum=3;
    
    
    UserDefault::getInstance()->setIntegerForKey("cLevelXingNumber", starNum);
    //        bool isGengxin=UserDefault::getInstance()->getBoolForKey("isGengxin");
    DataUtil::updateStarData(starNum, cLevel);//更新星星的数量
    Director::getInstance()->pause();//暂停游戏
    //添加过关层
    auto _succeedLayer=ShadeLayer_Guild::create();
    this->addChild(_succeedLayer,100,"succeedLayer");
    hiddenPictureVector.at(0)->setOpacity(0);
    log("%%%%%%%%%%%%");
    
    UserDefault::getInstance()->setIntegerForKey("Userguide", UserDefault::getInstance()->getIntegerForKey("Userguide")+1);
    //设为进行第一次新手第一部分完成引导
}



void Userguide::updateTime(float dt)
{
    Vec2 v2=spriteVector.at(0)->PPOINT;
    for (int i=0; i<9; i++) {
        if (i!=8) {
            spriteVector.at(i)->runAction(MoveTo::create(0.2,spriteVector.at(i+1)->PPOINT));
            spriteVector.at(i)->savePicturePosition(spriteVector.at(i+1)->PPOINT);
        }else{
            spriteVector.at(i)->runAction(MoveTo::create(0.2,v2));
            spriteVector.at(i)->savePicturePosition(v2);
        }
        
        
    }
    
}
