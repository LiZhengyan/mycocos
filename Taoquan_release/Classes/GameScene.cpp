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
    MenuItemImage*pauseItem = MenuItemImage::create("gamescene/pauseButton.png","gamescene/pauseButton.png",
                                           CC_CALLBACK_1(GameScene::menuPauseCallback, this));
    pauseItem->setScale(visibleSize.width*0.9/640);
    pauseItem->setPosition(Vec2(visibleSize.width*0.9,origin.y + visibleSize.height*0.94));
    
    //帮助按钮
    /*auto helpItem = MenuItemImage::create("gamescene/helpButton.png","gamescene/helpButton.png",
                                          CC_CALLBACK_1(GameScene::menuHelpCallback, this));
    
    helpItem->setPosition(Vec2(origin.x +visibleSize.width*0.1,origin.y + visibleSize.height*0.94));
    helpItem->setScale(visibleSize.width*0.9/640);*/
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
    _loopNumber=circlePropNumber;
    char circleNumberChar[10];
    sprintf(circleNumberChar, ":%d",_loopNumber);
    labelNumber = LabelAtlas::create(circleNumberChar, "gamescene/shuzi2.png", 27.0f, 40.0f, '0');
    labelNumber->setScale(visibleSize.width/640.0);
    //labelNumber->setPosition(Vec2(origin.x + visibleSize.width*0.84,origin.y + visibleSize.height*0.062));
    labelNumber->setPosition(Vec2(origin.x + visibleSize.width*0.15,origin.y + visibleSize.height*0.91));
    this->addChild(labelNumber, 1);
    //添加不动圈
    auto noMoveSprite = Sprite::create("gamescene/huan.png");
    noMoveSprite->setScale(visibleSize.width*0.5/640.0);
    //noMoveSprite->setPosition(Vec2(origin.x + visibleSize.width*0.78, origin.y + visibleSize.height*0.08));
    noMoveSprite->setPosition(Vec2(origin.x + visibleSize.width*0.1, origin.y + visibleSize.height*0.94));
    this->addChild(noMoveSprite, 1);

    
    
    
    // create menu, it's an autorelease object
    auto menu = Menu::create(pauseItem, NULL);
    menu->setPosition(Vec2::ZERO);
    
    this->addChild(menu, 1);

    
    //添加圈
    if (cLevel>18) {
        _spriteQuan=Sprite::create("gamescene/quan3.png");
    }else
        _spriteQuan=Sprite::create("gamescene/quan2.png");
    _spriteQuan->setScale(0.8*visibleSize.width/640);
    _spriteQuan->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height*0.1 + origin.y));
    this->addChild(_spriteQuan,3);
    
    QUAN_SCA=0.8*visibleSize.width/640;
    
    //刻度
    _ruling=Sprite::create("gamescene/kedu.png");
    _ruling->setScale(0.7*visibleSize.width/640);
    _ruling->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height*0.255 + origin.y));
    _ruling->setVisible(false);
    this->addChild(_ruling,2);
    //添加力度和角度
    _labelAngle = LabelAtlas::create("0", "gamescene/shuzi2.png", 27.0f, 40.0f, '0');
    _labelAngle->setScale(visibleSize.width/640.0);
    _labelAngle->setPosition(Vec2(origin.x + visibleSize.width*0.8,origin.y + visibleSize.height*0.25));
    _labelAngle->setVisible(false);
    this->addChild(_labelAngle, 1);
    
    _labelPower = LabelAtlas::create("0", "gamescene/shuzi2.png", 27.0f, 40.0f, '0');
    _labelPower->setScale(visibleSize.width/640.0);
    _labelPower->setPosition(Vec2(origin.x + visibleSize.width*0.2,origin.y + visibleSize.height*0.25));
    _labelPower->setVisible(false);
    this->addChild(_labelPower, 1);
    //上次套圈轨迹虚线
    _dottedLineProgress2=ProgressTimer::create(Sprite::create("gamescene/dottedLine.png"));
    _dottedLineProgress2->setScale(visibleSize.width*0.85/640);
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
        _ruling->setVisible(true);
        _labelAngle->setVisible(true);
        _labelPower->setVisible(true);
        _speed=2.0;
    }else if(pattern==2){
        _speed=1.5;
        
    }else if(pattern==1&&yinXingNum==3){
        _speed=1.5;
        DataUtil::updatePatternData(2,cLevel);//更新游戏模式
        UserDefault::getInstance()->setBoolForKey("isGengxin", true);
    }
    
    
    //从json文件中随机取出一种图片摆放形状
    int randNum=random(1, 6);
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
                std::string mPicName =picVV.at(i).asValueMap()["pictureName"].asString();
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
//        Sprite* dizuo=Sprite::create("gamescene/foundation.png");
//        dizuo->setScale(0.7*visibleSize.width/640);
//        dizuo->setPosition(Vec2(origin.x+visibleSize.width*pX*0.01, origin.y + visibleSize.height*0.91*pY*0.01));
//        this->addChild(dizuo, 1);
//        dizuoVector.pushBack(dizuo);
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
    //指针
    _spriteTiao=Sprite::create("gamescene/zhizhenBG.png");
    _spriteTiao->setScale(0.7*visibleSize.width/640);
    _spriteTiao->setRotation(45);
    _spriteTiao->setTag(1);
    _spriteTiao->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height*0.1 + origin.y));
    _spriteTiao->setAnchorPoint(Vec2(0.5,0));
    this->addChild(_spriteTiao, 0);
    //虚线指针
    _dottedSprite=Sprite::create("gamescene/dottedLine.png");
    _dottedSprite->setScale(0.9*visibleSize.width/640);
    _dottedSprite->setRotation(45);
    _dottedSprite->setTag(1);
    _dottedSprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height*0.1 + origin.y));
    _dottedSprite->setAnchorPoint(Vec2(0.5,0));
    this->addChild(_dottedSprite, 3);
    _dottedSprite->setVisible(false);
    
    

    //旋转
    RotateTo* rotate1= RotateTo::create(_speed,-45.0);
    RotateTo* rotate2 = RotateTo::create(_speed,45.0);
    Sequence* sequenceBG=Sequence::create(rotate1, rotate2, NULL);
    RepeatForever* repeatBG=RepeatForever::create(sequenceBG);
    repeatBG->setTag(1000);
    _spriteTiao->runAction(repeatBG);
    
    auto lineRotate1= RotateTo::create(_speed,-45.0);
    auto lineRotate2= RotateTo::create(_speed,45.0);
    auto sequenceLineBG=Sequence::create(lineRotate1, lineRotate2, NULL);
    _repeatLineBG=RepeatForever::create(sequenceLineBG);
    _repeatLineBG->setTag(1001);
    _dottedSprite->runAction(_repeatLineBG);
    //添加虚线进度条
    _dottedLineProgress=ProgressTimer::create(Sprite::create("gamescene/dottedLine.png"));
    _dottedLineProgress->setScale(visibleSize.width*0.9/640);
    _dottedLineProgress->setTag(2);
    _dottedLineProgress->setRotation(0);
    
    _dottedLineProgress->setAnchorPoint(Vec2(0.5,0));
    _dottedLineProgress->setBarChangeRate(Point(0,1));
    _dottedLineProgress->setType(ProgressTimer::Type::BAR);
    _dottedLineProgress->setMidpoint(Point(0,0));
    _dottedLineProgress->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height*0.1 + origin.y));
    _dottedLineProgress->setPercentage(0.0f);
    this->addChild(_dottedLineProgress,3);
    _repeatLineBG->setTag(2000);
    
   _dottedLineProgress->setVisible(false);

    
    //添加进度条
    _powerProgress=ProgressTimer::create(Sprite::create("gamescene/powerBar.png"));
    _powerProgress->setScale(0.7*visibleSize.width/640);
    _powerProgress->setTag(2);
    _powerProgress->setRotation(45);
    
    _powerProgress->setAnchorPoint(Vec2(0.5,0));
    _powerProgress->setBarChangeRate(Point(0,1));
    _powerProgress->setType(ProgressTimer::Type::BAR);
    _powerProgress->setMidpoint(Point(0,0));
    _powerProgress->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height*0.1 + origin.y));
    _powerProgress->setPercentage(0.0f);
    this->addChild(_powerProgress,0);
    _powerProgress->setVisible(false);
    
    
    
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
    
    auto backSelectLevelCustomListener = EventListenerCustom::create("backSelectLevel", CC_CALLBACK_1(GameScene::backSelectLevel, this));
    _eventDispatcher->addEventListenerWithFixedPriority(backSelectLevelCustomListener, 1);


    //注册捕捉监听
    auto listenerkeyPad = EventListenerKeyboard::create();
    listenerkeyPad->onKeyReleased = CC_CALLBACK_2(GameScene::onKeyReleased, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listenerkeyPad, this);
    
    
    
    //_eventDispatcher->removeAllEventListeners();
    return true;
}

std::string GameScene::randomChoosePictureColor(int num)
{
    string color;
    //随机颜色

    Texture2D* texture;
    do {
        switch (random(1, 5)) {
            case 1:
                color="gamescene/hong";
                break;
            case 2:
                color="gamescene/huang";
                break;
            case 3:
                color="gamescene/ju";
                break;
            case 4:
                color="gamescene/lan";
                break;
            case 5:
                color="gamescene/zi";
                break;
            default:
                break;
        }
        
        std::stringstream filename;
        filename<<color<<num<<".png";
        texture= Director::getInstance()->getTextureCache()->addImage(filename.str());
        
        
    } while (!texture);
    return color;
}

//设置图片的摆放位置
void GameScene::setNextLevelPicture(EventCustom* e)
{
    Director::getInstance()->resume();
    
    _isTouch=true;
    SimpleAudioEngine::getInstance()->rewindBackgroundMusic();//重新开始播放背景音乐
    _isTaoZhong=false;
    char*buf =static_cast<char*>(e->getUserData());
     _loopNumber=std::atoi(buf);
    labelNumber->setString(buf);
   
    int num=random(1, 6);
    ValueVector shapeVV=LevelData::paeseLevelShape(num).asValueVector();
    cLevel++;
    UserDefault::getInstance()->setIntegerForKey("cLevel", cLevel);
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
        std::stringstream name; string color="";int randNumber;
        
        if (cLevel>9) {
            if (i<4) {
                int randName=random(0, 2);
                int mPicID =avm.at(i+randName*4).asValueMap()["id"].asInt();
                std::string mPicName =avm.at(i).asValueMap()["pictureName"].asString();
                name<<mPicName<<mPicID<<".png";
                Texture2D* texture = TextureCache::sharedTextureCache()->addImage(name.str());
                rp->ID=randNumber;
                rp->setTexture(texture);
            }else{
                randNumber=random(1, 6);//随机图片
                name<<"gamescene/t"<<randNumber<<".png";
                Texture2D* texture = TextureCache::sharedTextureCache()->addImage(name.str());
                rp->ID=randNumber;
                rp->setTexture(texture);
            }
        }else{
            if (i<avm.size()) {
                int mPicID =avm.at(i).asValueMap()["id"].asInt();
                randNumber=mPicID;
                string picName;
                picName=avm.at(i).asValueMap()["pictureName"].asString();
                Texture2D* texture = TextureCache::sharedTextureCache()->addImage(picName);
                rp->ID=randNumber;
                rp->setTexture(texture);
            }else{
                randNumber=random(1, 8);//随机图片
                name<<"gamescene/n"<<randNumber<<".png";
                Texture2D* texture = TextureCache::sharedTextureCache()->addImage(name.str());
                rp->ID=randNumber;
                rp->setTexture(texture);
            }
        }
        
        Sprite* dzty=(Sprite*)dizuoTouyingVector.at(i);
        Texture2D* textureDzty;Texture2D* textureBG;
        if (cLevel>9) {
            //背景
            textureBG = TextureCache::sharedTextureCache()->addImage("gamescene/gameBG.png");
            _gameBG->setTexture(textureBG);
            //圈
            Texture2D* textureQuan = TextureCache::sharedTextureCache()->addImage("gamescene/quan3.png");
            _spriteQuan->setTexture(textureQuan);
            //底座投影
            textureDzty = TextureCache::sharedTextureCache()->addImage("gamescene/foundation5.png");
            dzty->setTexture(textureDzty);
            dzty->setPosition(Vec2(origin.x+visibleSize.width*pX*0.01, origin.y + visibleSize.height*pY*0.01-visibleSize.height*smartRes_dzty));
        }else{
            //更换背景图片
            char bgName[40];
            sprintf(bgName, "gamescene/gameBG%d.png",num);
            textureBG = TextureCache::sharedTextureCache()->addImage(bgName);
            _gameBG->setTexture(textureBG);
            //底座投影
            textureDzty = TextureCache::sharedTextureCache()->addImage("gamescene/foundation.png");
            dzty->setTexture(textureDzty);
            dzty->setPosition(Vec2(origin.x+visibleSize.width*pX*0.01, origin.y + visibleSize.height*pY*0.01-visibleSize.height*smartRes_dzty));
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
    Texture2D* texture = TextureCache::sharedTextureCache()->addImage(bigPicName);
    _wholePicture->setTexture(texture);
    //判断本关模式
    char getUserSql[100];
    sprintf(getUserSql, "select * from User where level=%d",cLevel);
    
    //从数据库中取出用户信息
    cocos2d::Value cv=DataUtil::getRow(getUserSql);
    int pattern=cv.asValueMap()["pattern"].asInt();
    float rotateTime1;float rotateTime2;
    if (pattern==1) {
        _ruling->setVisible(true);
        _labelAngle->setVisible(true);
        _labelPower->setVisible(true);
        _labelAngle->setString("0");
        _labelPower->setString("0");
        _dottedLineProgress2->setVisible(false);
        rotateTime1=2.0;rotateTime2=2.0;
    }else{
        _ruling->setVisible(false);
        _labelAngle->setVisible(false);
        _labelPower->setVisible(false);
        _dottedLineProgress2->setVisible(false);
        rotateTime1=1.5;rotateTime2=1.5;
    }
    Director* director=Director::getInstance();
    director->getActionManager()->removeActionByTag(1000, _spriteTiao);
    director->getActionManager()->removeActionByTag(1001, _dottedSprite);
    
    RotateTo* rotate1= RotateTo::create(rotateTime1,-45.0);
    RotateTo* rotate2 = RotateTo::create(rotateTime2,45.0);
    Sequence* sequenceBG=Sequence::create(rotate1, rotate2, NULL);
    RepeatForever* repeatBG=RepeatForever::create(sequenceBG);
    repeatBG->setTag(1000);
    director->getActionManager()->addAction(repeatBG, _spriteTiao, false);
    auto lineRotate1= RotateTo::create(rotateTime1,-45.0);
    auto lineRotate2= RotateTo::create(rotateTime2,45.0);
    auto sequenceLineBG=Sequence::create(lineRotate1, lineRotate2, NULL);
    RepeatForever* repeatLineBG=RepeatForever::create(sequenceLineBG);
    repeatLineBG->setTag(1001);
    director->getActionManager()->addAction(repeatLineBG, _dottedSprite, false);
}
void GameScene::resetGame(EventCustom* e)
{
  
    char getPropSql[100];
    sprintf(getPropSql, "select * from Prop ");
    Value propAvm=DataUtil::getRow(getPropSql);
    int cieclePropNumber=propAvm.asValueMap()["circleProp"].asInt();
    _loopNumber=cieclePropNumber;
    _isTouch=true;
    _isTaoZhong=false;
    SimpleAudioEngine::getInstance()->rewindBackgroundMusic();//重新开始播放背景音乐
    sprintf(_loopNumberLabel, ":%d",_loopNumber);
    labelNumber->setString(_loopNumberLabel);
    Director::getInstance()->resume();
    
    int num=random(1, 6);
    ValueVector shapeVV=LevelData::paeseLevelShape(num).asValueVector();

    //从json中取出小图
    ValueVector avm=LevelData::paeseLevelSmallPicture(cLevel).asValueVector();
    hiddenPictureVector.clear();//清空Vector
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
        std::stringstream name; string color="";int randNumber;
        
        if (cLevel>9) {
            if (i<4) {
                int randName=random(0, 2);
                int mPicID =avm.at(i+randName*4).asValueMap()["id"].asInt();
                std::string mPicName =avm.at(i).asValueMap()["pictureName"].asString();
                name<<mPicName<<mPicID<<".png";
                Texture2D* texture = TextureCache::sharedTextureCache()->addImage(name.str());
                rp->ID=randNumber;
                rp->setTexture(texture);
            }else{
                randNumber=random(1, 6);//随机图片
                name<<"gamescene/t"<<randNumber<<".png";
                Texture2D* texture = TextureCache::sharedTextureCache()->addImage(name.str());
                rp->ID=randNumber;
                rp->setTexture(texture);
            }
        }else{
            if (i<avm.size()) {
                int mPicID =avm.at(i).asValueMap()["id"].asInt();
                randNumber=mPicID;
                string picName;
                picName=avm.at(i).asValueMap()["pictureName"].asString();
                Texture2D* texture = TextureCache::sharedTextureCache()->addImage(picName);
                rp->ID=randNumber;
                rp->setTexture(texture);
            }else{
                randNumber=random(1, 8);//随机图片
                name<<"gamescene/n"<<randNumber<<".png";
                Texture2D* texture = TextureCache::sharedTextureCache()->addImage(name.str());
                rp->ID=randNumber;
                rp->setTexture(texture);
            }
        }
        
        Sprite* dzty=(Sprite*)dizuoTouyingVector.at(i);
        Texture2D* textureDzty;Texture2D* textureBG;
        if (cLevel>9) {
            //背景
            textureBG = TextureCache::sharedTextureCache()->addImage("gamescene/gameBG.png");
            _gameBG->setTexture(textureBG);
            //圈
            Texture2D* textureQuan = TextureCache::sharedTextureCache()->addImage("gamescene/quan3.png");
            _spriteQuan->setTexture(textureQuan);
            //底座投影
            textureDzty = TextureCache::sharedTextureCache()->addImage("gamescene/foundation5.png");
            dzty->setTexture(textureDzty);
            dzty->setPosition(Vec2(origin.x+visibleSize.width*pX*0.01, origin.y + visibleSize.height*pY*0.01-visibleSize.height*smartRes_dzty));
        }else{
            
            //更换背景图片
            char bgName[40];
            sprintf(bgName, "gamescene/gameBG%d.png",num);
            textureBG = TextureCache::sharedTextureCache()->addImage(bgName);
            _gameBG->setTexture(textureBG);
            //底座投影
            textureDzty = TextureCache::sharedTextureCache()->addImage("gamescene/foundation.png");
            dzty->setTexture(textureDzty);
            dzty->setPosition(Vec2(origin.x+visibleSize.width*pX*0.01, origin.y + visibleSize.height*pY*0.01-visibleSize.height*smartRes_dzty));
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
    Texture2D* texture = TextureCache::sharedTextureCache()->addImage(bigPicName);
    _wholePicture->setTexture(texture);
    
    //判断本关模式
    char getUserSql[100];
    sprintf(getUserSql, "select * from User where level=%d",cLevel);
    
    //从数据库中取出用户信息
    cocos2d::Value cv=DataUtil::getRow(getUserSql);
    int pattern=cv.asValueMap()["pattern"].asInt();
    int yinXingNum=cv.asValueMap()["starNum"].asInt();
    float rotateTime1;float rotateTime2;

    if (pattern==1&&yinXingNum!=3) {
        _ruling->setVisible(true);
        _labelAngle->setVisible(true);
        _labelPower->setVisible(true);
        rotateTime1=2.0;rotateTime2=2.0;
    }else if(pattern==2){
        rotateTime1=1.5;rotateTime2=1.5;
        _ruling->setVisible(false);
        _labelAngle->setVisible(false);
        _labelPower->setVisible(false);
        _dottedLineProgress2->setVisible(false);
        
    }else if(pattern==1&&yinXingNum==3){
        rotateTime1=1.5;rotateTime2=1.5;
        DataUtil::updatePatternData(2,cLevel);//更新游戏模式
        UserDefault::getInstance()->setBoolForKey("isGengxin", true);
    }

    Director* director=Director::getInstance();
    director->getActionManager()->removeActionByTag(1000, _spriteTiao);
    director->getActionManager()->removeActionByTag(1001, _dottedSprite);
    
    RotateTo* rotate1= RotateTo::create(rotateTime1,-45.0);
    RotateTo* rotate2 = RotateTo::create(rotateTime2,45.0);
    Sequence* sequenceBG=Sequence::create(rotate1, rotate2, NULL);
    RepeatForever* repeatBG=RepeatForever::create(sequenceBG);
    repeatBG->setTag(1000);
    director->getActionManager()->addAction(repeatBG, _spriteTiao, false);
    auto lineRotate1= RotateTo::create(rotateTime1,-45.0);
    auto lineRotate2= RotateTo::create(rotateTime2,45.0);
    auto sequenceLineBG=Sequence::create(lineRotate1, lineRotate2, NULL);
    RepeatForever* repeatLineBG=RepeatForever::create(sequenceLineBG);
    repeatLineBG->setTag(1001);
    director->getActionManager()->addAction(repeatLineBG, _dottedSprite, false);

}


bool GameScene::onTouchBegan(Touch *touch, Event *event)
{

    Director* director=Director::getInstance();
    director->getActionManager()->pauseTarget(GameScene::_spriteTiao);//暂停指针的动作
    director->getActionManager()->pauseTarget(GameScene::_dottedSprite);//暂停虚线的动作
    //director->getActionManager()->removeActionByTag(2000, _dottedLineProgress);
    _powerProgress->setVisible(true);
    _dottedSprite->setVisible(false);
    if (_isHelp) {
        _dottedLineProgress->setVisible(true);
        _isHelp=false;
    }
    
    //指针进度条的动作
    auto rotate3= RotateTo::create(0.01f,_spriteTiao->getRotation());
    _powerProgress->runAction(rotate3);
    
    auto rotate4= RotateTo::create(0.01f,_spriteTiao->getRotation());
    _dottedLineProgress->runAction(rotate4);
    ProgressFromTo* ptUp=ProgressFromTo::create(1, 0.0f, 100.0f);
    ProgressFromTo* ptDown=ProgressFromTo::create(1, 100.0f, 0.0f);
    auto sequencePG=Sequence::create(ptUp, ptDown, NULL);
    auto repeatPG=RepeatForever::create(sequencePG);
    _powerProgress->runAction(repeatPG);
    //虚线进度条的动作
    //_dottedLineProgress->setPercentage(0.0f);
    ProgressFromTo* LineptUp=ProgressFromTo::create(1, 0.0f, 100.0f);
    ProgressFromTo* LineptDown=ProgressFromTo::create(1, 100.0f, 0.0f);
    auto sequenceLine=Sequence::create(LineptUp, LineptDown, NULL);
    auto repeatLine=RepeatForever::create(sequenceLine);
    _dottedLineProgress->runAction(repeatLine);
   
    
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
    director->getActionManager()->resumeTarget(GameScene::_dottedSprite);//暂停虚线的动作
    //director->getActionManager()->addAction(_repeatLineBG, _dottedLineProgress, false);
    
    //RepeatForever* repeatLineBG=(RepeatForever*)_powerProgress->getActionByTag(1000);
    _powerProgress->setVisible(false);//显示指针的进度条
    //_dottedSprite->setVisible(true);
    _dottedLineProgress->setVisible(false);
    
    //力度和角度
    _powerNumber=_powerProgress->getPercentage();
    _angleNumber=_spriteTiao->getRotation();
    
    char powerChar[10];
    sprintf(powerChar, "%d",_powerNumber);
    _labelPower->setString(powerChar);
    
    char angleChar[10];
    sprintf(angleChar, "%d",_angleNumber);
    _labelAngle->setString(angleChar);
    
    
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
        _dottedLineProgress2->setRotation(_angleNumber);
        _dottedLineProgress2->setPercentage(_powerNumber);

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
        
        
        auto menuItemBlink=Spawn::create(JumpBy::create(0.6f, Vec2(0,50), 50, 1),FadeTo::create(0.6f, 0), NULL);
        
        
        ResolvePicture* taozhong=NULL;
        ResolvePicture* taozhong_heshi=NULL;
        for (int i=0; i<spriteVector.size(); i++)
        {
            //判断是否套住
            ResolvePicture* showRp=spriteVector.at(i);
            if (sqrt((x-showRp->getPositionX())*(x-showRp->getPositionX())+(y-showRp->getPositionY())*(y-showRp->getPositionY()))<=53.0)
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
                    }
                }
            }
        }
        
        
        auto spriteQuan_return  = TargetedAction::create(_spriteQuan,Place::create(Vec2(visibleSize.width/2, visibleSize.height*0.1)));
        auto targetAct = TargetedAction::create(taozhong,menuItemBlink);
        
        
        
        if(taozhong != NULL && taozhong_heshi!=NULL)
        {
            MoveTo* quanMove=MoveTo::create(s/(visibleSize.width*1.3), Vec2(taozhong->getPositionX(),taozhong->getPositionY()));
            auto quanRate = Spawn::create(quanMove,   Sequence::create(ScaleTo::create((s/(visibleSize.width*1.3)*1),QUAN_SCA,QUAN_SCA*0.5), NULL),  NULL);
//            auto quanRate = Spawn::create(quanMove,RotateBy::create(s/(visibleSize.width*1.3), _spriteTiao->getRotation()/2),  ScaleTo::create(s/(visibleSize.width*1.3),QUAN_SCA,QUAN_SCA*0.5),MoveBy::create(0.2, Vec2(0,20)), NULL);
            auto ease=EaseSineOut::create(quanRate);
            
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
            
            _spriteQuan->runAction(Sequence::create(ease,CallFunc::create([=]{_spriteQuan->setZOrder(1);}),MoveBy::create(0.3, Vec2(0,-30)),FadeTo::create(0.2, 0),targetAct,spriteQuan_return,
                CallFunc::create([=]{_spriteQuan->setZOrder(3);}),
                CallFunc::create([=](){
                _spriteQuan->setOpacity(255);
                _spriteQuan->setScale(QUAN_SCA);
                _spriteQuan->setRotation(0);
                taozhong->setPosition(taozhong->getPositionX(),taozhong->getPositionY()-50);
    
                p5->setVisible(true);
                p4->setVisible(true);
                
                p4->runAction(MoveTo::create(0.5, taozhong_heshi->getPosition()));
                p5->runAction(MoveTo::create(0.5, taozhong_heshi->getPosition()));
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
                }}),NULL));
        }else if (taozhong != NULL)
        {
            MoveTo* quanMove=MoveTo::create(s/(visibleSize.width*1.3), Vec2(taozhong->getPositionX(),taozhong->getPositionY()));
            auto quanRate = Spawn::create(quanMove,Sequence::create(ScaleTo::create((s/(visibleSize.width*1.3)*1),QUAN_SCA*0.8,QUAN_SCA*0.56), NULL), NULL);
            auto ease=EaseSineOut::create(quanRate);
            
            auto targetAct = TargetedAction::create(taozhong,Sequence::create(MoveBy::create(0.05, Vec2(-15,0)),MoveBy::create(0.1, Vec2(30,0)), MoveBy::create(0.05, Vec2(-15,0)),NULL));
            _spriteQuan->runAction(Sequence::create(ease,CallFunc::create([=]{_spriteQuan->setZOrder(1);}),
                                                    MoveBy::create(0.3, Vec2(0,-30)),
                                                    FadeTo::create(0.2, 0),spriteQuan_return,
                                                    CallFunc::create([=]{_spriteQuan->setZOrder(3);}),
                                                    Repeat::create(targetAct,1),
                                                    CallFunc::create([=](){_spriteQuan->setOpacity(255);_spriteQuan->setScale(QUAN_SCA);_spriteQuan->setRotation(0);
                taozhong->setPosition(taozhong->getPositionX(),taozhong->getPositionY());
                _spriteQuan->setPosition(Vec2(visibleSize.width/2, visibleSize.height*0.1));
                if(--_loopNumber>0){
                    _isTouch=true;
                }
            }),NULL));
        }else
        {
            MoveTo* quanMove=MoveTo::create(s/(visibleSize.width*1.3), Vec2(x, y));
            auto quanRate = Spawn::create(quanMove,Sequence::create(ScaleTo::create((s/(visibleSize.width*1.3)*1),QUAN_SCA*0.8,QUAN_SCA*0.56), NULL),NULL);
            auto ease=EaseSineOut::create(quanRate);
            
            _spriteQuan->runAction(Sequence::create(ease,FadeTo::create(0.2, 0),spriteQuan_return,
                                                    CallFunc::create([=](){
                _spriteQuan->setOpacity(255);
                _spriteQuan->setRotation(0);
                _spriteQuan->setScale(QUAN_SCA);
                if(--_loopNumber>0){
                    _isTouch=true;
                    
                }}),NULL));
            log("啥都没有中。回来吧");
            log("在循环里面圈子的数目是%d",_loopNumber);
        }
        log("-----End-------x= %f y=%f ",x,y);
        
    }
    if (_loopNumber>0) {

//        addChild(labelTime_D,2);
        sprintf(_loopNumberLabel, ":%d",_loopNumber-1);
//        labelNumber->setString(_loopNumberLabel);
        labelNumber->runAction(Sequence::create(ScaleTo::create(0.5, 1.5*visibleSize.width/640.0),
                                                ScaleTo::create(0.25, 1.25*visibleSize.width/640.0),CallFunc::create([=](){labelNumber->setString(_loopNumberLabel);}), ScaleTo::create(0.25, 1.25*visibleSize.width/640.0),  ScaleTo::create(1, 1*visibleSize.width/640.0),        NULL));

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

ValueVector GameScene::calculationSatrNumber(int quanNumber,int picNumber)
{
    ValueVector starVV;int num3=0;int num2=0;
    switch (picNumber) {
        case 1:
            num3=0.3;
            num2=0.6;
            break;
        case 2:
            num3=1;
            num2=1.5;
            break;
        case 3:
            num3=1;
            num2=2;
            break;
        case 4:
            num3=2;
            num2=3;
            break;
        default:
            break;
    }
    int starNmber3=quanNumber/picNumber*num3;
    int starNmber2=quanNumber/picNumber*num2;
    starVV.push_back(Value(starNmber3));//3星
    starVV.push_back(Value(starNmber2));//2星
    return starVV;
}

void GameScene::enterIntoSucceedUI()
{
    //套完所有图片执行

    if ((hiddenPictureVector.size()==0&&getChildByName("succeedLayer")==NULL)||(hiddenPictureVector.size()==8&&getChildByName("succeedLayer")==NULL)) {
        int picNumber=(int)showPictureVector.size();
        for (int i=0; i<showPictureVector.size(); i++) {
            ResolvePicture* rp=(ResolvePicture*)showPictureVector.at(i);
            this->removeChild(rp);
        }
        char getUserSql[100];
        sprintf(getUserSql, "select * from User where level=%d",cLevel);
        
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
        if (_loopNumber<=starNumber3) {
            starNum=1;
        }
        else if (_loopNumber>starNumber3&&_loopNumber<=starNumber2){
            starNum=2;
        }else{
            starNum=3;
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
        _spriteQuan->setPosition(Vec2(visibleSize.width/2, visibleSize.height*0.1+ origin.y));//圈回到原位
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
        if (getChildByName("failedLayer")==NULL) {
            //_isFailed=true;
            //移除本关套住的图片
            for (int i=0; i<showPictureVector.size(); i++) {
                ResolvePicture* rp=(ResolvePicture*)showPictureVector.at(i);
                this->removeChild(rp);
            }
            SimpleAudioEngine::getInstance()->stopBackgroundMusic();//停止背景音乐
            Director::getInstance()->pause();//暂停游戏
            _spriteQuan->setPosition(Vec2(visibleSize.width/2, visibleSize.height*0.1+ origin.y));//圈回到原位
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
    if (!_dottedSprite->isVisible()) {
        if (_helpNumber>0) {
            _helpNumber--;
            _isHelp=true;
            _dottedSprite->setVisible(true);
            DataUtil::updatePropData("fileProp", _helpNumber);
            char _helpNumberLabel[10];
            sprintf(_helpNumberLabel, ":%d",_helpNumber);
            _labelHelpNumber->setString(_helpNumberLabel);
        }else{
            log("帮助道具数量不足");
            Director::getInstance()->pause();
            Scene* shopScene=ShoppingMall::createScene();
            Director::getInstance()->pushScene(shopScene);
        }

    }
    
    
}

void GameScene::backSelectLevel(EventCustom* e)
{
//    char getUserSql[100];
//    sprintf(getUserSql, "select * from User where level=%d",cLevel);
//    
//    //从数据库中取出用户信息
//    cocos2d::Value cv=DataUtil::getRow(getUserSql);
//    int oldStarNum=cv.asValueMap()["starNum"].asInt();//从数据库取出星星的个数
//    int pattern=cv.asValueMap()["pattern"].asInt();
//    if(oldStarNum==3&&pattern==2){
//         DataUtil::updatePatternData(1, cLevel);//更新模式
//    }else if (oldStarNum<3&&pattern==2)
//    {}
    
    bool isGengxin=UserDefault::getInstance()->getBoolForKey("isGengxin");
    if(isGengxin)
    {
        DataUtil::updatePatternData(1,cLevel);
        UserDefault::getInstance()->setBoolForKey("isGengxin",false);
    }

    Scene* selectScene=SelectLevel::createScene();
    Director::getInstance()->replaceScene(selectScene);
   
}


GameScene::~GameScene()
{
    _eventDispatcher->removeCustomEventListeners("succeefulUI");
    _eventDispatcher->removeCustomEventListeners("failedUI");
    _eventDispatcher->removeCustomEventListeners("backSelectLevel");
    _eventDispatcher->removeCustomEventListeners("ThisLevelGold");
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

