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
static int cLevel=1;static char Nmuber[10];
// on "init" you need to initialize your instance
bool GameScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    //setKeyboardEnabled(true);//开启键盘触摸
    //setSwallowsTouches(false);
    //或者是这样
    //注册捕捉监听
    // listenerkeyPad = EventListenerKeyboard::create();
    //listenerkeyPad->onKeyReleased = CC_CALLBACK_2(HelloWorld::onKeyReleased, this);
    //_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerkeyPad, this);
    
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();
    
    _isTouch=true;
    _isLoopOrigin=true;
    _IsNeedExit=false;
    _timeNumber=60;
    
    
    for (int i=0; i<42; i++) {
        int randX=random(1, 10);
        int randY=random(4, 9);
        Sprite* waterLight=Sprite::create("gamescene/waterLight.png");
        waterLight->setPosition(Vec2(visibleSize.width*0.1*randX, visibleSize.height*0.1*randY));
        this->addChild(waterLight,1);
        waterVector.pushBack(waterLight);
    }
    
    
    //添加暂停按钮
    pauseItem = MenuItemImage::create("gamescene/pauseButton.png","gamescene/pauseButton.png",
                                           CC_CALLBACK_1(GameScene::menuPauseCallback, this));
    pauseItem->setScale(visibleSize.width/640);
    pauseItem->setPosition(Vec2(visibleSize.width*0.9,origin.y + visibleSize.height*0.94));
    
    //重新开始按钮
    auto restartItem = MenuItemImage::create("gamescene/restartButton.png","gamescene/restartButton.png",
                                             CC_CALLBACK_1(GameScene::menuResartCallback, this));
    restartItem->setScale(visibleSize.width/640);
    
    restartItem->setPosition(Vec2(origin.x +visibleSize.width*0.8,origin.y + visibleSize.height*0.94));

    //返回按钮
    auto backItem = MenuItemImage::create("gamescene/backButton.png","gamescene/backButton.png",
                                           CC_CALLBACK_1(GameScene::menuBackCallback, this));
    
    backItem->setPosition(Vec2(origin.x + visibleSize.width*0.1 ,
                                origin.y + visibleSize.height*0.94));
    backItem->setScale(visibleSize.width/640);
    //帮助按钮
    auto helpItem = MenuItemImage::create("gamescene/helpButton.png","gamescene/helpButton.png",
                                          CC_CALLBACK_1(GameScene::menuHelpCallback, this));
    
    helpItem->setPosition(Vec2(origin.x +visibleSize.width*0.22,origin.y + visibleSize.height*0.94));
    helpItem->setScale(visibleSize.width/640);

    
    
    // create menu, it's an autorelease object
    auto menu = Menu::create(backItem,pauseItem,helpItem,restartItem, NULL);
    menu->setPosition(Vec2::ZERO);
    
    this->addChild(menu, 1);

    
    //添加圈
//    spriteQuan=QuanSprite::createSprite();
//    spriteQuan->initQuanSprite(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/6 + origin.y));
//    spriteQuan->setScale(0.7*visibleSize.width/640);
//    this->addChild(spriteQuan,3);
    
    _spriteQuan=Sprite::create("gamescene/quan.png");
    _spriteQuan->setScale(0.7*visibleSize.width/640);
    _spriteQuan->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/6 + origin.y));
    this->addChild(_spriteQuan,3);

    
    //上
    Sprite* up=Sprite::create("gamescene/Up.png");
    up->setScale(0.7*visibleSize.width/640);
    up->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/6 + origin.y));
    this->addChild(up,2);
    //下
    Sprite* down=Sprite::create("gamescene/Down.png");
    down->setScale(0.7*visibleSize.width/640);
    down->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/6 + origin.y));
    this->addChild(down,1);
    
    //从json文件中随机取出一种图片摆放形状
    int randNum=random(1, 6);
    ValueVector shapeVV=LevelData::paeseLevelShape(randNum).asValueVector();
    
    int comeInLevel=UserDefault::getInstance()->getIntegerForKey("comeInLevel");//从选关界面跳转
    cLevel=comeInLevel;
    ValueVector picVV=LevelData::paeseLevelSmallPicture(comeInLevel).asValueVector();//从json文件中取出每关必须有小图片
    for (int i=0; i<9; i++) {
        char s[10];
        sprintf(s, "s%d", i+1);
        int ss =shapeVV.at(0).asValueMap()[s].asInt();
        int pX=ss/100;
        int pY=ss%100;
        //添加图片
        ResolvePicture* rp=ResolvePicture::createResolvePicture();
        rp->setScale(0.7*visibleSize.width/640);
        
        char name[40];
        int randNumber;
        if (i<picVV.size()) {
            int mPicID =picVV.at(i).asValueMap()["id"].asInt();
            std::string mPicName =picVV.at(i).asValueMap()["pictureName"].asString();
            sprintf(name, "%s",mPicName.c_str());
            randNumber=mPicID;
        }else{
            randNumber=random(1, 6);
            sprintf(name, "gamescene/%d.png",randNumber);
        }
        rp->initResolvePicture(name, randNumber);
        rp->setPicturePosition(origin.x+visibleSize.width*pX*0.01, origin.y + visibleSize.height*pY*0.01);
        this->addChild(rp, 2);
        spriteVector.pushBack(rp);
        //底座
        Sprite* dizuoTouying=Sprite::create("gamescene/foundationProjection.png");
        dizuoTouying->setScale(0.7*visibleSize.width/640);
        //dizuoTouying->setAnchorPoint(Vec2(0.5,1));
        dizuoTouying->setPosition(Vec2(origin.x+visibleSize.width*pX*0.01, origin.y + visibleSize.height*pY*0.01-dizuoTouying->getContentSize().height*2/3));
        this->addChild(dizuoTouying,1);
        dizuoTouyingVector.pushBack(dizuoTouying);
        Sprite* dizuo=Sprite::create("gamescene/foundation.png");
        dizuo->setScale(0.7*visibleSize.width/640);
        dizuo->setPosition(Vec2(origin.x+visibleSize.width*pX*0.01, origin.y + visibleSize.height*pY*0.01));
        this->addChild(dizuo, 1);
        dizuoVector.pushBack(dizuo);
    }

    
    //背景
    auto sprite = Sprite::create("gamescene/gameBG.png");
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    sprite->setScale(visibleSize.width/sprite->getContentSize().width);
    this->addChild(sprite, 0);
    //倒计时
    labelTime=LabelAtlas::create("60:", "gamescene/shuzi.png", 37.0f, 59.0f, '0');//加:是为了显示字母，0是开始字符
    labelTime->setScale(visibleSize.width/640.0);
    labelTime->setPosition(Vec2(origin.x + visibleSize.width/2,origin.y + visibleSize.height*0.97 - labelTime->getContentSize().height));
    
    this->addChild(labelTime, 1);
    
    this->schedule(schedule_selector(GameScene::updateTime), 1.0);
    this->scheduleUpdate();
    //指针
    _spriteTiao=Sprite::create("gamescene/zhizhenBG.png");
    _spriteTiao->setScale(0.7*visibleSize.width/640);
    _spriteTiao->setRotation(45);
    _spriteTiao->setTag(1);
    _spriteTiao->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/5.4 + origin.y));
    _spriteTiao->setAnchorPoint(Vec2(0.5,0));
    // add the sprite as a child to this layer
    this->addChild(_spriteTiao, 0);
    
    //旋转
    auto rotate1= RotateTo::create(1.5f,-45.0);
    auto rotate2= RotateTo::create(1.5f,45.0);
    auto sequenceBG=Sequence::create(rotate1, rotate2, NULL);
    auto repeatBG=RepeatForever::create(sequenceBG);
    
    _spriteTiao->runAction(repeatBG);
    
    //添加进度条
    _powerProgress=ProgressTimer::create(Sprite::create("gamescene/powerBar.png"));
    _powerProgress->setScale(0.7*visibleSize.width/640);
    _powerProgress->setTag(2);
    _powerProgress->setRotation(45);
    
    _powerProgress->setAnchorPoint(Vec2(0.5,0));
    _powerProgress->setBarChangeRate(Point(0,1));
    _powerProgress->setType(ProgressTimer::Type::BAR);
    _powerProgress->setMidpoint(Point(0,0));
    _powerProgress->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/5.4 + origin.y));
    _powerProgress->setPercentage(0.0f);
    this->addChild(_powerProgress,0);
    _powerProgress->setVisible(false);
    
    
    //添加圈数
    _loopNumber=10;

    labelNumber = LabelAtlas::create(":10", "gamescene/shuzi2.png", 26.0f, 41.0f, '0');
    labelNumber->setScale(visibleSize.width/640.0);
    labelNumber->setPosition(Vec2(origin.x + visibleSize.width*0.8,origin.y + visibleSize.height/6));
    this->addChild(labelNumber, 1);
    //添加不动圈
    auto noMoveSprite = Sprite::create("gamescene/huan.png");
    noMoveSprite->setScale(visibleSize.width/640.0);
    noMoveSprite->setPosition(Vec2(origin.x + visibleSize.width*0.8, origin.y + visibleSize.height/8 - labelNumber->getContentSize().height));
    this->addChild(noMoveSprite, 1);
    
    //json文件解析获取隐藏小图
    
    ValueVector hiddenPic=LevelData::paeseXml(comeInLevel).asValueVector();
    
    for (int i=0; i<hiddenPic.size(); i++) {
    
        int _inttag =hiddenPic.at(i).asValueMap()["inttag"].asInt();
        int picId=_inttag/100;
        std::string name =hiddenPic.at(i).asValueMap()["picName"].asString();
        int px =hiddenPic.at(i).asValueMap()["positionX"].asInt();
        int py =hiddenPic.at(i).asValueMap()["positionY"].asInt();
        int rotation=hiddenPic.at(i).asValueMap()["rotation"].asInt();
        if (_inttag>99) {
            ResolvePicture* rp=ResolvePicture::createResolvePicture();
            rp->setScale(_spriteQuan->getContentSize().width*2/visibleSize.width);
            rp->initResolvePicture(name, picId);
            rp->setPicturePosition(visibleSize.width*px*0.01, visibleSize.height*py*0.01);
            rp->setRotation(rotation);
            //rp->setVisible(false);
            //this->addChild(rp,3);
            hiddenPictureVector.pushBack(rp);
        }else{
        //添加大图
            _wholePicture = Sprite::create(name);
            _wholePicture->setScale(_spriteQuan->getContentSize().width/_wholePicture->getContentSize().width);
            _wholePicture->setPosition(Vec2(origin.x + visibleSize.width/5, origin.y + visibleSize.height/6));
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

    auto mCustomListener = EventListenerCustom::create("succeefulUI", CC_CALLBACK_1(GameScene::setPicturePosition, this));
    _eventDispatcher->addEventListenerWithFixedPriority(mCustomListener, 1);
    //失败界面自定义监听回调
    auto failedUICustomListener = EventListenerCustom::create("failedUI", CC_CALLBACK_1(GameScene::resetGame, this));
    _eventDispatcher->addEventListenerWithFixedPriority(failedUICustomListener, 1);

    //注册捕捉监听
    auto listenerkeyPad = EventListenerKeyboard::create();
    listenerkeyPad->onKeyReleased = CC_CALLBACK_2(GameScene::onKeyReleased, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listenerkeyPad, this);

    
    //_eventDispatcher->removeAllEventListeners();
    return true;
}
//设置图片的摆放位置
void GameScene::setPicturePosition(EventCustom* e)
{
    Director::getInstance()->resume();
    _timeNumber=60;
   
    
    char*buf =static_cast<char*>(e->getUserData());
     _loopNumber=std::atoi(buf);
    //sprintf(_loopNumberLabel, ":%d",_loopNumber);
    labelNumber->setString(buf);
   
    int num=random(1, 6);
    ValueVector shapeVV=LevelData::paeseLevelShape(num).asValueVector();
    cLevel++;
    //string sqlssssss = "select * from picture where level=1";
    //取出数据库所有
    //ValueVector avm=DataUtil::getAll(sqlssssss).asValueVector();
    //ValueVector avm=DataUtil::getSmallPicture("picture", cLevel);
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
        rp->setScale(0.7*visibleSize.width/640);
        rp->setPicturePosition(origin.x+visibleSize.width*pX*0.01, origin.y + visibleSize.height*pY*0.01);
        int randNumber;
        if (i<avm.size()) {
            int mPicID =avm.at(i).asValueMap()["id"].asInt();
            randNumber=mPicID;
        }else{
            randNumber=random(1, 6);
        }
        char name[40];
        sprintf(name, "gamescene/%d.png",randNumber);
        Texture2D* texture = TextureCache::sharedTextureCache()->addImage(name);
        rp->ID=randNumber;
        rp->setTexture(texture);
        
        Sprite* dzty=(Sprite*)dizuoTouyingVector.at(i);
        dzty->setPosition(Vec2(rp->getPositionX(),rp->getPositionY()-dzty->getContentSize().height*2/3));
        Sprite* dz=(Sprite*)dizuoVector.at(i);
        dz->setPosition(rp->getPosition());
    }
    
    //std::string bigPicName=DataUtil::getBigPicture("bigPicture", cLevel);//从数据库中取大图名字
    std::string bigPicName;
    
    //添加隐藏小图（从json文件中获取）
    ValueVector picVV=LevelData::paeseXml(cLevel).asValueVector();
    hiddenPictureVector.clear();//清空Vector
    for (int i=0; i<picVV.size(); i++) {
        int _inttag =picVV.at(i).asValueMap()["inttag"].asInt();
        int picId=_inttag/100;
        std::string name =picVV.at(i).asValueMap()["picName"].asString();
        int px =picVV.at(i).asValueMap()["positionX"].asInt();
        int py =picVV.at(i).asValueMap()["positionY"].asInt();
        int rotation=picVV.at(i).asValueMap()["rotation"].asInt();
        //大图从json文件中获得
        if (_inttag<99) {
            bigPicName=name;
        }else{
            //int size=(int)hiddenPictureVector.size();
           // if (i==size) {
            
                ResolvePicture* rp=ResolvePicture::createResolvePicture();
                rp->setScale(_spriteQuan->getContentSize().width*2/visibleSize.width);
                rp->initResolvePicture(name, picId);
                rp->setPicturePosition(visibleSize.width*px*0.01, visibleSize.height*py*0.01);
                rp->setRotation(rotation);
                //this->addChild(rp,3);
                //rp->setVisible(false);
                hiddenPictureVector.pushBack(rp);
            //}else{
            //    ResolvePicture* rp=hiddenPictureVector.at(i);
             //   Texture2D* texture = TextureCache::sharedTextureCache()->addImage(name);
             //   rp->setTexture(texture);
              //  rp->ID=picId;
             //   rp->setPicturePosition(visibleSize.width*px*0.01, visibleSize.height*py*0.01);
                //rp->setVisible(false);
           // }
        }
//        ResolvePicture* rp=hiddenPictureVector.at(i);
//            Texture2D* texture = TextureCache::sharedTextureCache()->addImage(name);
//            rp->setTexture(texture);
//            rp->ID=picId;
//            rp->setPicturePosition(visibleSize.width*px*0.01, visibleSize.height*py*0.01);
        
//        ResolvePicture* rp=ResolvePicture::createResolvePicture();
//        rp->setScale(spriteQuan->getContentSize().width*1.5/visibleSize.width);
//        rp->initResolvePicture(name, picId);
//        rp->setPicturePosition(visibleSize.width*px*0.01, visibleSize.height*py*0.01);
//        this->addChild(rp,1);
//        hiddenPictureVector.pushBack(rp);
            //rp->setVisible(true);
    
    }
    //添加大图
    Texture2D* texture = TextureCache::sharedTextureCache()->addImage(bigPicName);
    _wholePicture->setTexture(texture);
    _wholePicture->setScale(_spriteQuan->getContentSize().width/_wholePicture->getContentSize().width);
}
void GameScene::resetGame(EventCustom* e)
{
    _timeNumber=60;
    _loopNumber=10;
    sprintf(_loopNumberLabel, ":%d",_loopNumber);
    labelNumber->setString(_loopNumberLabel);
    Director::getInstance()->resume();
    
    int num=random(1, 6);
    ValueVector shapeVV=LevelData::paeseLevelShape(num).asValueVector();
    
    
    //string sqlssssss = "select * from picture where level=1";
    //取出数据库所有
    //ValueVector avm=DataUtil::getAll(sqlssssss).asValueVector();
    //从json中取出小图
    ValueVector avm=LevelData::paeseLevelSmallPicture(cLevel).asValueVector();
    hiddenPictureVector.clear();//清空Vector
    for (int i=0; i<spriteVector.size(); i++) {
        char s[10];
        sprintf(s, "s%d", i+1);
        int ss =shapeVV.at(0).asValueMap()[s].asInt();
        int pX=ss/100;
        int pY=ss%100;
        //添加图片
        ResolvePicture* rp=(ResolvePicture*)spriteVector.at(i);
        rp->setScale(0.7*visibleSize.width/640);
        rp->setPicturePosition(origin.x+visibleSize.width*pX*0.01, origin.y + visibleSize.height*pY*0.01);
        int randNumber;
        if (i<avm.size()) {
            int mPicID =avm.at(i).asValueMap()["id"].asInt();
            randNumber=mPicID;
        }else{
            randNumber=random(1, 6);
        }
        char name[40];
        sprintf(name, "gamescene/%d.png",randNumber);
        Texture2D* texture = TextureCache::sharedTextureCache()->addImage(name);
        rp->setTexture(texture);
        rp->ID=randNumber;
        Sprite* dzty=(Sprite*)dizuoTouyingVector.at(i);
        dzty->setPosition(Vec2(rp->getPositionX(),rp->getPositionY()-dzty->getContentSize().height*2/3));
        Sprite* dz=(Sprite*)dizuoVector.at(i);
        dz->setPosition(rp->getPosition());
    }
    
    //std::string bigPicName=DataUtil::getBigPicture("bigPicture", cLevel);//从数据库中取大图名字
    std::string bigPicName;
    
    //添加隐藏小图和大图（从json文件中获取）
    ValueVector picVV=LevelData::paeseXml(cLevel).asValueVector();
    
    for (int i=0; i<picVV.size(); i++) {
        int _inttag =picVV.at(i).asValueMap()["inttag"].asInt();
        int picId=_inttag/100;
        std::string name =picVV.at(i).asValueMap()["picName"].asString();
        int px =picVV.at(i).asValueMap()["positionX"].asInt();
        int py =picVV.at(i).asValueMap()["positionY"].asInt();
        int rotation=picVV.at(i).asValueMap()["rotation"].asInt();
        //大图从json文件中获得
        if (_inttag<99) {
            bigPicName=name;
        }else{
            //int size=(int)hiddenPictureVector.size();
            //if (i==size) {
                ResolvePicture* rp=ResolvePicture::createResolvePicture();
                rp->setScale(_spriteQuan->getContentSize().width*2/visibleSize.width);
                rp->initResolvePicture(name, picId);
                rp->setPicturePosition(visibleSize.width*px*0.01, visibleSize.height*py*0.01);
                rp->setRotation(rotation);
                 //rp->setVisible(false);
                //this->addChild(rp,3);
                hiddenPictureVector.pushBack(rp);
           // }else{
             //   ResolvePicture* rp=hiddenPictureVector.at(i);
            //    Texture2D* texture = TextureCache::sharedTextureCache()->addImage(name);
            //    rp->setTexture(texture);
           //     rp->ID=picId;
            //    rp->setPicturePosition(visibleSize.width*px*0.01, visibleSize.height*py*0.01);
                //rp->setVisible(false);
                
          //  }
        }
    }
    //添加大图
    Texture2D* texture = TextureCache::sharedTextureCache()->addImage(bigPicName);
    _wholePicture->setTexture(texture);
    _wholePicture->setScale(_spriteQuan->getContentSize().width/_wholePicture->getContentSize().width);
    
}

void GameScene::updateTime(float dt)
{
    if (_timeNumber>0) {
        _timeNumber--;
        
        sprintf(Nmuber, "%d:",_timeNumber);
        log("%s",Nmuber);
        labelTime->setString(Nmuber);
        
    }
    log("关卡数： %d",cLevel);
  
    int num=random(0, 14);
    int numX=random(1, 9);
    int numY=random(3, 9);
    Sprite* waterLight=waterVector.at(num);
    Blink* blink= Blink::create(2, 1);
    Sequence* seq= Sequence::create(CallFunc::create([=](){
            waterLight->setPosition(Vec2(visibleSize.width*0.1*numX, visibleSize.height*0.1*numY));
        }),blink, NULL);
    RepeatForever* rf=RepeatForever::create(seq);
    waterLight->runAction(rf);
    
    //测试
//       if (_timeNumber%5==0) {
//        
//           DataUtil::updateTimeData(60-_timeNumber, cLevel);//更新时间
//           DataUtil::updateSuoData(false, cLevel+1);//下一关解锁
//           int starNum=0;
//           if (_timeNumber>=40) {
//               starNum=3;
//           }
//           else if (_timeNumber>=20&&_timeNumber<40){
//               starNum=2;
//           }else{
//               starNum=1;
//           }
//           DataUtil::updateStarData(starNum, cLevel);//更新星星的数量
//          
//           if (getChildByName("layer")==NULL) {
//               _succeedLayer=ShadeLayer::create();
//               _succeedLayer->init();
//               this->addChild(_succeedLayer,100,"layer");
//               log("cLevel= %d",cLevel);
//           }
//        
//    }
//    if (timeNumber%9==0) {
//         Director::getInstance()->pause();//暂停游戏
//        failLayer=FailedShadeLayer::create();
//        failLayer->init();
//          this->addChild(failLayer,100);
//    }
  
}

bool GameScene::onTouchBegan(Touch *touch, Event *event)
{

    Director* director=Director::getInstance();
    director->getActionManager()->pauseTarget(GameScene::_spriteTiao);
    
    _powerProgress->setVisible(true);
    auto rotate3= RotateTo::create(0.01f,_spriteTiao->getRotation());
    
    _powerProgress->runAction(rotate3);

    ProgressFromTo* ptUp=ProgressFromTo::create(1, 0.0f, 100.0f);
    ProgressFromTo* ptDown=ProgressFromTo::create(1, 100.0f, 0.0f);
    auto sequencePG=Sequence::create(ptUp, ptDown, NULL);
    auto repeatPG=RepeatForever::create(sequencePG);
    _powerProgress->runAction(repeatPG);
    
    return true;
}

void GameScene::onTouchMoved(Touch *touch, Event *event)
{
    log("-----Move-------");
}

void GameScene::onTouchEnded(Touch *touch, Event *event)
{
    Director* director=Director::getInstance();
    director->getActionManager()->resumeTarget(GameScene::_spriteTiao);
    //director->getActionManager()->resumeTarget(HelloWorld::powerProgress);
    _powerProgress->setVisible(false);
    //移除进度条
    //this->removeChildByTag(2);
    
    if (_isTouch) {
         log("isTouch=   %d",_isTouch);
        if (_spriteTiao->getRotation()>0) {
            float rr=sqrt(visibleSize.width/2*visibleSize.width/2+visibleSize.height*3/4*visibleSize.height*3/4);
            
            float r=_powerProgress->getPercentage()*0.01*rr;
            float x1=r*cos((90-_spriteTiao->getRotation())*3.1415926/180);
            float y1=r*sin((90-_spriteTiao->getRotation())*3.1415926/180);
            if (y1<0) {
                y1=-y1;
            }
            y=y1+visibleSize.height/4;
            x=x1+visibleSize.width/2;
            
            float s=sqrtf((x*x+y*y)-(_spriteQuan->getPositionX()*getPositionX()+getPositionY()*getPositionY()));
            
            MoveTo* quanMove=MoveTo::create(s/400.0f, Vec2(x, y));
            auto ease=EaseSineOut::create(quanMove);
            _spriteQuan->runAction(ease);
            //spriteQuan->quanRunMoveToPoint(s/200.0f, Vec2(x, y));
            _loopNumber--;
            sprintf(_loopNumberLabel, ":%d",_loopNumber);
            labelNumber->setString(_loopNumberLabel);
            _isTouch=false;
           
            
            log("-----End-------x= %f y=%f ",x,y);
        }else{
            float rr=sqrt(visibleSize.width/2*visibleSize.width/2+visibleSize.height*3/4*visibleSize.height*3/4);
            float r=_powerProgress->getPercentage()*0.01*rr;
            float x1=r*cos((90+_spriteTiao->getRotation())*3.1415926/180);
            float y1=r*sin((90+_spriteTiao->getRotation())*3.1415926/180);
            if (y1<0) {
                y1=-y1;
            }
            y=y1+visibleSize.height/4;
            x=visibleSize.width/2-x1;
            float s=sqrtf((x*x+y*y)-(_spriteQuan->getPositionX()*getPositionX()+getPositionY()*getPositionY()));
           //spriteQuan->quanRunMoveToPoint(s/200.0f, Vec2(x, y));
                MoveTo* quanMove=MoveTo::create(s/800.0f, Vec2(x, y));
                auto ease=EaseSineOut::create(quanMove);
                _spriteQuan->runAction(ease);
                _loopNumber--;
                sprintf(_loopNumberLabel, ":%d",_loopNumber);
                labelNumber->setString(_loopNumberLabel);
              _isTouch=false;
            
            
            log("-----End-------x= %f y=%f ",x,y);
        }
        _isTouch=false;
        
    }
    
    
    
}

void GameScene::onTouchCancelled(Touch *touch, Event *event)
{}


void GameScene::update(float dt)
{
    
    //判断圈是否到达目的地
    if (_spriteQuan->getPositionX()==x&&_spriteQuan->getPositionY()==y) {
        
        for (int i=0; i<spriteVector.size(); i++) {
            
            //判断是否套住
            ResolvePicture* showRp=spriteVector.at(i);
            if (sqrt((x-showRp->getPositionX())*(x-showRp->getPositionX())+(y-showRp->getPositionY())*(y-showRp->getPositionY()))<=50.0) {

                showRp->isCover=true;
                Blink* menuItemBlink=Blink::create(1.0f, 2);
                showRp->runAction( Sequence::create(menuItemBlink,DelayTime::create(1.0f),CallFunc::create([=](){
                    if (_spriteQuan->getPosition()==Vec2(visibleSize.width/2, visibleSize.height/6)) {
                        _isLoopOrigin=true;
                    }else{
                        _isLoopOrigin=false;
                    }
                    this->enterIntoSucceedUI();//判断是否进入成功界面
                }),NULL));
                
                
                if (showRp->isCover) {
                
                    for (int j=0; j<hiddenPictureVector.size(); j++) {
                        ResolvePicture* hiddenRp=hiddenPictureVector.at(j);
                        if (hiddenRp->ID==showRp->ID) {
                            //添加帧动画
                           /*Animation* animation=Animation::create();
                            for (int i=0; i<3; i++) {
                                char name[30];
                                sprintf(name, "gamescene/dizuo%d.png",i+1);
                                animation->addSpriteFrameWithFileName(name);
                            }
                            animation->setDelayPerUnit(1.0f / 3.0f); // 这个动画包含14帧，将会持续2.8秒.
                            animation->setRestoreOriginalFrame(true); // 14帧播放完之后返回到第一帧
                            
                            Animate *action = Animate::create(animation);
                            auto dizuo=Sprite::create("gamescene/dizuo1.png");
                            dizuo->setPosition(Vec2(showRp->getPositionX(),showRp->getPositionY()));
                            
                            this->addChild(dizuo,0);
                            dizuo->runAction(action);  // 运行精灵对象*/
                            //dizuo->setVisible(false);
                            //换图片
                            showRp->changPicture();
                            //显示套住的图片
                            //hiddenRp->setVisible(true);
                            log("****%d",hiddenRp->ID);
                            this->addChild(hiddenRp,3);
                            hiddenPictureVector.eraseObject(hiddenRp);
                            showPictureVector.pushBack(hiddenRp);
                            break;
                        }
                        
                    }
                }

            }else{
                log("没套住");
                if(i==8)
                {
                    //spriteQuan->setPosition(Vec2(visibleSize.width/2, visibleSize.height/6));
                    //spriteQuan->runAction(Sequence::create(Blink::create(1.0f, 2),MoveTo::create(0.01f, Vec2(visibleSize.width/2, visibleSize.height/6)), NULL));
                   //spriteQuan->runAction(Blink::create(1.0f, 2));
                     //isTouch=true;
                     enterIntoFailedUI();//判断是否进入失败界面
                }
               
            }

        }
        x=0.0;y=0.0;
        if (_loopNumber>=0) {
            
            _spriteQuan->setPosition(Vec2(visibleSize.width/2, visibleSize.height/6));
            _isTouch=true;
        }else{
            _spriteQuan->setVisible(false);
        }
    }

    
    //log("x= %f,y=%f, istouch=%d",spriteQuan->getPositionX(),spriteQuan->getPositionY(),isTouch);

}

void GameScene::enterIntoSucceedUI()
{
    //套完所有图片执行
    
    if (hiddenPictureVector.size()==0&&getChildByName("layer")==NULL&&_isLoopOrigin) {
        this->runAction(DelayTime::create(2.0f));
        for (int i=0; i<showPictureVector.size(); i++) {
            ResolvePicture* rp=(ResolvePicture*)showPictureVector.at(i);
            this->removeChild(rp);
        }
        
        DataUtil::updateTimeData(60-_timeNumber, cLevel);//更新时间
        DataUtil::updateSuoData(false, cLevel+1);//下一关解锁
        int starNum=0;
        if (_timeNumber>=40) {
            starNum=3;
        }
        else if (_timeNumber>=20&&_timeNumber<40){
            starNum=2;
        }else{
            starNum=1;
        }
        DataUtil::updateStarData(starNum, cLevel);//更新星星的数量
        Director::getInstance()->pause();//暂停游戏
        _spriteQuan->setPosition(Vec2(visibleSize.width/2, visibleSize.height/6));//圈回到原位
        //添加过关层
        _succeedLayer=ShadeLayer::create();
        _succeedLayer->init();
        this->addChild(_succeedLayer,100,"layer");
        log("%%%%%%%%%%%%");
        
    }


}
void GameScene::enterIntoFailedUI()
{
    //判断圈数和时间
    if (_loopNumber==0||_timeNumber==0) {
        
        for (int i=0; i<showPictureVector.size(); i++) {
            ResolvePicture* rp=(ResolvePicture*)showPictureVector.at(i);
            this->removeChild(rp);
        }
        Director::getInstance()->pause();//暂停游戏
        _spriteQuan->setPosition(Vec2(visibleSize.width/2, visibleSize.height/6));//圈回到原位
        //添加失败层
        _failLayer=FailedShadeLayer::create();
        _failLayer->init();
        this->addChild(_failLayer,100);
        
    }


}


void GameScene::menuPauseCallback(Ref* pSender)
{
        Director::getInstance()->pause();
        _pauseLayer=PauseLayer::create();
        _pauseLayer->init();
        this->addChild(_pauseLayer,3);
       /* LayerColor* layerColor = LayerColor::create();
        layerColor->setColor(Color3B(0, 0, 0));
        layerColor->setOpacity(150);
        layerColor->setContentSize(visibleSize);
        this->addChild(layerColor);
        //添加监听
        auto callback=[](Touch*,Event*)
        {
            return true;
        };
        auto listener1=EventListenerTouchOneByOne::create();
        listener1->onTouchBegan=callback;
        listener1->setSwallowTouches(true);
        _eventDispatcher->addEventListenerWithFixedPriority(listener1, -1);*/
}
//重新开始按钮回调方法

void GameScene::menuResartCallback(cocos2d::Ref* pSender)
{}
//帮助按钮回调方法
void GameScene::menuHelpCallback(Ref* pSender)
{}


void GameScene::menuBackCallback(Ref* pSender)
{
    Scene* selectScene=SelectLevel::createScene();
    Director::getInstance()->replaceScene(selectScene);
   
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

