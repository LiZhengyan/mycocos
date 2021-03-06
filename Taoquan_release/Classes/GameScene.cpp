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
#include "FailedShadeLayer.h"
#include "LevelData.h"
#include "PauseLayer.h"
#include "SmartRes.h"
#include "ShoppingMall.h"
#include "Single.h"
USING_NS_CC;
#include"SimpleAudioEngine.h"
using namespace CocosDenshion;


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
static int cLevel=1;
// on "init" you need to initialize your instance
bool GameScene::init()
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
    
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();
    log("width===%f   height===%f",visibleSize.width,visibleSize.height);
    _isTouch=true;
    _IsNeedExit=false;
    _isHelp=false;
    _isTaoZhong=false;
    
    
    int comeInLevel=UserDefault::getInstance()->getIntegerForKey("comeInLevel");//从选关界面跳转
    cLevel=comeInLevel;
    UserDefault::getInstance()->setIntegerForKey("cLevel", cLevel);
    //添加暂停按钮
    Sprite* pauseSprite=Sprite::create("gamescene/pauseButton.png");
    pauseSprite->setPosition(Vec2(visibleSize.width*0.94,origin.y + visibleSize.height*0.94));
    pauseSprite->setScale(visibleSize.width*0.8/640);
    this->addChild(pauseSprite,2);
    
    MenuItemImage*pauseItem = MenuItemImage::create("gamescene/pauseButton.png","gamescene/pauseButton.png",
                                           CC_CALLBACK_1(GameScene::menuPauseCallback, this));
    pauseItem->setScale(visibleSize.width*1.6/640);
    pauseItem->setOpacity(0);
    pauseItem->setPosition(Vec2(visibleSize.width*0.94,origin.y + visibleSize.height*0.94));
   
    //帮助按钮
    /*auto helpItem = MenuItemImage::create("gamescene/helpButton.png","gamescene/helpButton.png",
                                          CC_CALLBACK_1(GameScene::menuHelpCallback, this));
    
    helpItem->setPosition(Vec2(origin.x +visibleSize.width*0.1,origin.y + visibleSize.height*0.94));
    helpItem->setScale(visibleSize.width*0.9/640);*/
    //增加圈按钮
    Sprite* addSprite=Sprite::create("selectlevel/jia.png");
    addSprite->setPosition(Vec2(origin.x + visibleSize.width*0.25, origin.y + visibleSize.height*0.94));
    addSprite->setScale(visibleSize.width*0.5/640);
    this->addChild(addSprite,2);
    
    auto addQuanItem = MenuItemImage::create("selectlevel/jia.png","selectlevel/jia.png",
                                          CC_CALLBACK_1(GameScene::menuAddQuanCallback, this));
    
    addQuanItem->setPosition(Vec2(origin.x + visibleSize.width*0.25, origin.y + visibleSize.height*0.935));
    addQuanItem->setScale(visibleSize.width*0.8/640);
    addQuanItem->setOpacity(0);
    addQuanItem->setContentSize(Size(80,80));

    
    auto menu = Menu::create(pauseItem,addQuanItem, NULL);
    menu->setPosition(Vec2::ZERO);
    
    this->addChild(menu, 1);
    //添加帮助数
    char getPropSql[100];
    sprintf(getPropSql, "select * from Prop ");
    Value avm=DataUtil::getRow(getPropSql);
    
//    _helpNumber=avm.asValueMap()["helpProp"].asInt();
//    char hNumber[10];
//    sprintf(hNumber, ":%d",_helpNumber);
//    _labelHelpNumber = LabelAtlas::create(hNumber, "gamescene/shuzi2.png", 27.0f, 40.0f, '0');
//    _labelHelpNumber->setScale(visibleSize.width/640.0);
//    _labelHelpNumber->setPosition(Vec2(origin.x +visibleSize.width*0.15,origin.y + visibleSize.height*0.92));
//    this->addChild(_labelHelpNumber, 1);
    
    //添加圈数
    int circlePropNumber=avm.asValueMap()["circleProp"].asInt();
    
    //剩余圈数
    _loopNumber=circlePropNumber;
    char circleNumberChar[10];
    sprintf(circleNumberChar, "%d",_loopNumber);
    labelNumber = LabelAtlas::create(circleNumberChar, "gamescene/shuzi2.png", 27.0f, 40.0f, '0');
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
    _totalQuanNumber = LabelAtlas::create(totalCircleNumberChar, "gamescene/shuzi2.png", 27.0f, 40.0f, '0');
    _totalQuanNumber->setScale(visibleSize.width*0.6/640.0);
    //labelNumber->setPosition(Vec2(origin.x + visibleSize.width*0.84,origin.y + visibleSize.height*0.062));
    _totalQuanNumber->setAnchorPoint(Vec2(0.5, 0.5));
    _totalQuanNumber->setPosition(Vec2(origin.x + visibleSize.width*0.19,origin.y + visibleSize.height*0.94));
    this->addChild(_totalQuanNumber, 1);

    
    //添加不动圈
    if (cLevel<10) {
        _noMoveSprite = Sprite::create("gamescene/huan1.png");
    }else
        _noMoveSprite = Sprite::create("gamescene/huan2.png");
    
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
    if(cLevel%9!=0){
        sprintf(levelNumberChar, "%d:%d",cLevel/9+1,cLevel%9);
    }else{
        sprintf(levelNumberChar, "%d:%d",cLevel/9,9);
    }
    _labelLevel = LabelAtlas::create(levelNumberChar, "gamescene/shuzi1.png", 18.0f, 24.0f, '0');
    _labelLevel->setScale(visibleSize.width*1.2/640.0);
    _labelLevel->setAnchorPoint(Vec2(0.5, 0.5));
    _labelLevel->setPosition(Vec2(origin.x + visibleSize.width*0.565,origin.y + visibleSize.height*0.915));
    
    this->addChild(_labelLevel, 1);
    
    //添加圈//力度条背景
    if (cLevel>9) {
        _spriteQuan=Sprite::create("gamescene/quan3.png");
        _ruling=Sprite::create("gamescene/powerBarBG2.png");
    }else{
        _spriteQuan=Sprite::create("gamescene/quan2.png");
        _ruling=Sprite::create("gamescene/powerBarBG1.png");
    }
    _spriteQuan->setScale(0.8*visibleSize.width/640);
    _spriteQuan->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height*0.1 + origin.y));
    this->addChild(_spriteQuan,3);
    
    _ruling->setScale(1.1*visibleSize.width/640);
    _ruling->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height*smartRes_jinDuTiaoHeigh + origin.y));
    this->addChild(_ruling,2);
    
    QUAN_SCA=0.8*visibleSize.width/640;
    
    //上次套圈轨迹虚线
    _dottedLineProgress2=ProgressTimer::create(Sprite::create("gamescene/dottedLine.png"));
    _dottedLineProgress2->setScale(visibleSize.width*smartRes_shangCiGuiJiHeigh/640);
    _dottedLineProgress2->setTag(2);
    _dottedLineProgress2->setRotation(0);
    
    _dottedLineProgress2->setAnchorPoint(Vec2(0.5,0));
    _dottedLineProgress2->setBarChangeRate(Point(0,1));
    _dottedLineProgress2->setType(ProgressTimer::Type::BAR);
    _dottedLineProgress2->setMidpoint(Point(0,0));
    _dottedLineProgress2->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height*0.1 + origin.y));
    _dottedLineProgress2->setPercentage(0.0f);
    _dottedLineProgress2->setVisible(false);
    this->addChild(_dottedLineProgress2,3);

    //从数据库中取出用户信息,判断游戏模式
    char getUserSql[100];
    sprintf(getUserSql, "select * from User where level=%d",cLevel);

    cocos2d::Value cv=DataUtil::getRow(getUserSql);
    int pattern=cv.asValueMap()["pattern"].asInt();
    int yinXingNum=cv.asValueMap()["starNum"].asInt();
    if (pattern==1&&yinXingNum!=3) {
        _speedT=0.7;
        _speedP=0.5;
        this->unschedule(schedule_selector(GameScene::updateTime));
    }else if(pattern==2){
        _speedT=1.2;
        _speedP=1.0;
        this->schedule(schedule_selector(GameScene::updateTime), 3.0);
    }else if(pattern==1&&yinXingNum==3){
        _speedT=1.2;
        _speedP=1.0;
        this->schedule(schedule_selector(GameScene::updateTime), 3.0);
        DataUtil::updatePatternData(2,cLevel);//更新游戏模式
        UserDefault::getInstance()->setBoolForKey("isGengxin", true);
    }
    
    
    //从json文件中随机取出一种图片摆放形状
    int randNum=random(1, 6);
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
        if (cLevel>9) {
            if (i<4) {
                int randName=random(0, 2);
                int mPicID =picVV.at(i+randName*4).asValueMap()["id"].asInt();
                std::string mPicName =picVV.at(i+randName*4).asValueMap()["pictureName"].asString();
                name<<mPicName<<mPicID<<".png";
                rp->initResolvePicture(name.str(), mPicID);
            }else{
                randNumber=random(1, 6);//随机图片
                name<<"gamescene/t"<<randNumber<<".png";
                rp->initResolvePicture(name.str(), -1);
            }

        }else{
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
        }
        rp->setPicturePosition(origin.x+visibleSize.width*pX*0.01, origin.y + visibleSize.height*pY*0.01);
        this->addChild(rp, 2);
        rp->savePicturePosition(rp->getPosition());   //保留一份老数据
        spriteVector.pushBack(rp);
        
      
        //底座
        Sprite* dizuoTouying;
        if (comeInLevel>9) {
            dizuoTouying=Sprite::create("gamescene/foundation5.png");
            dizuoTouying->setPosition(Vec2(origin.x+visibleSize.width*pX*0.01, origin.y + visibleSize.height*pY*0.01-visibleSize.height*smartRes_dzty));
        }else{
            dizuoTouying=Sprite::create("gamescene/foundation.png");
            dizuoTouying->setPosition(Vec2(origin.x+visibleSize.width*pX*0.01, origin.y + visibleSize.height*pY*0.01-visibleSize.height*smartRes_dzty));
        }
       
        dizuoTouying->setScale(0.8*visibleSize.width/640);
        this->addChild(dizuoTouying,1);
        dizuoTouyingVector.pushBack(dizuoTouying);

    }


    //背景
    if (comeInLevel<10) {
        char bgName[30];
        sprintf(bgName, "gamescene/gameBG%d.png",randNum);
        _gameBG = Sprite::create(bgName);
    }else
    {
        _gameBG = Sprite::create("gamescene/gameBG.png");
    }
    _gameBG->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    _gameBG->setScale(visibleSize.width/_gameBG->getContentSize().width);
    this->addChild(_gameBG, 0);
    
    
    this->scheduleUpdate();
    
    if (cLevel>9) {
        //指针
        _spriteTiao=Sprite::create("gamescene/zhizhenBG2.png");
    }else{
        //指针
        _spriteTiao=Sprite::create("gamescene/zhizhenBG1.png");
    }
    _spriteTiao->setScale(0.7*visibleSize.width/640);
    _spriteTiao->setRotation(45);
    _spriteTiao->setTag(1);
    _spriteTiao->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height*0.1 + origin.y));
    _spriteTiao->setAnchorPoint(Vec2(0.5,0.5));
    this->addChild(_spriteTiao, 0);
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

    //旋转
    RotateTo*rotate1= RotateTo::create(1.5,-45.0);
    
    RotateTo*rotate2 = RotateTo::create(1.5,45.0);
    Sequence* sequenceBG=Sequence::create(rotate1, rotate2, NULL);
    RepeatForever* repeatBG=RepeatForever::create(sequenceBG);
    //设置速度
    _spriteTiaoSpeed=Speed::create(repeatBG, _speedT);
    _spriteTiao->runAction(_spriteTiaoSpeed);
    
    //json文件解析获取隐藏小图
    
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
    
   
    
    //添加监听
    auto _eventDispatcher=Director::getInstance()->getEventDispatcher();
    auto listener1=EventListenerTouchOneByOne::create();
    listener1->setSwallowTouches(true);
    listener1->onTouchMoved=CC_CALLBACK_2(GameScene::onTouchMoved, this);
    listener1->onTouchBegan=CC_CALLBACK_2(GameScene::onTouchBegan,this);
    listener1->onTouchEnded=CC_CALLBACK_2(GameScene::onTouchEnded, this);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, this);
    //过关界面自定义监听回调

    auto mCustomListener = EventListenerCustom::create("succeefulUI", CC_CALLBACK_1(GameScene::setNextLevelPicture, this));
    _eventDispatcher->addEventListenerWithFixedPriority(mCustomListener, 1);
    
    
    //过关界面进入金星模式自定义监听回调
    auto jinXingCustomListener = EventListenerCustom::create("ThisLevelGold", CC_CALLBACK_1(GameScene::resetGame, this));
    _eventDispatcher->addEventListenerWithFixedPriority(jinXingCustomListener, 1);
    
    
    //失败界面自定义监听回调
    auto failedUICustomListener = EventListenerCustom::create("failedUI", CC_CALLBACK_1(GameScene::resetGame, this));
    _eventDispatcher->addEventListenerWithFixedPriority(failedUICustomListener, 1);
    
    
    //暂停界面自定义监听回调
    auto pauseUICustomListener = EventListenerCustom::create("backRestartGame", CC_CALLBACK_1(GameScene::resetGame, this));
    _eventDispatcher->addEventListenerWithFixedPriority(pauseUICustomListener, 1);
    //成功界面重新开始自定义监听回调
    auto succeedCustomListener = EventListenerCustom::create("succeedResatrt", CC_CALLBACK_1(GameScene::resetGame, this));
    _eventDispatcher->addEventListenerWithFixedPriority(succeedCustomListener, 1);


    //注册捕捉监听
    auto listenerkeyPad = EventListenerKeyboard::create();
    listenerkeyPad->onKeyReleased = CC_CALLBACK_2(GameScene::onKeyReleased, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listenerkeyPad, this);
    
    
    
    //_eventDispatcher->removeAllEventListeners();
    return true;
}

//判断本关模式
void GameScene::judgeCurrentLevelPattern(int level)
{
    char getUserSql[100];
    sprintf(getUserSql, "select * from User where level=%d",level);
    //从数据库中取出用户信息
    cocos2d::Value cv=DataUtil::getRow(getUserSql);
    int pattern=cv.asValueMap()["pattern"].asInt();
    int yinXingNum=cv.asValueMap()["starNum"].asInt();
    if (pattern==1&&yinXingNum!=3) {
        this->unschedule(schedule_selector(GameScene::updateTime));
        //设置指针摆动速度
        _spriteTiaoSpeed->setSpeed(0.7);
        //设置进度条速度
        if (_progressTimerSpeed==NULL) {
            //力度条的动作
            repeatPG=RepeatForever::create(Sequence::create(ProgressFromTo::create(1.0, 0.0f, 100.0f), ProgressFromTo::create(1.0, 100.0f, 0.0f), NULL));
            _progressTimerSpeed=Speed::create(repeatPG, 0.5);
        }else
            _progressTimerSpeed->setSpeed(0.5);
    }else if(pattern==2){
        //设置指针摆动速度
        _spriteTiaoSpeed->setSpeed(1.2);
        //设置进度条速度
        if (_progressTimerSpeed==NULL) {
            //力度条的动作
            repeatPG=RepeatForever::create(Sequence::create(ProgressFromTo::create(1.0, 0.0f, 100.0f), ProgressFromTo::create(1.0, 100.0f, 0.0f), NULL));
            _progressTimerSpeed=Speed::create(repeatPG, 1.0);
        }else
            _progressTimerSpeed->setSpeed(1.0);
        
        this->schedule(schedule_selector(GameScene::updateTime), 3.0);//图片位置移动
    }else if(pattern==1&&yinXingNum==3){
        //设置指针摆动速度
        _spriteTiaoSpeed->setSpeed(1.2);
        //设置进度条速度
        if (_progressTimerSpeed==NULL) {
            //力度条的动作
            repeatPG=RepeatForever::create(Sequence::create(ProgressFromTo::create(1.0, 0.0f, 100.0f), ProgressFromTo::create(1.0, 100.0f, 0.0f), NULL));
            _progressTimerSpeed=Speed::create(repeatPG, 1.0);
        }else
            _progressTimerSpeed->setSpeed(1.0);
        DataUtil::updatePatternData(2,cLevel);//更新游戏模式
        UserDefault::getInstance()->setBoolForKey("isGengxin", true);
        this->schedule(schedule_selector(GameScene::updateTime), 3.0);//图片位置移动
    }
}

//设置图片的摆放位置
void GameScene::setNextLevelPicture(EventCustom* e)
{
    Director::getInstance()->resume();
    
    _isTouch=true;
    SimpleAudioEngine::getInstance()->rewindBackgroundMusic();//重新开始播放背景音乐
    _isTaoZhong=false;
    //更新圈数
    char*buf =static_cast<char*>(e->getUserData());
    _loopNumber=std::atoi(buf);
    labelNumber->setString(buf);
    _powerProgress->setPercentage(0);//将力度条的值归0
    _dottedLineProgress2->setVisible(false);//将上次轨迹线隐藏
    cLevel++;//关卡加1
    UserDefault::getInstance()->setIntegerForKey("cLevel", cLevel);
    
    //更新关卡数字
    char levelNumberChar[20];
    if(cLevel%9!=0){
        sprintf(levelNumberChar, "%d:%d",cLevel/9+1,cLevel%9);
    }else{
        sprintf(levelNumberChar, "%d:%d",cLevel/9,9);
    }
    
    _labelLevel->setString(levelNumberChar);

    
    //更新显示图形的排列模式
    int num=random(1, 6);
    ValueVector shapeVV=LevelData::paeseLevelShape(num).asValueVector();
    
    //从json中取出小图
    ValueVector avm=LevelData::paeseLevelSmallPicture(cLevel).asValueVector();

    for (int i=0; i<spriteVector.size(); i++) {
        char s[10];
        sprintf(s, "s%d", i+1);
        int ss =shapeVV.at(0).asValueMap()[s].asInt();
        int pX=ss/100;
        int pY=ss%100;
        
        //添加图片
        ResolvePicture* rp=(ResolvePicture*)spriteVector.at(i);
        rp->setScale(0.8*visibleSize.width/640);
        rp->setPicturePosition(origin.x+visibleSize.width*pX*0.01, origin.y + visibleSize.height*pY*0.01);
        rp->savePicturePosition(rp->getPosition());
        std::stringstream name; string color="";int randNumber;
        if (cLevel>9) {
            if (i<4) {
                int randName=random(0, 2);
                int mPicID =avm.at(i+randName*4).asValueMap()["id"].asInt();
                std::string mPicName =avm.at(i+randName*4).asValueMap()["pictureName"].asString();
                name<<mPicName<<mPicID<<".png";
                //Texture2D* texture = TextureCache::sharedTextureCache()->addImage(name.str());
                rp->ID=mPicID;
                rp->setTexture(name.str());
            }else{
                randNumber=random(1, 6);//随机图片
                name<<"gamescene/t"<<randNumber<<".png";
                rp->ID=randNumber;
                rp->setTexture(name.str());
            }
        }else{
            if (i<avm.size()) {
                int mPicID =avm.at(i).asValueMap()["id"].asInt();
                randNumber=mPicID;
                string picName;
                picName=avm.at(i).asValueMap()["pictureName"].asString();
                //Texture2D* texture = TextureCache::sharedTextureCache()->addImage(picName);
                rp->ID=randNumber;
                rp->setTexture(picName);
            }else{
                randNumber=random(1, 8);//随机图片
                name<<"gamescene/n"<<randNumber<<".png";
                rp->ID=randNumber;
                rp->setTexture(name.str());
            }
        }
        
        Sprite* dzty=(Sprite*)dizuoTouyingVector.at(i);
        if (cLevel>9) {
            //背景
            _gameBG->setTexture("gamescene/gameBG.png");
            //左上角 环
            _noMoveSprite->setTexture("gamescene/huan2.png");
            //圈
            _spriteQuan->setTexture("gamescene/quan3.png");
            //指针
            _spriteTiao->setTexture("gamescene/zhizhenBG2.png");
            //进度条背景
            _ruling->setTexture("gamescene/powerBarBG2.png");
            //底座投影
            dzty->setTexture("gamescene/foundation5.png");
            dzty->setPosition(Vec2(origin.x+visibleSize.width*pX*0.01, origin.y + visibleSize.height*pY*0.01-visibleSize.height*smartRes_dzty));
        }else{
            //更换背景图片
            char bgName[40];
            sprintf(bgName, "gamescene/gameBG%d.png",num);
            _gameBG->setTexture(bgName);
            //底座投影
            dzty->setPosition(Vec2(origin.x+visibleSize.width*pX*0.01, origin.y + visibleSize.height*pY*0.01-visibleSize.height*smartRes_dzty));
            //左上角 环
            _noMoveSprite->setTexture("gamescene/huan1.png");
            //圈
            _spriteQuan->setTexture("gamescene/quan2.png");
            //指针
            _spriteTiao->setTexture("gamescene/zhizhenBG1.png");
            //进度条背景
            _ruling->setTexture("gamescene/powerBarBG1.png");

        }
        
        }
    

    std::string bigPicName;
    
    //添加隐藏小图（从json文件中获取）
    ValueVector picVV=LevelData::paeseXml(cLevel).asValueVector();
    hiddenPictureVector.clear();//清空Vector
    for (int i=0; i<picVV.size(); i++) {
        int _inttag =picVV.at(i).asValueMap()["inttag"].asInt();
        int picId=_inttag;
        std::string name =picVV.at(i).asValueMap()["picName"].asString();
        int px =picVV.at(i).asValueMap()["positionX"].asInt();
        int py =picVV.at(i).asValueMap()["positionY"].asInt();
        int rotation=picVV.at(i).asValueMap()["rotation"].asInt();
        //大图从json文件中获得
        if (_inttag>1000) {
            bigPicName=name;
        }else{
            ResolvePicture* rp=ResolvePicture::createResolvePicture();
            rp->setScale(visibleSize.width*smartRes_hiddenPicScale/58);
            rp->initResolvePicture(name, picId);
            rp->setPicturePosition(visibleSize.width*px*0.001, visibleSize.height*py*0.001);
            rp->setRotation(rotation);
            //this->addChild(rp,3);
            //rp->setVisible(false);
            hiddenPictureVector.pushBack(rp);
        }
    }
    //添加大图
    _wholePicture->setTexture(bigPicName);
    //判断本关模式
    judgeCurrentLevelPattern(cLevel);
    
}

void GameScene::updateToOriginalState()
{
    Director* director=Director::getInstance();
    
    director->getActionManager()->removeAllActionsFromTarget(_spriteQuan);//暂停所有的动作
    _spriteQuan->setPosition(Vec2(visibleSize.width/2, visibleSize.height*0.1)); 
    _spriteQuan->setZOrder(3);
    _spriteQuan->setOpacity(255);
    _spriteQuan->setScale(QUAN_SCA);
    _spriteQuan->setRotation(0);
    
    this->removeChildByTag(124);
    this->removeChildByTag(125);
    
}

void GameScene::resetGame(EventCustom* e)
{
    updateToOriginalState();
    char getPropSql[100];
    sprintf(getPropSql, "select * from Prop ");
    Value propAvm=DataUtil::getRow(getPropSql);
    int cieclePropNumber=propAvm.asValueMap()["circleProp"].asInt();
    _loopNumber=cieclePropNumber;
    _isTouch=true;
    _isTaoZhong=false;
    SimpleAudioEngine::getInstance()->rewindBackgroundMusic();//重新开始播放背景音乐
    sprintf(_loopNumberLabel, "%d",_loopNumber);
    labelNumber->setString(_loopNumberLabel);
    Director::getInstance()->resume();
    _powerProgress->setPercentage(0);//将力度条的值归0
    _dottedLineProgress2->setVisible(false);//将上次轨迹线隐藏
    
    
    //更新关卡数字
    char levelNumberChar[20];
    if(cLevel%9!=0){
        sprintf(levelNumberChar, "%d:%d",cLevel/9+1,cLevel%9);
    }else{
        sprintf(levelNumberChar, "%d:%d",cLevel/9,9);
    }

    _labelLevel->setString(levelNumberChar);
    
    //清空showPictureVector
    int picNumber=(int)showPictureVector.size();
    for (int i=0; i<picNumber; i++) {
        ResolvePicture* rp=(ResolvePicture*)showPictureVector.at(i);
        this->removeChild(rp);
        
    }
    hiddenPictureVector.clear();//清空Vector
    
    //更新显示图形的排列模式
    int num=random(1, 6);
    ValueVector shapeVV=LevelData::paeseLevelShape(num).asValueVector();

    //从json中取出小图
    ValueVector avm=LevelData::paeseLevelSmallPicture(cLevel).asValueVector();
    
    for (int i=0; i<spriteVector.size(); i++) {
        char s[10];
        sprintf(s, "s%d", i+1);
        int ss =shapeVV.at(0).asValueMap()[s].asInt();
        int pX=ss/100;
        int pY=ss%100;
        //刷新图片
        ResolvePicture* rp=(ResolvePicture*)spriteVector.at(i);
        rp->setScale(0.8*visibleSize.width/640);
        rp->setPicturePosition(origin.x+visibleSize.width*pX*0.01, origin.y + visibleSize.height*pY*0.01);
        rp->savePicturePosition(rp->getPosition());
        std::stringstream name; string color="";int randNumber;
        
        if (cLevel>9) {
            if (i<4) {
                int randName=random(0, 2);
                int mPicID =avm.at(i+randName*4).asValueMap()["id"].asInt();
                std::string mPicName =avm.at(i+randName*4).asValueMap()["pictureName"].asString();
                name<<mPicName<<mPicID<<".png";
                rp->ID=mPicID;
                rp->setTexture(name.str());
            }else{
                randNumber=random(1, 6);//随机图片
                name<<"gamescene/t"<<randNumber<<".png";
                rp->ID=randNumber;
                rp->setTexture(name.str());
            }
        }else{
            if (i<avm.size()) {
                int mPicID =avm.at(i).asValueMap()["id"].asInt();
                randNumber=mPicID;
                string picName;
                picName=avm.at(i).asValueMap()["pictureName"].asString();
                rp->ID=randNumber;
                rp->setTexture(picName);
            }else{
                randNumber=random(1, 8);//随机图片
                name<<"gamescene/n"<<randNumber<<".png";
                rp->ID=randNumber;
                rp->setTexture(name.str());
            }
        }
        rp->setOpacity(255);
        
        Sprite* dzty=(Sprite*)dizuoTouyingVector.at(i);
        if (cLevel>9) {
            //背景
            _gameBG->setTexture("gamescene/gameBG.png");
            //左上角 环
            _noMoveSprite->setTexture("gamescene/huan2.png");
            //圈
            _spriteQuan->setTexture("gamescene/quan3.png");
            //指针
            _spriteTiao->setTexture("gamescene/zhizhenBG2.png");
            //进度条背景
            _ruling->setTexture("gamescene/powerBarBG2.png");
            //底座投影
            dzty->setTexture("gamescene/foundation5.png");
            dzty->setPosition(Vec2(origin.x+visibleSize.width*pX*0.01, origin.y + visibleSize.height*pY*0.01-visibleSize.height*smartRes_dzty));
        }else{
            
            //更换背景图片
            char bgName[40];
            sprintf(bgName, "gamescene/gameBG%d.png",num);
            _gameBG->setTexture(bgName);
            //底座投影
            dzty->setTexture("gamescene/foundation.png");
            dzty->setPosition(Vec2(origin.x+visibleSize.width*pX*0.01, origin.y + visibleSize.height*pY*0.01-visibleSize.height*smartRes_dzty));
            //左上角 环
            _noMoveSprite->setTexture("gamescene/huan1.png");
            //圈
            _spriteQuan->setTexture("gamescene/quan2.png");
            //指针
            _spriteTiao->setTexture("gamescene/zhizhenBG1.png");
            //进度条背景
            _ruling->setTexture("gamescene/powerBarBG1.png");
        }
    }
    
    std::string bigPicName;
    
    //添加隐藏小图和大图（从json文件中获取）
    ValueVector picVV=LevelData::paeseXml(cLevel).asValueVector();
    
    for (int i=0; i<picVV.size(); i++) {
        int _inttag =picVV.at(i).asValueMap()["inttag"].asInt();
        int picId=_inttag;
        std::string name =picVV.at(i).asValueMap()["picName"].asString();
        int px =picVV.at(i).asValueMap()["positionX"].asInt();
        int py =picVV.at(i).asValueMap()["positionY"].asInt();
        int rotation=picVV.at(i).asValueMap()["rotation"].asInt();
        //大图从json文件中获得
        if (_inttag>1000) {
            bigPicName=name;
        }else{
            ResolvePicture* rp=ResolvePicture::createResolvePicture();
            rp->setScale(visibleSize.width*smartRes_hiddenPicScale/58);
            rp->initResolvePicture(name, picId);
            rp->setPicturePosition(visibleSize.width*px*0.001, visibleSize.height*py*0.001);
            rp->setRotation(rotation);
            //rp->setVisible(false);
            //this->addChild(rp,3);
            hiddenPictureVector.pushBack(rp);
        }
    }
    //添加大图
    _wholePicture->setTexture(bigPicName);
    //判断本关模式
    judgeCurrentLevelPattern(cLevel);

}


bool GameScene::onTouchBegan(Touch *touch, Event *event)
{

    Director* director=Director::getInstance();
    director->getActionManager()->pauseTarget(GameScene::_spriteTiao);//暂停指针的动作
    director->getActionManager()->resumeTarget(_powerProgress);//继续力度条进度
    _powerProgress->setVisible(true);
    
//    if (_isHelp) {
//        _dottedLineProgress->setVisible(true);
//        _isHelp=false;
//    }
    
    //力度条的动作
    repeatPG=RepeatForever::create(Sequence::create(ProgressFromTo::create(1.0, 0.0f, 100.0f), ProgressFromTo::create(1.0, 100.0f, 0.0f), NULL));
    _progressTimerSpeed=Speed::create(repeatPG, _speedP);
    _powerProgress->runAction(_progressTimerSpeed);
    
    return true;
}

void GameScene::onTouchMoved(Touch *touch, Event *event)
{
    log("-----Move-------");
}

void GameScene::onTouchEnded(Touch *touch, Event *event)
{
    //暂停指针的旋转动作
    Director* director=Director::getInstance();
    director->getActionManager()->resumeTarget(GameScene::_spriteTiao);
    
    _powerProgress->setVisible(true);//显示指针的进度条
    director->getActionManager()->pauseTarget(_powerProgress);//暂停力度条进度
    //从数据库中取出用户信息,判断游戏模式
    int comeInLevel=UserDefault::getInstance()->getIntegerForKey("cLevel");
    char getUserSql[100];
    sprintf(getUserSql, "select * from User where level=%d",comeInLevel);
    cocos2d::Value cv=DataUtil::getRow(getUserSql);
    int pattern=cv.asValueMap()["pattern"].asInt();
    int yinXingNum=cv.asValueMap()["starNum"].asInt();
    if ((pattern==1&&yinXingNum==3)||pattern==2) {
        //虚线轨迹
        _dottedLineProgress2->setVisible(false);
    }else{
        //虚线轨迹
        _dottedLineProgress2->setVisible(true);
        _dottedLineProgress2->setRotation(_spriteTiao->getRotation());
        _dottedLineProgress2->setPercentage(_powerProgress->getPercentage());
    }
    
    if (_isTouch) {
        
        if (_spriteTiao->getRotation()>0) {
            float rr=sqrt(visibleSize.width/2*visibleSize.width/2+visibleSize.height*9/10*visibleSize.height*9/10);
            
            float r=_powerProgress->getPercentage()*0.01*rr;
            float x1=r*cos((90-_spriteTiao->getRotation())*3.1415926/180);
            float y1=r*sin((90-_spriteTiao->getRotation())*3.1415926/180);
            if (y1<0) {
                y1=-y1;
            }
            y=y1+visibleSize.height/10;
            x=x1+visibleSize.width/2;
        }else{
            float rr=sqrt(visibleSize.width/2*visibleSize.width/2+visibleSize.height*9/10*visibleSize.height*9/10);
            float r=_powerProgress->getPercentage()*0.01*rr;
            float x1=r*cos((90+_spriteTiao->getRotation())*3.1415926/180);
            float y1=r*sin((90+_spriteTiao->getRotation())*3.1415926/180);
            if (y1<0) {
                y1=-y1;
            }
            y=y1+visibleSize.height/10;
            x=visibleSize.width/2-x1;
        }
        float s=sqrtf((x*x+y*y)-(_spriteQuan->getPositionX()*getPositionX()+getPositionY()*getPositionY()));
        _isTouch=false;
        
        if ((pattern==1&&yinXingNum==3)||pattern==2) {
            //进度条的值归0
            _powerProgress->setPercentage(0);
            
        }
        //下面是圈子飞行
        
        int t_id=-1;  //套中得id，目的是为了修正飞行轨迹
        for (int i=0; i<spriteVector.size(); i++)
        {
            //判断是否套住
            ResolvePicture* showRp=spriteVector.at(i);
            if (sqrt((x-showRp->getPositionX())*(x-showRp->getPositionX())+(y-showRp->getPositionY())*(y-showRp->getPositionY()))<=35.0)
            {
                t_id=i;
                
            }
        }
        Vec2 quanMove_endpoint=(t_id==-1)? Vec2(x,y):spriteVector.at(t_id)->getPosition();
        MoveTo* quanMove=MoveTo::create(s/(visibleSize.width*1.3), quanMove_endpoint);
        auto quanRate = Spawn::create(quanMove,Sequence::create(ScaleTo::create(s/(visibleSize.width*1.3),QUAN_SCA,QUAN_SCA*0.5), NULL),  NULL);
        auto ease=EaseSineOut::create(quanRate);
        
        
        auto mfunc =CallFunc::create ( CC_CALLBACK_0(GameScene::spriteQuanMoveCallBack, this) );
        _spriteQuan->runAction(Sequence::create(ease, mfunc, NULL));
        return ;
        
    }
    
}

void GameScene::spriteQuanMoveCallBack()
{
    ResolvePicture* taozhong=NULL;
    
    ResolvePicture* taozhong_heshi=NULL;
    for (int i=0; i<spriteVector.size(); i++)
    {
        //判断是否套住
        ResolvePicture* showRp=spriteVector.at(i);
        if (sqrt((x-showRp->getPositionX())*(x-showRp->getPositionX())+(y-showRp->getPositionY())*(y-showRp->getPositionY()))<=35.0)
        {
            taozhong=showRp;
            
            
            showRp->isCover=true;
            for (int j=0; j<hiddenPictureVector.size(); j++) {
                ResolvePicture* hiddenRp=hiddenPictureVector.at(j);
                if (hiddenRp->ID==showRp->ID)
                {
                    taozhong_heshi=hiddenRp;
                    hiddenPictureVector.eraseObject(hiddenRp);
                    showPictureVector.pushBack(taozhong_heshi);
                    break;
                }
            }
        }
    }
    
    
    auto spriteQuan_return  = TargetedAction::create(_spriteQuan,Place::create(Vec2(visibleSize.width/2, visibleSize.height*0.1)));
    auto menuItemBlink=Spawn::create(JumpBy::create(0.6f, Vec2(0,50), 50, 1),FadeTo::create(0.6f, 0), NULL);
    auto targetAct = TargetedAction::create(taozhong,menuItemBlink);
    
    
    
    if(taozhong != NULL && taozhong_heshi!=NULL)
    {
        ParticleSystem * p4=ParticleGalaxy::createWithTotalParticles(200);
        p4->setPosition(Vec2(taozhong->getPositionX(),taozhong->getPositionY()+50));
        p4->setStartColor(Color4F(1,1,1,1));
        this->addChild(p4,5);
        p4->setVisible(false);
        
        auto p5 = MotionStreak::create(0.2, 1, 100, Color3B::WHITE,"gamescene/start5.png" );
        p5->setPosition(Vec2(taozhong->getPositionX(),taozhong->getPositionY()+50));
        p5->setVisible(false);
        p5->isFastMode();
        this->addChild(p5,5);
        
        _spriteQuan->runAction(Sequence::create(CallFunc::create([=]{_spriteQuan->setZOrder(1);}),MoveBy::create(0.3, Vec2(0,-30)),FadeTo::create(0.2, 0),targetAct,spriteQuan_return,
                                                CallFunc::create([=]{_spriteQuan->setZOrder(3);}),
                                                CallFunc::create([=](){
            _spriteQuan->setOpacity(255);
            _spriteQuan->setScale(QUAN_SCA);
            _spriteQuan->setRotation(0);
            taozhong->setPosition(taozhong->getPositionX(),taozhong->getPositionY()-50);
            
            p5->setVisible(true);
            p4->setVisible(true);
            
            p4->runAction(MoveTo::create(0.3, taozhong_heshi->getPosition()));
            p5->runAction(MoveTo::create(0.3, taozhong_heshi->getPosition()));
            taozhong->changPicture(cLevel);
            
        }),DelayTime::create(0.5), //等p4结束哦 0.5秒
                                                CallFunc::create([=](){
            taozhong->setVisible(true);
            taozhong->setOpacity(255);
            addChild(taozhong_heshi,3);
            taozhong_heshi->setOpacity(0);
            
            taozhong_heshi->runAction(FadeTo::create(0.5, 255));
            removeChild(p4,p5);
            
            this->scheduleOnce(SEL_SCHEDULE(&GameScene::enterIntoSucceedUI), 1.0f);
            
            if(--_loopNumber>0){
                _isTouch=true;
                //判断圈数，来确定是否减少体力
                UserDefault::getInstance()->setBoolForKey("isReduceEnergy", true);
                
            }}),NULL));
    }
    else if (taozhong != NULL)
    {
        
        
        auto targetAct = TargetedAction::create(taozhong,Sequence::create(MoveBy::create(0.05, Vec2(-15,0)),MoveBy::create(0.1, Vec2(30,0)), MoveBy::create(0.05, Vec2(-15,0)),NULL));
        _spriteQuan->runAction(Sequence::create(CallFunc::create([=]{_spriteQuan->setZOrder(1);}),
                                                MoveBy::create(0.3, Vec2(0,-30)),
                                                FadeTo::create(0.2, 0),spriteQuan_return,
                                                CallFunc::create([=]{_spriteQuan->setZOrder(3);}),
                                                Repeat::create(targetAct,1),
                                                CallFunc::create([=](){_spriteQuan->setOpacity(255);_spriteQuan->setScale(QUAN_SCA);_spriteQuan->setRotation(0);
            taozhong->setPosition(taozhong->getPositionX(),taozhong->getPositionY());
            _spriteQuan->setPosition(Vec2(visibleSize.width/2, visibleSize.height*0.1));
            if(--_loopNumber>0){
                _isTouch=true;
                //判断圈数，来确定是否减少体力
                UserDefault::getInstance()->setBoolForKey("isReduceEnergy", true);
            }
        }),NULL));
    }else
    {
        
        _spriteQuan->runAction(Sequence::create(FadeTo::create(0.2, 0),spriteQuan_return,
                                                CallFunc::create([=](){
            _spriteQuan->setOpacity(255);
            _spriteQuan->setRotation(0);
            _spriteQuan->setScale(QUAN_SCA);
            if(--_loopNumber>0){
                _isTouch=true;
                //判断圈数，来确定是否减少体力
                //if (_loopNumber<10) {
                UserDefault::getInstance()->setBoolForKey("isReduceEnergy", true);
                // }else
                //   UserDefault::getInstance()->setBoolForKey("isReduceEnergy", false);
                
            }}),NULL));
        log("啥都没有中。回来吧");
        log("在循环里面圈子的数目是%d",_loopNumber);
    }
    log("-----End-------x= %f y=%f ",x,y);
    
    
    if (_loopNumber>0) {
        sprintf(_loopNumberLabel, "%d",_loopNumber-1);
        labelNumber->runAction(Sequence::create(ScaleTo::create(0.5, 1.0*visibleSize.width/640.0),
                                                CallFunc::create([=](){labelNumber->setString(_loopNumberLabel);}), ScaleTo::create(0.5, 0.6*visibleSize.width/640.0),       NULL));
        
    }else
        _isTouch=false;
    
    
    
    
}

void GameScene::onTouchCancelled(Touch *touch, Event *event)
{}

void GameScene::update(float dt)
{
   if ((hiddenPictureVector.size()>0&&_loopNumber==0)||(hiddenPictureVector.size()>8&&_loopNumber==0))
    {   log("这里进入失败界面2");
        this->scheduleOnce(SEL_SCHEDULE(&GameScene::enterIntoFailedUI), 1.0f);
        
    }

}

void GameScene::updateTime(float dt)
{
    //Vec2 v2=spriteVector.at(0)->getPosition();
    Vec2 v2=spriteVector.at(0)->PPOINT;
    for (int i=0; i<9; i++) {
        
//        Sprite* s1=spriteVector.at(i);
//        if (i!=8) {
//            s1->setPosition(spriteVector.at(i+1)->getPosition());
//        }else{
//            s1->setPosition(v2);
//        }
        if (i!=8) {
            spriteVector.at(i)->runAction(MoveTo::create(0.2,spriteVector.at(i+1)->PPOINT));
            spriteVector.at(i)->savePicturePosition(spriteVector.at(i+1)->PPOINT);
        }else{
            spriteVector.at(i)->runAction(MoveTo::create(0.2,v2));
            spriteVector.at(i)->savePicturePosition(v2);
        }

        
    }

}

ValueVector GameScene::calculationSatrNumber(int quanNumber,int picNumber)
{
    ValueVector starVV;
    int star=quanNumber*0.618;int star3=0;int star2=0;
    switch (picNumber) {
        case 2:
            star3=star-1;
            break;
        case 3:
            star3=star;
            break;
        case 4:
            star3=star+1;
            break;
        default:
            break;
    }
    switch (quanNumber) {
        case 10:
            star2=star3+2;
            break;
        case 15:
            star2=star3+3;
            break;
        case 20:
            star2=star3+4;
            break;
        default:
            break;
    }
    
    starVV.push_back(Value(star3));//3星
    starVV.push_back(Value(star2));//2星
    
    //log("%d   %d",star3,star2);
    
    return starVV;
}

void GameScene::enterIntoSucceedUI()
{
    //套完所有图片执行

    if ((hiddenPictureVector.size()==0&&getChildByName("succeedLayer")==NULL)||(hiddenPictureVector.size()==8&&getChildByName("succeedLayer")==NULL)) {
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
        int oldStarNum=cv.asValueMap()["starNum"].asInt();//从数据库取出星星的个数
        
        SimpleAudioEngine::getInstance()->stopBackgroundMusic();//停止背景音乐
        DataUtil::updateSuoData(false, cLevel+1);//下一关解锁
        int starNum=0;
        char getPropSql[100];
        sprintf(getPropSql, "select * from Prop ");
        Value propAvm=DataUtil::getRow(getPropSql);
        int circlePropNumber=propAvm.asValueMap()["circleProp"].asInt();
        ValueVector starVV=calculationSatrNumber(circlePropNumber,picNumber);
        int starNumber3=starVV.at(0).asInt();
        int starNumber2=starVV.at(1).asInt();
        if (picNumber==1) {
            starNum=3;
        }else{
            if ((circlePropNumber-_loopNumber)<=starNumber3) {
                starNum=3;
            }
            else if ((circlePropNumber-_loopNumber)>starNumber3&&(circlePropNumber-_loopNumber)<=starNumber2){
                starNum=2;
            }else {
                starNum=1;
            }
        }
       
        UserDefault::getInstance()->setIntegerForKey("cLevelXingNumber", starNum);
        bool isGengxin=UserDefault::getInstance()->getBoolForKey("isGengxin");
        if(isGengxin)
        {
            DataUtil::updateStarData(starNum, cLevel);//更新星星的数量
            UserDefault::getInstance()->setBoolForKey("isGengxin",false);
        }else if (starNum>oldStarNum) {
            DataUtil::updateStarData(starNum, cLevel);//更新星星的数量
        }
        Director::getInstance()->pause();//暂停游戏
        //添加过关层
        _succeedLayer=ShadeLayer::create();
        _succeedLayer->init();
        this->addChild(_succeedLayer,100,"succeedLayer");
        log("%%%%%%%%%%%%");
    }


}
void GameScene::enterIntoFailedUI()
{
    if (_loopNumber==0) {
        //判断失败层是否为空
        if (getChildByName("failedLayer")==NULL&&getChildByName("succeedLayer")==NULL) {
            //移除本关套住的图片
            for (int i=0; i<showPictureVector.size(); i++) {
                ResolvePicture* rp=(ResolvePicture*)showPictureVector.at(i);
                this->removeChild(rp);
            }
            showPictureVector.clear();
            SimpleAudioEngine::getInstance()->stopBackgroundMusic();//停止背景音乐
            Director::getInstance()->pause();//暂停游戏
            //添加失败层
            _failLayer=FailedShadeLayer::create();
            _failLayer->init();
            this->addChild(_failLayer,100,"failedLayer");
            
        }

    }
    
}


void GameScene::menuPauseCallback(Ref* pSender)
{
    bool isSound=UserDefault::getInstance()->getBoolForKey("isSound");
    if (isSound) {
    SimpleAudioEngine::getInstance()->playEffect("musicAndeffect/buttonEffect.wav");
    }
    
    Director::getInstance()->pause();
    _pauseLayer=PauseLayer::create();
    _pauseLayer->init();
    this->addChild(_pauseLayer,3);
    
}
//增加圈按钮回调方法
void GameScene::menuAddQuanCallback(Ref* pSender)
{
    char getUserSql[100];
    sprintf(getUserSql, "select * from Prop ");
    Value avm=DataUtil::getRow(getUserSql);
    int quanNumber=avm.asValueMap()["circleProp"].asInt();
    DataUtil::updatePropData("circleProp", quanNumber+5);
    
    char totalQuan[10];
    sprintf(totalQuan, "%d",quanNumber+5);
    _totalQuanNumber->setString(totalQuan);
    
    _loopNumber=_loopNumber+5;
    char quanNum[10];
    sprintf(quanNum, "%d",_loopNumber);
    labelNumber->setString(quanNum);
}

////重新开始按钮回调方法
//void GameScene::menuResartCallback(cocos2d::Ref* pSender)
//{
//    EventCustom* e;
//    resetGame(e);
//
//}
//帮助按钮回调方法
void GameScene::menuHelpCallback(Ref* pSender)
{
    bool isSound=UserDefault::getInstance()->getBoolForKey("isSound");
    if (isSound) {
        SimpleAudioEngine::getInstance()->playEffect("musicAndeffect/buttonEffect.wav");
    }
//    if (!_dottedSprite->isVisible()) {
//        if (_helpNumber>0) {
//            _helpNumber--;
//            _isHelp=true;
//            _dottedSprite->setVisible(true);
//            DataUtil::updatePropData("fileProp", _helpNumber);
//            char _helpNumberLabel[10];
//            sprintf(_helpNumberLabel, ":%d",_helpNumber);
//            _labelHelpNumber->setString(_helpNumberLabel);
//        }else{
//            log("帮助道具数量不足");
//            Director::getInstance()->pause();
//            Scene* shopScene=ShoppingMall::createScene();
//            Director::getInstance()->pushScene(shopScene);
//        }
//
//    }
    
    
}


GameScene::~GameScene()
{
    _eventDispatcher->removeCustomEventListeners("succeefulUI");
    _eventDispatcher->removeCustomEventListeners("failedUI");
    _eventDispatcher->removeCustomEventListeners("ThisLevelGold");
    _eventDispatcher->removeCustomEventListeners("backRestartGame");
    _eventDispatcher->removeCustomEventListeners("succeedResatrt");

}

void GameScene::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
}
void GameScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
    switch (keyCode)
    {
        case cocos2d::EventKeyboard::KeyCode::KEY_BACK:
        {
            if(_IsNeedExit == false)
            {
                _IsNeedExit = true;
                this->scheduleOnce(SEL_SCHEDULE(&GameScene::CloseExitSign),5.0f);
            }
            else
            {
                menuCloseCallback(nullptr);
            }
        }
        default:
            break;
    }

}

void GameScene::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
    MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif
//    Single::getInstance()->stop();
//    //更新时间
//    DataUtil::updatePropData("month", Single::getInstance()->getLocalMonth());
//    DataUtil::updatePropData("day", Single::getInstance()->getLocalDay());
//    DataUtil::updatePropData("monute", Single::getInstance()->getLocalMinute());
//    DataUtil::updatePropData("hour", Single::getInstance()->getLocalHour());
    //最后别忘了关闭数据库哦
    DataUtil::closeDB();
    SimpleAudioEngine::getInstance()->end();//关闭音乐
    Director::getInstance()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
    
}

//定时器回调 退出标志关闭
void GameScene::CloseExitSign(float dt)
{
    _IsNeedExit = false;
}

