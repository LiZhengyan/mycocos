//
//  SelectLevel.cpp
//  TaoQuan
//
//  Created by yongxinwan on 15/6/16.
//
//

#include "SelectLevel.h"
#include "GameScene.h"
#include "SmartRes.h"
#include"SimpleAudioEngine.h"
#include "ShoppingMall.h"
#include "RemindLayer.h"
#include "Single.h"
#include "IOSiAP_Bridge.h"
#include "Userguide.h"
//USING_NS_CC;
using namespace CocosDenshion;
Scene* SelectLevel::createScene()
{
    auto scene = Scene::create();
    auto layer = SelectLevel::create();
    scene->addChild(layer);
    return scene;
}
//static int timeMin=10;static int timeSec=60;
static LabelAtlas* _minuteNumber;


bool SelectLevel::init()
{
   if ( !Layer::init() )
    {
        return false;
    }


    //数据库测试
     DataUtil::initDB("ok.db");
    //数据库中创建用户表
    bool isUserExist=DataUtil::tableIsExist("User");
    bool isPropExist=DataUtil::tableIsExist("Prop");
    if (isUserExist==false) {
        //pattern：1银星 2金星
        string creatUserTable = "create table User(level integer,isSuo bool,starNum integer,pattern integer)";
        DataUtil::createTable(creatUserTable,"User");
        //像表格中插入数据
        /*string insertUser = "insert into User values(1,'false',0,0),(2,'true',0,0),(3,'true',0,0),(4,'true',0,0),(5,'true',0,0),(6,'true',0,0),(7,'true',0,0),(8,'true',0,0),(9,'true',0,0),(10,'true',0,0),(11,'true',0,0),(12,'true',0,0),(13,'true',0,0),(14,'true',0,0),(15,'true',0,0),(16,'true',0,0),(17,'true',0,0),(18,'true',0,0)";*/
        string insertUser = "insert into User values(1,'false',0,1),(2,'true',0,1),(3,'true',0,1),(4,'true',0,1),(5,'true',0,1),(6,'true',0,1),(7,'true',0,1),(8,'true',0,1),(9,'true',0,1),(10,'true',0,1),(11,'true',0,1),(12,'true',0,1),(13,'true',0,1),(14,'true',0,1),(15,'true',0,1),(16,'true',0,1),(17,'true',0,1),(18,'true',0,1),(19,'true',0,1),(20,'true',0,1),(21,'true',0,1),(22,'true',0,1),(23,'true',0,1),(24,'true',0,1),(25,'true',0,1),(26,'true',0,1),(27,'true',0,1),(28,'true',0,1),(29,'true',0,1),(30,'true',0,1),(31,'true',0,1),(32,'true',0,1),(33,'true',0,1),(34,'true',0,1),(35,'true',0,1),(36,'true',0,1)";
        DataUtil::insertData(insertUser);
    }
    if (isPropExist==false) {
        string creatPropTable = "create table Prop(fileProp integer,helpProp integer,circleProp integer,energy integer,month integer,day integer,hour integer,minute integer)";
        DataUtil::createTable(creatPropTable,"Prop");
        //像表格中插入数据
        string insertProp = "insert into Prop values(10,10,10,6,0,0,0,0)";
        DataUtil::insertData(insertProp);
    }

    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();
    //导演类的定时器
    //Scheduler* m_scheduler=new Scheduler();
    //setScheduler(m_scheduler);
    //Director::getInstance()->getScheduler()->scheduleUpdateForTarget(m_scheduler, 1, false);
    
    //Director::getInstance()->getScheduler()->schedule(schedule_selector(SelectLevel::showEnergy), this, 1.0, false);
    this->schedule(SEL_SCHEDULE(&SelectLevel::showEnergy), 1.0f);
   
    
    
    
    //Director::getInstance()->getScheduler()->scheduleSelector(schedule_selector(SelectLevel::showEnergy), this, 1.0, false);
    //播放背景音乐，true表示循环播放
    //SimpleAudioEngine::getInstance()->preloadBackgroundMusic("gameSceneMusic.mp3");//加载
    bool isSound=UserDefault::getInstance()->getBoolForKey("isSound");
    if(isSound)
    {
        SimpleAudioEngine::getInstance()->playBackgroundMusic("musicAndeffect/selectLevelMusic.mp3",true);//播放
    }
    m_IsNeedExit=false; 
    
    ScrollView * scrollView = ScrollView::create(Size(visibleSize.width,visibleSize.height));
    
    //创建一个CCLayer，将内容添加到CCLayer中，然后将这个layer添加到scrollview中
        Layer * layer =Layer::create();
        for(int k = 0;k<3;k++)
        {
            //String * string = String::createWithFormat("gamescene/%d.png",i+1);
            //Sprite * sprite = Sprite::create(string->getCString());
            //将所有的精灵都放到屏幕的中间显示
            //sprite->setPosition(ccpAdd(Vec2(visibleSize.width/2,visibleSize.height/2),Vec2(visibleSize.width*i,0)));
            //layer->addChild(sprite);
            //背景
            char gameName[30];
            sprintf(gameName, "selectlevel/gameBG%d.jpg",k);
            auto sprite = Sprite::create(gameName);
            //sprite->setPosition(ccpAdd(Vec2(visibleSize.width/2,visibleSize.height/2),Vec2(visibleSize.width*k,0)));
            /*3.0以后ccpAdd(p1,p2),改成p1+p2*/
            sprite->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2)+Vec2(visibleSize.width*k,0));
            sprite->setScale(visibleSize.width/sprite->getContentSize().width);
            layer->addChild(sprite, 0);
            //标题
            char titleName[30];
            sprintf(titleName, "selectlevel/title%d.png",k);
            Sprite* spriteTitle=Sprite::create(titleName);
            spriteTitle->setScale(visibleSize.width/640.0);
            spriteTitle->setPosition(Vec2(visibleSize.width/2+visibleSize.width*k,visibleSize.height*0.82));
            layer->addChild(spriteTitle,3);
            //背景圆
            auto quanBG = Sprite::create("selectlevel/circleBG.png");
            quanBG->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2)+Vec2(visibleSize.width*k,0));
            quanBG->setScale(visibleSize.width*0.9/quanBG->getContentSize().width);
            layer->addChild(quanBG, 2);
            
            for (int i=0; i<3; i++) {
                for (int j=0; j<3; j++) {
                    char getUserSql[100];
                    sprintf(getUserSql, "select * from User where level=%d",k*9+i*3+j+1);
                    
                    //从数据库中取出用户信息
                    cocos2d::Value cv=DataUtil::getRow(getUserSql);
                    bool isSuo;int starNum; int pattern;
                    if (k<2) {
                        isSuo=cv.asValueMap()["isSuo"].asBool();//从数据库取出是否解锁的值
                        starNum=cv.asValueMap()["starNum"].asInt();//从数据库取出星星的个数
                        pattern=cv.asValueMap()["pattern"].asInt();//从数据库取出游戏模式
                    }else{
                        isSuo=true;
                        starNum=0;
                    }
                    MenuItemImage* levelButton;Sprite* suo;Sprite* hengTiao;Sprite* shuTiao;
                    
                    
                    if (isSuo) {
                        levelButton = MenuItemImage::create("selectlevel/levelNumberBG.png","selectlevel/levelNumberBG.png",CC_CALLBACK_1(SelectLevel::menuLevelButtonCallback, this,k*9+i*3+j+1,isSuo));
                        //锁
                        suo=Sprite::create("selectlevel/suo.png");
                        //suo->setPosition(ccpAdd(Vec2(visibleSize.width/4*(j+1),visibleSize.height*0.64-visibleSize.height*0.128*i),Vec2(visibleSize.width*k,0)) );
                        
                        //4和6调换位置
                        if (i==1) {
                            suo->setPosition(Vec2(visibleSize.width*0.75-visibleSize.width/4*j,visibleSize.height*0.64-visibleSize.height*0.128*i)+Vec2(visibleSize.width*k,0));
                        }else{
                            suo->setPosition(Vec2(visibleSize.width*0.25+visibleSize.width/4*j,visibleSize.height*0.64-visibleSize.height*0.128*i)+Vec2(visibleSize.width*k,0));
                        }
                        layer->addChild(suo,4);
                    }else{
                        //星星个数是否为0时，关卡按钮的状态
                        if (starNum==0)
                            levelButton = MenuItemImage::create("selectlevel/weiJiesuo.png","selectlevel/weiJiesuo.png",CC_CALLBACK_1(SelectLevel::menuLevelButtonCallback, this,k*9+i*3+j+1,isSuo));
                        else
                            levelButton = MenuItemImage::create("selectlevel/levelNumberBG.png","selectlevel/levelNumberBG.png",CC_CALLBACK_1(SelectLevel::menuLevelButtonCallback, this,k*9+i*3+j+1,isSuo));
                        
                        //关卡数字
                        LabelAtlas* levelNum;
                        levelNum=LabelAtlas::create("1", "selectlevel/weiJiesuoNum.png", 40.0f, 54.0f, '1');//加:是为了显示字母，0是开始字符
                       
                        char levelNumber[10];
                        sprintf(levelNumber, "%d",i*3+(j+1));
                        levelNum->setString(levelNumber);
                        levelNum->setScale(visibleSize.width/640.0);
                        //4和6调换位置
                        if (i==1) {
                            levelNum->setPosition(Vec2(visibleSize.width*0.72-visibleSize.width/4*j,visibleSize.height*smartRes_shuZiHigh-visibleSize.height*0.13*i)+Vec2(visibleSize.width*k,0));
                        }else{
                            levelNum->setPosition(Vec2(visibleSize.width*0.22+visibleSize.width/4*j,visibleSize.height*smartRes_shuZiHigh-visibleSize.height*0.13*i)+Vec2(visibleSize.width*k,0));
                        }
                        
                        layer->addChild(levelNum, 3);
                 
                    }
                    //4和6按钮调换位置
                    if (i==1) {
                        levelButton->setPosition(Vec2(visibleSize.width/4*3-visibleSize.width/4*j,visibleSize.height*0.64-(visibleSize.height*0.09+visibleSize.height*0.038)*i)+Vec2(visibleSize.width*k,0));
                    }else{
                        levelButton->setPosition(Vec2(visibleSize.width/4*(j+1),visibleSize.height*0.64-(visibleSize.height*0.09+visibleSize.height*0.038)*i)+Vec2(visibleSize.width*k,0));
                    }
                    
                    levelButton->setScale(visibleSize.width*0.9/640);
                    
                    levelButton->setTag(i*3+j+1);
                    auto menu = Menu::create(levelButton, NULL);
                    menu->setPosition(Vec2::ZERO);
                    layer->addChild(menu, 2);
                    //横条和竖条
                    if (j<2) {
                        hengTiao=Sprite::create("selectlevel/hengtiao2.png");
                        hengTiao->setPosition(Vec2(visibleSize.width*0.375+visibleSize.width*0.25*j,visibleSize.height*0.64-(visibleSize.height*0.09+visibleSize.height*0.038)*i)+Vec2(visibleSize.width*k,0));
                        hengTiao->setScale(visibleSize.width*0.12/hengTiao->getContentSize().width);
                        layer->addChild(hengTiao,2);
                        shuTiao=Sprite::create("selectlevel/shutiao2.png");
                        shuTiao->setPosition(Vec2(visibleSize.width/4*3-visibleSize.width/2*j,visibleSize.height*0.576-visibleSize.height*0.13*j)+Vec2(visibleSize.width*k,0));
                        shuTiao->setScale(visibleSize.width*1.1/640,visibleSize.height*smartRes_shuTiaoScale/shuTiao->getContentSize().height);
                        layer->addChild(shuTiao,2);
                        
                    }
                    
                   
                    //星星
                    for (int n=0; n<3; n++) {
                        Sprite* star;
                        if (n<starNum){
                                if (pattern==1)
                                    star=Sprite::create("selectlevel/yinXing.png");
                                else
                                    star=Sprite::create("selectlevel/starLight.png");
                        }else
                            star=Sprite::create("selectlevel/starNoLight.png");
                        if (starNum==0)
                            star->setVisible(false);
                        else
                            star->setVisible(true);
                            star->setPosition(levelButton->getPositionX()+visibleSize.width*0.03*(n-1), levelButton->getPositionY()-visibleSize.height*smartRes_starHigh);
                            star->setScale(visibleSize.width/640.0);
                            layer->addChild(star,3);
                        }
                    
                }
                
            }

            
        }
    
    
        //设置scrollView中的内容，必须先设置内容再设置内容的大小
        scrollView->setContainer(layer);
        //setContentSize()设置内容区的大小
        scrollView->setContentSize(Size(visibleSize.width*5,visibleSize.height));
    
        //我们屏蔽scrollView这个层的触摸，采用其他的实现方法
        scrollView->setTouchEnabled(false);
        //设置里边内容的偏移量
        scrollView->setContentOffset(Point(0,0));
    
    
        this->addChild(scrollView);
    
        m_scrollView = scrollView;
    
        //当前显示的是第几页
        //this->m_nCurPage =0;
        int pageNumber=UserDefault::getInstance()->getIntegerForKey("comeInLevel");
        this->m_nCurPage= pageNumber/9;
        this->m_scrollView->setContentOffset(Vec2(-visibleSize.width * m_nCurPage,0));//设置滑动视图的当前页
        //this->m_scrollView->setContentOffsetInDuration(Vec2(-visibleSize.width * 1,0), 0.1f);//设置滑动视图的当前页在0.1秒内移动多少像素
    
    //透明条
    _transparent=Sprite::create("selectlevel/toumingtiao.png");
    _transparent->setPosition(Vec2(visibleSize.width/2, visibleSize.height-_transparent->getContentSize().height/2));
    _transparent->setScale(visibleSize.width/640);
    this->addChild(_transparent,2);
    
    
    
    //圈数量图标
//    Sprite* cNumber=Sprite::create("selectlevel/c.png");
//    cNumber->setPosition(Vec2(visibleSize.width*0.7, visibleSize.height*0.97));
//    cNumber->setScale(visibleSize.width/640);
//    this->addChild(cNumber,3);
    
    char getUserSql[100];
    sprintf(getUserSql, "select * from Prop ");
    Value avm=DataUtil::getRow(getUserSql);
    int energyNumber=avm.asValueMap()["energy"].asInt();
    if (UserDefault::getInstance()->getBoolForKey("isTimeGengXin")) {
        int month=avm.asValueMap()["month"].asInt();
        int day=avm.asValueMap()["day"].asInt();
        int hour=avm.asValueMap()["hour"].asInt();
        int minute=avm.asValueMap()["minute"].asInt();
        if (Single::getInstance()->getLocalMonth()>month) {
            DataUtil::updatePropData("energy", 6);
        }else if (Single::getInstance()->getLocalDay()>day){
            DataUtil::updatePropData("energy", 6);
        }else if (Single::getInstance()->getLocalHour()>hour){
            DataUtil::updatePropData("energy", 6);
        }else if ((Single::getInstance()->getLocalMinute()-minute)/2){
            int num=(Single::getInstance()->getLocalMinute()-minute)/2;
            if (num+energyNumber>6) {
                DataUtil::updatePropData("energy", 6);
            }else{
                DataUtil::updatePropData("energy", num+energyNumber);
            }
            
        }
        
        UserDefault::getInstance()->setBoolForKey("isTimeGengXin", false);
    }
    
    
    char hpropChar[20];
    sprintf(hpropChar, "%d:%d",Single::getInstance()->get_minute(),Single::getInstance()->get_second());
    _minuteNumber=LabelAtlas::create(hpropChar, "selectlevel/shuzi.png", 17.0f, 24.0f, '0');
    _minuteNumber->setPosition(Vec2(visibleSize.width*0.08, visibleSize.height*0.92));
    _minuteNumber->setScale(visibleSize.width/640);
    _minuteNumber->setAnchorPoint(Vec2(0.5, 0.5));
    this->addChild(_minuteNumber,2);
    
    //添加红心
    char getUserSql1[100];
    sprintf(getUserSql1, "select * from Prop ");
    Value avm1=DataUtil::getRow(getUserSql1);
    _heartNumber=avm.asValueMap()["energy"].asInt();
    
    for (int i=0; i<6; i++) {
        Sprite* heart=Sprite::create("selectlevel/kongxin.png");
        heart->setPosition(Vec2(visibleSize.width*0.05+visibleSize.width*0.065*i, visibleSize.height*0.97));
        heart->setScale(visibleSize.width*0.4/640);
        this->addChild(heart,3);
        _heartVector.pushBack(heart);
    }
    for (int i=0; i<_heartNumber; i++) {
        //Texture2D* texture = TextureCache::sharedTextureCache()->addImage("selectlevel/hongxin.png");
        _heartVector.at(i)->setTexture("selectlevel/hongxin.png");
    }
    
    
    
//    char cpropChar[20];
//    sprintf(cpropChar, ":%d",PropNumber2);
//    _cPropNumber=LabelAtlas::create(cpropChar, "selectlevel/propNumber.png", 17.0f, 24.0f, '0');
//    _cPropNumber->setPosition(Vec2(visibleSize.width*0.75, visibleSize.height*0.957));
//    _cPropNumber->setScale(visibleSize.width/640);
//    this->addChild(_cPropNumber,2);

    // 添加 声音  的开关按钮
    if (isSound) {
        _musicMenu=MenuItemImage::create("selectlevel/musicOpen.png","selectlevel/selectMusicOpen.png",CC_CALLBACK_1(SelectLevel::menuMusicCallback, this));
    }else{
        _musicMenu=MenuItemImage::create("selectlevel/musicClose.png","selectlevel/selectedMusicClose.png",CC_CALLBACK_1(SelectLevel::menuMusicCallback, this));
    }
    _musicMenu->setScale(visibleSize.width*0.15/_musicMenu->getContentSize().width);
    _musicMenu->setOpacity(0);
    _musicMenu->setPosition(Point(origin.x +visibleSize.width*0.2,0));
    _musicMenu->runAction( Spawn::create(FadeTo::create(1.0, 255),
                                         MoveTo::create(1.0, Vec2(origin.x + visibleSize.width*0.2 ,origin.y+visibleSize.height*0.05 +_musicMenu->getContentSize().height)),
                                         NULL));
    //成就按钮
    auto chengjiuButton = MenuItemImage::create("selectlevel/chengjiu.png","selectlevel/selectChengjiu.png",
                                                CC_CALLBACK_1(SelectLevel::menuChengjiuCallback, this));
    chengjiuButton->setScale(visibleSize.width*0.15/chengjiuButton->getContentSize().width);
    chengjiuButton->setOpacity(0);
    chengjiuButton->setPosition(Vec2(origin.x +visibleSize.width*0.5,0));
    chengjiuButton->runAction( Spawn::create(FadeTo::create(1.2, 255),
                                             MoveTo::create(1.2, Vec2(origin.x + visibleSize.width*0.5 ,origin.y+visibleSize.height*0.05 +chengjiuButton->getContentSize().height)),
                                             NULL));
    //分享按钮
    auto shareButton = MenuItemImage::create("selectlevel/fenxiang.png","selectlevel/selectFenxiang.png",
                                             CC_CALLBACK_1(SelectLevel::menuShareCallback, this));
    shareButton->setScale(visibleSize.width*0.15/shareButton->getContentSize().width);
    shareButton->setOpacity(0);
    shareButton->setPosition(Vec2(origin.x + visibleSize.width*0.8 ,0));
    shareButton->runAction( Spawn::create(FadeTo::create(1.5, 255),
                                          MoveTo::create(1.5, Vec2(origin.x + visibleSize.width*0.8 ,origin.y+visibleSize.height*0.05 +shareButton->getContentSize().height)),
                                          NULL));
//    //商城按钮
//    auto cundangButton = MenuItemImage::create("selectlevel/shangcheng.png","selectlevel/selectedShangcheng.png",
//                                                CC_CALLBACK_1(SelectLevel::menuCundangCallback, this));
//    cundangButton->setScale(visibleSize.width*0.15/cundangButton->getContentSize().width);
//    cundangButton->setPosition(Vec2(origin.x+visibleSize.width*0.8,origin.y +visibleSize.height*0.05+cundangButton->getContentSize().height));
    
    //左滑按钮
    _leftButton = MenuItemImage::create("selectlevel/leftButton.png","selectlevel/leftButton.png",
                                               CC_CALLBACK_1(SelectLevel::leftAndRightAdjustScrollView, this));
    _leftButton->setTag(1111);
    _leftButton->setPosition(Vec2(origin.x+visibleSize.width*0.05 +_leftButton->getContentSize().width/2 ,origin.y +visibleSize.height/2));
    _leftButton->setScale(visibleSize.width*0.08/_leftButton->getContentSize().width);
    //右滑按钮
    _rightButton = MenuItemImage::create("selectlevel/rightButton.png","selectlevel/rightButton.png",
                                            CC_CALLBACK_1(SelectLevel::leftAndRightAdjustScrollView, this));
    _rightButton->setTag(2222);
    _rightButton->setPosition(Vec2(origin.x+visibleSize.width*0.95-_rightButton->getContentSize().width/2 ,origin.y +visibleSize.height/2));
    _rightButton->setScale(visibleSize.width*0.08/_rightButton->getContentSize().width);

    
    //添加金币按钮
    Sprite* addSprite=Sprite::create("selectlevel/jia.png");
    addSprite->setPosition(Vec2(visibleSize.width*0.45, visibleSize.height*0.97));
    addSprite->setScale(visibleSize.width*0.4/640);
    this->addChild(addSprite,3);
    
    MenuItemImage* addButton=MenuItemImage::create("selectlevel/jia.png","selectlevel/jia.png",CC_CALLBACK_1(SelectLevel::addGold, this));
    addButton->setOpacity(0);
    addButton->setPosition(Vec2(visibleSize.width*0.45, visibleSize.height*0.97));
    addButton->setScale(visibleSize.width*0.8/640);
    // create menu, it's an autorelease object
    auto menu = Menu::create(chengjiuButton,shareButton,_leftButton,_rightButton,_musicMenu,addButton, NULL);
    menu->setPosition(Vec2::ZERO);
    
    this->addChild(menu, 3);

    //添加监听
    auto _eventDispatcher=Director::getInstance()->getEventDispatcher();
    auto listener=EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchMoved=CC_CALLBACK_2(SelectLevel::onTouchMoved, this);
    listener->onTouchBegan=CC_CALLBACK_2(SelectLevel::onTouchBegan,this);
    listener->onTouchEnded=CC_CALLBACK_2(SelectLevel::onTouchEnded, this);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    //注册捕捉监听
    auto listenerkeyPad = EventListenerKeyboard::create();
    listenerkeyPad->onKeyReleased = CC_CALLBACK_2(SelectLevel::onKeyReleased, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listenerkeyPad, this);
    
    //商城层自定义监听回调
    auto shopUICustomListener = EventListenerCustom::create("shopUI", CC_CALLBACK_1(SelectLevel::callBackPropNumberChange, this));
    _eventDispatcher->addEventListenerWithFixedPriority(shopUICustomListener, 1);
    
    return true;
}
void SelectLevel::addGold(Ref* pSender)
{
    for (int i=0; i<6; i++) {
        //Texture2D* texture = TextureCache::sharedTextureCache()->addImage("selectlevel/hongxin.png");
        _heartVector.at(i)->setTexture("selectlevel/hongxin.png");
    }
    _heartNumber=6;
    DataUtil::updatePropData("energy", _heartNumber);
}

void SelectLevel::showEnergy(float dt)
{
    char hpropChar[20];
    if (Single::getInstance()->get_second()<10) {
        sprintf(hpropChar, "%d:0%d",Single::getInstance()->get_minute(),Single::getInstance()->get_second());
    }else
        sprintf(hpropChar, "%d:%d",Single::getInstance()->get_minute(),Single::getInstance()->get_second());
    _minuteNumber->setString(hpropChar);
    
    
    char getUserSql[100];
    sprintf(getUserSql, "select * from Prop ");
    Value avm=DataUtil::getRow(getUserSql);
    int energyNumber=avm.asValueMap()["energy"].asInt();
    if (energyNumber>_heartNumber) {
        //Texture2D* texture = TextureCache::sharedTextureCache()->addImage("selectlevel/hongxin.png");
        _heartVector.at(_heartNumber)->setTexture("selectlevel/hongxin.png");
        _heartNumber++;
    }
    
}

void SelectLevel::callBackPropNumberChange(EventCustom* e)
{
//    char getUserSql[100];
//    sprintf(getUserSql, "select * from Prop ");
//    Value avm=DataUtil::getRow(getUserSql);
//    int PropNumber0=avm.asValueMap()["helpProp"].asInt();
//    int PropNumber2=avm.asValueMap()["circleProp"].asInt();
//    
//    char hPropChar[10];
//    sprintf(hPropChar, ":%d",PropNumber0);
//    char cPropChar[10];
//    sprintf(cPropChar, ":%d",PropNumber2);
//    _hPropNumber->setString(hPropChar);
    
}

void SelectLevel::menuLevelButtonCallback(Ref* pSender,int level,bool issuo)
{
    Director::getInstance()->resume();
    bool isSound=UserDefault::getInstance()->getBoolForKey("isSound");
    if(isSound)
    {
    SimpleAudioEngine::getInstance()->playEffect("musicAndeffect/selectLevelButtonEffect.wav");
    }
    UserDefault::getInstance()->setIntegerForKey("comeInLevel", level);
    if (!issuo&&_heartNumber>0) {
        //红心减少
//        CallFunc* c1=CallFunc::create([=]{
//            if (_heartNumber>0) {
//                Texture2D* texture = TextureCache::sharedTextureCache()->addImage("selectlevel/kongxin.png");
//                _heartVector.at(_heartNumber-1)->setTexture(texture);
//                _heartNumber--;
//                DataUtil::updatePropData("energy", _heartNumber);
//            }
//        });
//        CallFunc* c2=CallFunc::create([=]{
            //进入游戏界面
        log("forkey=%d",UserDefault::getInstance()->getIntegerForKey("Userguide"));
        if (UserDefault::getInstance()->getIntegerForKey("Userguide")==2)   //完成引导以后会设置成2
        {
            Scene* gameScene=GameScene::createScene();
            Director::getInstance()->replaceScene(TransitionFade::create(1.0f, gameScene));
            
        }else{
            log("Userguide=%zd",UserDefault::getInstance()->getIntegerForKey("Userguide"));  //第一次为0 ，
                                                                                             //然后进入超级模式为1.完成超级模式以后为2
            Scene* gameScene=Userguide::createScene();
            Director::getInstance()->replaceScene(TransitionFade::create(1.0f, gameScene));
        }
        //});
        //this->runAction(Sequence::create(c1,DelayTime::create(0.5),c2,NULL));
        
    }
    
}


bool SelectLevel::onTouchBegan(Touch * touch,Event * pEvent)
{
    //用开始的触摸点和scroll的偏移量初始化以下的成员变量
    this->m_touchPoint = touch->getLocation();
    this->m_offsetPoint = this->m_scrollView->getContentOffset();
    
    //以下的这一点特别要注意，大家可以先注释掉以下的这句话然后运行程序，会发现如果触摸不是很快
    //的时候不会有什么问题，但是如果触摸进行的很快，关卡的位置偏移的就不会正确，以下的代码正是解决这个问题到
    if((int)this->m_offsetPoint.x%((int)CCDirector::getInstance()->getWinSize().width) == 0)
    {
        return true;
    }
    return false;
}

//设置关卡跟随手指的方向移动
void SelectLevel::onTouchMoved(Touch * touch,Event * pEvent)
{
    /*3.0中ccpSub(p1,p2)换成p1-p2*/
    Point point = touch->getLocation();
    Point direction = point-this->m_touchPoint;
    
    //CCPoint spriteDirection = ccpAdd(this->m_offsetPoint,direction);
    //当滑动视图是第一页和最后一页时让视图不能滑动
    Point spriteDirection;
    
    if(m_nCurPage==0)
    {
        //当在第1页时不能再往左滑动并且左按钮消失 只在x方向偏移
        spriteDirection = Point(0,0);
        _leftButton->setVisible(false);
    }else if (m_nCurPage==2)
    {
        //当在第最后一页时不能再往右滑动并且右按钮消失 只在x方向偏移
        spriteDirection = Point(this->m_offsetPoint.x,0);
        _rightButton->setVisible(false);
    }else{
        //只在x方向偏移
        spriteDirection = Point(direction.x+this->m_offsetPoint.x,0);
        _leftButton->setVisible(true);
        _rightButton->setVisible(true);
    }
    
    //只在x方向偏移
    //spriteDirection = Point(direction.x+this->m_offsetPoint.x,0);
    this->m_scrollView->setContentOffset(spriteDirection);
    
}

//以下的代码是重点，当结束触摸的时候，为了使关卡显示在屏幕的中间，我们需要这么做
void SelectLevel::onTouchEnded(Touch * touch,Event * pEvent)
{
  
    Point endPoint = touch->getLocation();
    
    float distance = endPoint.x-this->m_touchPoint.x;
    //手指移动的距离小于20的时候，就将偏移量作为0处理
    if(fabs(distance) < 20)
    {
        this->adjustScrollView(0);
    }
    else
    {
        //将偏移量作为参数传进来
        this->adjustScrollView(distance);
    }
}

void SelectLevel::onTouchCancelled(Touch *touch, Event *event)
{

}

//调整关卡的最终位置
void SelectLevel::adjustScrollView(float offset)
{
    Size winSize = Director::getInstance()->getWinSize();
    // 我们根据 offset 的实际情况来判断移动效果
    //如果手指往左划，offset大于0，说明页面在减小，往右增大
    if (offset < 0)
        m_nCurPage ++;
    else if (offset > 0)
        m_nCurPage --;
    
    //不允许超出最左边的一页和最右边的一页
    if (m_nCurPage < 0)
        m_nCurPage = 0;
    else if (m_nCurPage > 2)
        m_nCurPage = 2;
    
    Point adjustPoint = Vec2(-winSize.width * m_nCurPage , 0);
    //这个函数比setContentOffset多了一个参数，第二个参数是设置时间的，就是用多长的时间来改变偏移量
    this->m_scrollView->setContentOffsetInDuration(adjustPoint, 0.3f);
}

//左右按钮调整关卡的最终位置
void SelectLevel::leftAndRightAdjustScrollView(Ref* pSender)
{
    MenuItemImage* button=(MenuItemImage*)pSender;
    
    Size winSize = Director::getInstance()->getWinSize();
    // 我们根据 offset 的实际情况来判断移动效果
    //如果手指往左划，offset大于0，说明页面在减小，往右增大
    if (button->getTag()==1111) {
        //不允许超出最左边的一页和最右边的一页
        m_nCurPage --;
        if (m_nCurPage < 0){
            m_nCurPage = 0;
            _leftButton->setVisible(false);
        }else{
            _rightButton->setVisible(true);
            _leftButton->setVisible(true);
        }
    }else{
        m_nCurPage ++;
        if (m_nCurPage > 2){
            m_nCurPage = 2;
            _rightButton->setVisible(false);
        }else{
            _rightButton->setVisible(true);
            _leftButton->setVisible(true);
        }
    }
    
    
    Point adjustPoint = Vec2(-winSize.width * m_nCurPage , 0);
    //这个函数比setContentOffset多了一个参数，第二个参数是设置时间的，就是用多长的时间来改变偏移量
    this->m_scrollView->setContentOffsetInDuration(adjustPoint, 0.1f);
}

SelectLevel::~SelectLevel()
{
    //_eventDispatcher->removeCustomEventListeners("alertUI");
    _eventDispatcher->removeCustomEventListeners("shopUI");
}

//音乐设置回调方法
void SelectLevel::menuMusicCallback(cocos2d::Ref* pSender)
{
    log("音乐设置");
    bool isSound=UserDefault::getInstance()->getBoolForKey("isSound");
    if(isSound)
    {
        Sprite* no=Sprite::create("selectlevel/musicClose.png");
        _musicMenu->setNormalImage(no);
        _musicMenu->setSelectedImage(no);
        SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
        SimpleAudioEngine::getInstance()->pauseAllEffects();
        UserDefault::getInstance()->setBoolForKey("isSound", false);
        
    }
    else
    {
        Sprite* no=Sprite::create("selectlevel/musicOpen.png");
        _musicMenu->setNormalImage(no);
        _musicMenu->setSelectedImage(no);
        SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
        SimpleAudioEngine::getInstance()->resumeAllEffects();
        UserDefault::getInstance()->setBoolForKey("isSound", true);
    }
    

}

//成就按钮回调方法
void SelectLevel::menuChengjiuCallback(cocos2d::Ref* pSender)
{
    log("成就设置");
    bool isSound=UserDefault::getInstance()->getBoolForKey("isSound");
    if (isSound) {
        SimpleAudioEngine::getInstance()->playEffect("musicAndeffect/buttonEffect.wav");
    }
    
    
    Achievement* _achieve=Achievement::create();
    addChild(_achieve,4,"lay_achieve");
}
//分享按钮回调方法
void SelectLevel::menuShareCallback(cocos2d::Ref* pSender)
{
    log("分享设置");
    bool isSound=UserDefault::getInstance()->getBoolForKey("isSound");
    if (isSound) {
        SimpleAudioEngine::getInstance()->playEffect("musicAndeffect/buttonEffect.wav");
    }
    
        IOSiAP_Bridge* bridge = new IOSiAP_Bridge;
        bridge->requestProducts(6);
    
    
}
//存档按钮回调方法
void SelectLevel::menuCundangCallback(cocos2d::Ref* pSender)
{
    //log("存档设置");
    bool isSound=UserDefault::getInstance()->getBoolForKey("isSound");
    if (isSound) {
        SimpleAudioEngine::getInstance()->playEffect("musicAndeffect/buttonEffect.wav");
    }
    Director::getInstance()->pause();
    Scene* shopScene=ShoppingMall::createScene();
    Director::getInstance()->pushScene(shopScene);
}

void SelectLevel::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
}
void SelectLevel::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
    switch (keyCode)
    {
        case cocos2d::EventKeyboard::KeyCode::KEY_BACK:
        {
            if(m_IsNeedExit == false)
            {
                m_IsNeedExit = true;
                this->scheduleOnce(SEL_SCHEDULE(&SelectLevel::CloseExitSign),5.0f);
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

void SelectLevel::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
    MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif
    Single::getInstance()->stop();
    Single::getInstance()->getLocalTime();
    //更新时间
    DataUtil::updatePropData("month", Single::getInstance()->getLocalMonth());
    DataUtil::updatePropData("day", Single::getInstance()->getLocalDay());
    DataUtil::updatePropData("monute", Single::getInstance()->getLocalMinute());
    DataUtil::updatePropData("hour", Single::getInstance()->getLocalHour());
    UserDefault::getInstance()->setBoolForKey("isTimeGengXin", true);
    //最后别忘了关闭数据库哦
    DataUtil::closeDB();
    SimpleAudioEngine::getInstance()->end();//关闭音乐

    Director::getInstance()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
    
}

//定时器回调 退出标志关闭
void SelectLevel::CloseExitSign(float dt)
{
    m_IsNeedExit = false;
}
