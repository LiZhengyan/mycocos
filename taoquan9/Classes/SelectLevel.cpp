//
//  SelectLevel.cpp
//  TaoQuan
//
//  Created by yongxinwan on 15/6/16.
//
//

#include "SelectLevel.h"
#include "GameScene.h"
USING_NS_CC;

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
    
    //char* dataXml;
    //this->makeXml(dataXml);
   // paeseXml(dataXml);
    
    
       
    //数据库测试
     DataUtil::initDB("ok.db");
    
//    string sqlssss = "drop table picture";
//    DataUtil::deleteData(sqlssss);
    
    //数据库中创建关卡小图表格
    /*bool isPicExist=DataUtil::tableIsExist("picture");
    if (isPicExist==false) {
        string sqlsss = "create table picture(id integer,level integer,name varchar(10),isCover bool)";
        DataUtil::createTable(sqlsss,"picture");
        //像表格中插入数据
        string sqlss = "insert into picture values(1,1,'1.png','false'),(2,1,'2.png','false'),(3,1,'3.png','false'),(4,1,'4.png','false'),(5,1,'5.png','false'),(6,1,'6.png','false')";
        DataUtil::insertData(sqlss);
    }*/
    
    //数据库中创建关卡大图表格
    /*string creatBigTable = "create table bigPicture(id integer,level integer,name varchar(30))";
    DataUtil::createTable(creatBigTable,"bigPicture");
    //像表格中插入数据
    string insertBigPic = "insert into bigPicture values(11,1,'gamescene/11.png'),(12,2,'gamescene/12.png'),(13,3,'gamescene/13.png'),(14,4,'gamescene/14.png'),(15,5,'gamescene/15.png'),(16,6,'gamescene/16.png'),(17,7,'gamescene/17.png'),(18,8,'gamescene/18.png'),(19,9,'gamescene/19.png')";
    DataUtil::insertData(insertBigPic);*/
    
    //数据库中创建用户表
    bool isUserExist=DataUtil::tableIsExist("User");
    if (isUserExist==false) {
        string creatUserTable = "create table User(level integer,isSuo bool,starNum integer,useTime integer)";
        DataUtil::createTable(creatUserTable,"User");
        //像表格中插入数据
        string insertUser = "insert into User values(1,'false',0,0),(2,'true',0,0),(3,'true',0,0),(4,'true',0,0),(5,'true',0,0),(6,'true',0,0),(7,'true',0,0),(8,'true',0,0),(9,'true',0,0),(10,'true',0,0),(11,'true',0,0),(12,'true',0,0),(13,'true',0,0),(14,'true',0,0),(15,'true',0,0),(16,'true',0,0),(17,'true',0,0),(18,'true',0,0)";
        DataUtil::insertData(insertUser);
    }
    
    //Sprite *pp = Sprite::create();
    // DataUtil::getDataInfo(sqlssssss,pp);
    //最后别忘了关闭数据库哦
    //  DataUtil::closeDB();
    
    
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
   
    isJieSuo=false;
    m_IsNeedExit=false;
    
    auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));
    
    this->addChild(label, 1);
    
    
    
    ScrollView * scrollView = ScrollView::create(Size(visibleSize.width,visibleSize.height));
    
    //创建一个CCLayer，将内容添加到CCLayer中，然后将这个layer添加到scrollview中
        Layer * layer =Layer::create();
        for(int k = 0;k<5;k++)
        {
            //String * string = String::createWithFormat("gamescene/%d.png",i+1);
            //Sprite * sprite = Sprite::create(string->getCString());
            //将所有的精灵都放到屏幕的中间显示
            //sprite->setPosition(ccpAdd(Vec2(visibleSize.width/2,visibleSize.height/2),Vec2(visibleSize.width*i,0)));
            //layer->addChild(sprite);
            //背景
            auto sprite = Sprite::create("gamescene/gameBG.png");
            
            //sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
            sprite->setPosition(ccpAdd(Vec2(visibleSize.width/2,visibleSize.height/2),Vec2(visibleSize.width*k,0)));
            sprite->setScale(visibleSize.width/sprite->getContentSize().width);
            layer->addChild(sprite, 0);
            //圈
            char circleName[30];
            if (k<2) {
                sprintf(circleName, "selectlevel/circleBG%d.png",k+1);

            }else{
                sprintf(circleName, "selectlevel/circleBG%d.png",1);
            }
            auto quanBG = Sprite::create(circleName);
            quanBG->setPosition(ccpAdd(Vec2(visibleSize.width/2,visibleSize.height/2),Vec2(visibleSize.width*k,0)));
            quanBG->setScale(visibleSize.width/quanBG->getContentSize().width);
            layer->addChild(quanBG, 0);
            
            for (int i=0; i<3; i++) {
                for (int j=0; j<3; j++) {
                    char getUserSql[100];
                    sprintf(getUserSql, "select * from User where level=%d",k*9+i*3+j+1);
                    
                    //从数据库中取出用户信息
                    
                    //ValueVector avm=DataUtil::getAll(getUserSql).asValueVector();
                    //log("+++++%lu",avm.size());
                    cocos2d::Value cv=DataUtil::getRow(getUserSql);
                    bool isSuo;int starNum;
                    if (k<2) {
                        isSuo=cv.asValueMap()["isSuo"].asBool();
                        log("suo=%d  =%d",k*9+i*3+j,isSuo);
                        starNum=cv.asValueMap()["starNum"].asInt();
                        //log("starNum=%d  =%d",i*3+j,starNum);
                    }else{
                        isSuo=true;
                        starNum=0;
                    }
                    
                    MenuItemImage* levelButton;
                    if (isSuo) {
                        levelButton = MenuItemImage::create("selectlevel/weiJiesuo.png","selectlevel/weiJiesuo.png",CC_CALLBACK_1(SelectLevel::menuLevelButtonCallback, this,k*9+i*3+j+1,isSuo));
                        //关卡数字
                        LabelAtlas* levelNum=LabelAtlas::create("1", "selectlevel/weiJiesuoNum.png", 28.0f, 20.0f, '1');//加:是为了显示字母，0是开始字符
                        char levelNumber[10];
                        sprintf(levelNumber, "%d",i*3+(j+1));
                        levelNum->setString(levelNumber);
                        levelNum->setScale(visibleSize.width/640.0);
                        levelNum->setPosition(ccpAdd(Vec2(visibleSize.width/4*(j+1)-40,visibleSize.height*0.64-(visibleSize.height*0.09+visibleSize.height*0.038)*i+30),Vec2(visibleSize.width*k,0)));
                        layer->addChild(levelNum, 3);
                    }else{
                        levelButton = MenuItemImage::create("selectlevel/levelNumberBG.png","selectlevel/levelNumberBG.png",CC_CALLBACK_1(SelectLevel::menuLevelButtonCallback, this,k*9+i*3+j+1,isSuo));
                        //关卡数字
                        LabelAtlas* levelNum=LabelAtlas::create("1", "selectlevel/levelNumber.png", 58.0f, 60.0f, '1');//加:是为了显示字母，0是开始字符
                        char levelNumber[10];
                        sprintf(levelNumber, "%d",i*3+(j+1));
                        levelNum->setString(levelNumber);
                        levelNum->setScale(visibleSize.width/640.0);
                        levelNum->setPosition(ccpAdd(Vec2(visibleSize.width/4*(j+1)-30,visibleSize.height*0.64-(visibleSize.height*0.09+visibleSize.height*0.038)*i-20),Vec2(visibleSize.width*k,0)));
                        
                        layer->addChild(levelNum, 3);
                    }
                    levelButton->setScale(visibleSize.width*0.9/640);
                    levelButton->setPosition(ccpAdd(Vec2(visibleSize.width/4*(j+1),visibleSize.height*0.64-(visibleSize.height*0.09+visibleSize.height*0.038)*i),Vec2(visibleSize.width*k,0)) );
                    levelButton->setTag(i*3+j+1);
                    auto menu = Menu::create(levelButton, NULL);
                    menu->setPosition(Vec2::ZERO);
                    layer->addChild(menu, 2);
                    
                    //星星
                    for (int n=0; n<3; n++) {
                        Sprite* star;
                        if (n<starNum)
                            star=Sprite::create("selectlevel/starLight.png");
                        else
                            star=Sprite::create("selectlevel/starNoLight.png");
                            star->setPosition(levelButton->getPositionX()+star->getContentSize().width*(n-1), levelButton->getPositionY()-levelButton->getContentSize().height/2);
                            star->setScale(visibleSize.width/640.0);
                            layer->addChild(star,3);
                        }
                    
                   /*
                    bool isSuo=avm.at(i*3+j).asValueMap()["isSuo"].asBool();
                    log("111111  =%d",isSuo);
                    bool starNum=avm.at(i*3+j).asValueMap()["starNum"].asBool();
                    log("222222  =%d",starNum);
                
                    if (isSuo) {
                        //按钮背景
                        auto levelButton = MenuItemImage::create("selectlevel/weiJiesuo.png","selectlevel/weiJiesuo.png",CC_CALLBACK_1(SelectLevel::menuCloseCallback, this));
                        levelButton->setScale(visibleSize.width*0.9/640);
                        levelButton->setPosition(ccpAdd(Vec2(visibleSize.width/4*j,visibleSize.height*0.64-(visibleSize.height*0.09+visibleSize.height*0.038)*i),Vec2(visibleSize.width*k,0)) );
                        
                        auto menu = Menu::create(levelButton, NULL);
                        menu->setPosition(Vec2::ZERO);
                        layer->addChild(menu, 2);
                        //关卡数字
                        LabelAtlas* levelNum=LabelAtlas::create("1", "selectlevel/weiJiesuoNum.png", 28.0f, 20.0f, '1');//加:是为了显示字母，0是开始字符
                        char levelNumber[10];
                        sprintf(levelNumber, "%d",i*3+j);
                        levelNum->setString(levelNumber);
                        levelNum->setScale(visibleSize.width/640.0);
                        levelNum->setPosition(ccpAdd(Vec2(visibleSize.width/4*j-40,visibleSize.height*0.64-(visibleSize.height*0.09+visibleSize.height*0.038)*i+30),Vec2(visibleSize.width*k,0)));
                        layer->addChild(levelNum, 3);

                        int starNum=avm.at(i*3+j).asValueMap()["starNum"].asInt();
                        log("222222  =%d",starNum);
                        starNum=2;
                        //星星
                        for (int n=0; n<3; n++) {
                            Sprite* star;
                            if (n<starNum)
                                star=Sprite::create("selectlevel/starLight.png");
                            else
                                star=Sprite::create("selectlevel/starNoLight.png");
                            star->setPosition(levelButton->getPositionX()+star->getContentSize().width*(n-1), levelButton->getPositionY()-levelButton->getContentSize().height/2);
                            star->setScale(visibleSize.width/640.0);
                            layer->addChild(star,3);
                        }

                    }else{
                        auto levelButton = MenuItemImage::create("selectlevel/levelNumberBG.png","selectlevel/levelNumberBG.png",CC_CALLBACK_1(SelectLevel::menuCloseCallback, this));
                        levelButton->setScale(visibleSize.width*0.9/640);
                        levelButton->setPosition(ccpAdd(Vec2(visibleSize.width/4*j,visibleSize.height*0.64-(visibleSize.height*0.09+visibleSize.height*0.038)*i),Vec2(visibleSize.width*k,0)) );
                        
                        auto menu = Menu::create(levelButton, NULL);
                        menu->setPosition(Vec2::ZERO);
                        layer->addChild(menu, 2);
                        
                        //关卡数字
                        LabelAtlas* levelNum=LabelAtlas::create("1", "selectlevel/levelNumber.png", 52.0f, 54.0f, '1');//加:是为了显示字母，0是开始字符
                        char levelNumber[10];
                        sprintf(levelNumber, "%d",i*3+j);
                        levelNum->setString(levelNumber);
                        levelNum->setScale(visibleSize.width/640.0);
                        levelNum->setPosition(ccpAdd(Vec2(visibleSize.width/4*j-30,visibleSize.height*0.64-(visibleSize.height*0.09+visibleSize.height*0.038)*i-20),Vec2(visibleSize.width*k,0)));
                        
                        layer->addChild(levelNum, 3);
                        
                        
                        //星星
                        for (int n=0; n<3; n++) {
                            Sprite* star;
                            if (n<starNum)
                                star=Sprite::create("selectlevel/starLight.png");
                            else
                                star=Sprite::create("selectlevel/starNoLight.png");
                            star->setPosition(levelButton->getPositionX()+star->getContentSize().width*(n-1), levelButton->getPositionY()-levelButton->getContentSize().height/2);
                            star->setScale(visibleSize.width/640.0);
                            layer->addChild(star,3);
                        }

                    }*/
                    
                    
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
        this->m_nCurPage = 0;
    
    
    // 添加 声音  的开关按钮
    MenuItemImage *_turnOn,*_turnOff;
    _turnOn = MenuItemImage::create("selectlevel/musicOpen.png","selectlevel/musicOpen.png");
    _turnOff = MenuItemImage::create("selectlevel/musicClose.png","selectlevel/musicClose.png");
    MenuItemToggle *toggleItem = MenuItemToggle::createWithCallback(CC_CALLBACK_1(SelectLevel::menuMusicCallback, this), _turnOn,_turnOff, NULL);

    toggleItem->setScale(visibleSize.width/640);
    toggleItem->setPosition(Point(_turnOn->getContentSize().width,_turnOn->getContentSize().height));
    this->addChild(toggleItem,1);
    //成就按钮
    auto chengjiuButton = MenuItemImage::create("selectlevel/chengjiu.png","selectlevel/chengjiu.png",
                                           CC_CALLBACK_1(SelectLevel::menuChengjiuCallback, this));
    
    chengjiuButton->setPosition(Vec2(origin.x +visibleSize.width- chengjiuButton->getContentSize().width ,origin.y +visibleSize.height- chengjiuButton->getContentSize().height));
    //分享按钮
    auto shareButton = MenuItemImage::create("selectlevel/fenxiang.png","selectlevel/fenxiang.png",
                                                CC_CALLBACK_1(SelectLevel::menuShareCallback, this));
    
    shareButton->setPosition(Vec2(origin.x + visibleSize.width - shareButton->getContentSize().width ,origin.y +shareButton->getContentSize().height));
    //存档按钮
    auto cundangButton = MenuItemImage::create("selectlevel/cundang.png","selectlevel/cundang.png",
                                                CC_CALLBACK_1(SelectLevel::menuCundangCallback, this));
    
    cundangButton->setPosition(Vec2(origin.x+ +cundangButton->getContentSize().width ,origin.y +visibleSize.height- cundangButton->getContentSize().height));
    
    
    // create menu, it's an autorelease object
    auto menu = Menu::create(chengjiuButton,shareButton,cundangButton, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

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
    
    return true;
}

void SelectLevel::menuLevelButtonCallback(Ref* pSender,int level,bool issuo)
{
    Director::getInstance()->resume();
    if (!issuo) {
        UserDefault::getInstance()->setIntegerForKey("comeInLevel", level);
        Scene* gameScene=GameScene::createScene();
        Director::getInstance()->replaceScene(gameScene);
    }
    
}


bool SelectLevel::onTouchBegan(Touch * touch,Event * pEvent)
{
    log("========Began=====");
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
    
    log("========Move=====");
    Point point = touch->getLocation();
    Point direction = ccpSub(point,this->m_touchPoint);
    
    //CCPoint spriteDirection = ccpAdd(this->m_offsetPoint,direction);
    //只在x方向偏移
    Point spriteDirection = Point(direction.x+this->m_offsetPoint.x,0);
    this->m_scrollView->setContentOffset(spriteDirection);
}

//以下的代码是重点，当结束触摸的时候，为了使关卡显示在屏幕的中间，我们需要这么做
void SelectLevel::onTouchEnded(Touch * touch,Event * pEvent)
{
    log("========End=====");
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
    log("=============");
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
    else if (m_nCurPage > 4)
        m_nCurPage = 4;
    
    Point adjustPoint = Vec2(-winSize.width * m_nCurPage , 0);
    //这个函数比setContentOffset多了一个参数，第二个参数是设置时间的，就是用多长的时间来改变偏移量
    this->m_scrollView->setContentOffsetInDuration(adjustPoint, 0.3f);
}
//音乐设置回调方法
void SelectLevel::menuMusicCallback(cocos2d::Ref* pSender)
{
    log("音乐设置");
}

//成就按钮回调方法
void SelectLevel::menuChengjiuCallback(cocos2d::Ref* pSender)
{
    log("成就设置");
}
//分享按钮回调方法
void SelectLevel::menuShareCallback(cocos2d::Ref* pSender)
{
    log("分享设置");
}
//存档按钮回调方法
void SelectLevel::menuCundangCallback(cocos2d::Ref* pSender)
{
    log("存档设置");
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
