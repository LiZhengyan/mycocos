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
//USING_NS_CC;
using namespace CocosDenshion;
Scene* SelectLevel::createScene()
{
    auto scene = Scene::create();
    auto layer = SelectLevel::create();
    scene->addChild(layer);
    return scene;
}

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
        string insertUser = "insert into User values(1,'false',0,1),(2,'false',0,1),(3,'false',0,1),(4,'false',0,1),(5,'false',0,1),(6,'false',0,1),(7,'false',0,1),(8,'false',0,1),(9,'false',0,1),(10,'false',0,1),(11,'false',0,1),(12,'false',0,1),(13,'false',0,1),(14,'false',0,1),(15,'false',0,1),(16,'false',0,1),(17,'false',0,1),(18,'false',0,1),(19,'false',0,1),(20,'false',0,1),(21,'false',0,1),(22,'false',0,1),(23,'false',0,1),(24,'false',0,1),(25,'false',0,1),(26,'false',0,1),(27,'false',0,1),(28,'false',0,1),(29,'false',0,1),(30,'false',0,1),(31,'false',0,1),(32,'false',0,1),(33,'false',0,1),(34,'false',0,1),(35,'false',0,1),(36,'false',0,1)";
        DataUtil::insertData(insertUser);
    }
    if (isPropExist==false) {
        string creatPropTable = "create table Prop(fileProp integer,helpProp integer,circleProp integer)";
        DataUtil::createTable(creatPropTable,"Prop");
        //像表格中插入数据
        string insertProp = "insert into Prop values(10,10,10)";
        DataUtil::insertData(insertProp);
    }

    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();
    
    
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
            sprite->setPosition(ccpAdd(Vec2(visibleSize.width/2,visibleSize.height/2),Vec2(visibleSize.width*k,0)));
            sprite->setScale(visibleSize.width/sprite->getContentSize().width);
            layer->addChild(sprite, 0);
            //标题
            char titleName[30];
            sprintf(titleName, "selectlevel/title%d.png",k);
            Sprite* spriteTitle=Sprite::create(titleName);
            spriteTitle->setScale(visibleSize.width*1.2/640.0);
            spriteTitle->setPosition(Vec2(visibleSize.width/2+visibleSize.width*k,visibleSize.height*0.82));
            layer->addChild(spriteTitle,3);
            //背景圆
            auto quanBG = Sprite::create("selectlevel/circleBG.png");
            quanBG->setPosition(ccpAdd(Vec2(visibleSize.width/2,visibleSize.height/2),Vec2(visibleSize.width*k,0)));
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
                        suo->setPosition(ccpAdd(Vec2(visibleSize.width/4*(j+1),visibleSize.height*0.64-(visibleSize.height*0.09+visibleSize.height*0.038)*i),Vec2(visibleSize.width*k,0)) );
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
                            levelNum->setPosition(ccpAdd(Vec2(visibleSize.width*0.72-visibleSize.width/4*j,visibleSize.height*smartRes_shuZiHigh-visibleSize.height*0.13*i),Vec2(visibleSize.width*k,0)));
                        }else{
                            levelNum->setPosition(ccpAdd(Vec2(visibleSize.width*0.22+visibleSize.width/4*j,visibleSize.height*smartRes_shuZiHigh-visibleSize.height*0.13*i),Vec2(visibleSize.width*k,0)));
                        }
                        
                        layer->addChild(levelNum, 3);
                 
                    }
                    //4和6按钮调换位置
                    if (i==1) {
                        levelButton->setPosition(ccpAdd(Vec2(visibleSize.width/4*3-visibleSize.width/4*j,visibleSize.height*0.64-(visibleSize.height*0.09+visibleSize.height*0.038)*i),Vec2(visibleSize.width*k,0)) );
                    }else{
                        levelButton->setPosition(ccpAdd(Vec2(visibleSize.width/4*(j+1),visibleSize.height*0.64-(visibleSize.height*0.09+visibleSize.height*0.038)*i),Vec2(visibleSize.width*k,0)) );
                    }
                    
                    levelButton->setScale(visibleSize.width*0.9/640);
                    
                    levelButton->setTag(i*3+j+1);
                    auto menu = Menu::create(levelButton, NULL);
                    menu->setPosition(Vec2::ZERO);
                    layer->addChild(menu, 2);
                    //横条和竖条
                    if (j<2) {
                        hengTiao=Sprite::create("selectlevel/hengtiao2.png");
                        hengTiao->setPosition(ccpAdd(Vec2(visibleSize.width*0.375+visibleSize.width*0.25*j,visibleSize.height*0.64-(visibleSize.height*0.09+visibleSize.height*0.038)*i),Vec2(visibleSize.width*k,0)) );
                        hengTiao->setScale(visibleSize.width*0.12/hengTiao->getContentSize().width);
                        layer->addChild(hengTiao,2);
                        shuTiao=Sprite::create("selectlevel/shutiao2.png");
                        shuTiao->setPosition(ccpAdd(Vec2(visibleSize.width/4*3-visibleSize.width/2*j,visibleSize.height*0.576-visibleSize.height*0.13*j),Vec2(visibleSize.width*k,0)) );
                        shuTiao->setScale(visibleSize.height*smartRes_shuTiaoScale/shuTiao->getContentSize().height);
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
//    Sprite* transparent=Sprite::create("selectlevel/toumingtiao.png");
//    transparent->setPosition(Vec2(visibleSize.width/2, visibleSize.height-transparent->getContentSize().height/2));
//    transparent->setScale(visibleSize.width/640);
//    this->addChild(transparent,2);
    
    //帮助数量图标
//    Sprite* hNumber=Sprite::create("selectlevel/h.png");
//    hNumber->setPosition(Vec2(visibleSize.width*0.45, visibleSize.height*0.97));
//    hNumber->setScale(visibleSize.width/640);
//    this->addChild(hNumber,3);
    //圈数量图标
//    Sprite* cNumber=Sprite::create("selectlevel/c.png");
//    cNumber->setPosition(Vec2(visibleSize.width*0.7, visibleSize.height*0.97));
//    cNumber->setScale(visibleSize.width/640);
//    this->addChild(cNumber,3);
    
//    char getUserSql[100];
//    sprintf(getUserSql, "select * from Prop ");
//    Value avm=DataUtil::getRow(getUserSql);
//    int PropNumber0=avm.asValueMap()["helpProp"].asInt();
//    int PropNumber2=avm.asValueMap()["circleProp"].asInt();
//    
// 
//
//    char hpropChar[20];
//    sprintf(hpropChar, ":%d",PropNumber0);
//    _hPropNumber=LabelAtlas::create(hpropChar, "selectlevel/propNumber.png", 17.0f, 24.0f, '0');
//    _hPropNumber->setPosition(Vec2(visibleSize.width*0.5, visibleSize.height*0.957));
//    _hPropNumber->setScale(visibleSize.width/640);
//    this->addChild(_hPropNumber,2);
//    
//    char cpropChar[20];
//    sprintf(cpropChar, ":%d",PropNumber2);
//    _cPropNumber=LabelAtlas::create(cpropChar, "selectlevel/propNumber.png", 17.0f, 24.0f, '0');
//    _cPropNumber->setPosition(Vec2(visibleSize.width*0.75, visibleSize.height*0.957));
//    _cPropNumber->setScale(visibleSize.width/640);
//    this->addChild(_cPropNumber,2);

    // 添加 声音  的开关按钮
    if (isSound) {
        _musicMenu=MenuItemImage::create("selectlevel/musicOpen.png","selectlevel/musicOpen.png",CC_CALLBACK_1(SelectLevel::menuMusicCallback, this));
    }else{
        _musicMenu=MenuItemImage::create("selectlevel/musicClose.png","selectlevel/musicClose.png",CC_CALLBACK_1(SelectLevel::menuMusicCallback, this));
    }
    _musicMenu->setScale(visibleSize.width*0.15/_musicMenu->getContentSize().width);
    _musicMenu->setPosition(Point(origin.x +visibleSize.width*0.2,origin.y +visibleSize.height*0.05+_musicMenu->getContentSize().height));
    //成就按钮
    auto chengjiuButton = MenuItemImage::create("selectlevel/chengjiu.png","selectlevel/chengjiu.png",
                                           CC_CALLBACK_1(SelectLevel::menuChengjiuCallback, this));
    chengjiuButton->setScale(visibleSize.width*0.15/chengjiuButton->getContentSize().width);
    chengjiuButton->setPosition(Vec2(origin.x +visibleSize.width*0.4,origin.y +visibleSize.height*0.05+chengjiuButton->getContentSize().height));
    //分享按钮
    auto shareButton = MenuItemImage::create("selectlevel/fenxiang.png","selectlevel/fenxiang.png",
                                                CC_CALLBACK_1(SelectLevel::menuShareCallback, this));
    shareButton->setScale(visibleSize.width*0.15/shareButton->getContentSize().width);
    shareButton->setPosition(Vec2(origin.x + visibleSize.width*0.6 ,origin.y+visibleSize.height*0.05 +shareButton->getContentSize().height));
    //存档按钮
    auto cundangButton = MenuItemImage::create("selectlevel/shangcheng.png","selectlevel/shangcheng.png",
                                                CC_CALLBACK_1(SelectLevel::menuCundangCallback, this));
    cundangButton->setScale(visibleSize.width*0.15/cundangButton->getContentSize().width);
    cundangButton->setPosition(Vec2(origin.x+visibleSize.width*0.8,origin.y +visibleSize.height*0.05+cundangButton->getContentSize().height));
    
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

    // create menu, it's an autorelease object
    auto menu = Menu::create(chengjiuButton,shareButton,cundangButton,_leftButton,_rightButton,_musicMenu, NULL);
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
    if (!issuo) {
        Scene* gameScene=GameScene::createScene();
        Director::getInstance()->replaceScene(gameScene);
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
    Point point = touch->getLocation();
    Point direction = ccpSub(point,this->m_touchPoint);
    
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
        m_nCurPage --;
    }else{
        m_nCurPage ++;
    }
    
    
    //不允许超出最左边的一页和最右边的一页
    if (m_nCurPage < 0){
        m_nCurPage = 0;
        _leftButton->setVisible(false);
    }
    else if (m_nCurPage > 2){
        m_nCurPage = 2;
        _rightButton->setVisible(false);
    }else{
        _rightButton->setVisible(true);
        _leftButton->setVisible(true);
    }
    Point adjustPoint = Vec2(-winSize.width * m_nCurPage , 0);
    //这个函数比setContentOffset多了一个参数，第二个参数是设置时间的，就是用多长的时间来改变偏移量
    this->m_scrollView->setContentOffsetInDuration(adjustPoint, 0.3f);
}

SelectLevel::~SelectLevel()
{
    _eventDispatcher->removeCustomEventListeners("alertUI");
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
}
//分享按钮回调方法
void SelectLevel::menuShareCallback(cocos2d::Ref* pSender)
{
    log("分享设置");
    bool isSound=UserDefault::getInstance()->getBoolForKey("isSound");
    if (isSound) {
        SimpleAudioEngine::getInstance()->playEffect("musicAndeffect/buttonEffect.wav");
    }
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
