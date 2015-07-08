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

       
    //数据库测试
     DataUtil::initDB("ok.db");

    
    //数据库中创建用户表
    bool isUserExist=DataUtil::tableIsExist("User");
    if (isUserExist==false) {
        string creatUserTable = "create table User(level integer,isSuo bool,starNum integer,useTime integer)";
        DataUtil::createTable(creatUserTable,"User");
        //像表格中插入数据
        /*string insertUser = "insert into User values(1,'false',0,0),(2,'true',0,0),(3,'true',0,0),(4,'true',0,0),(5,'true',0,0),(6,'true',0,0),(7,'true',0,0),(8,'true',0,0),(9,'true',0,0),(10,'true',0,0),(11,'true',0,0),(12,'true',0,0),(13,'true',0,0),(14,'true',0,0),(15,'true',0,0),(16,'true',0,0),(17,'true',0,0),(18,'true',0,0)";*/
        string insertUser = "insert into User values(1,'false',0,0),(2,'false',0,0),(3,'false',0,0),(4,'false',0,0),(5,'false',0,0),(6,'false',0,0),(7,'false',0,0),(8,'false',0,0),(9,'false',0,0),(10,'false',0,0),(11,'false',0,0),(12,'false',0,0),(13,'false',0,0),(14,'false',0,0),(15,'false',0,0),(16,'false',0,0),(17,'false',0,0),(18,'false',0,0)";
        DataUtil::insertData(insertUser);
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
   
    isJieSuo=false;
    m_IsNeedExit=false;

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
            auto sprite = Sprite::create("selectlevel/gameBG.png");
            
            //sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
            sprite->setPosition(ccpAdd(Vec2(visibleSize.width/2,visibleSize.height/2),Vec2(visibleSize.width*k,0)));
            sprite->setScale(visibleSize.width/sprite->getContentSize().width);
            layer->addChild(sprite, 0);
            //圈
            char circleName[30];
            if (k<1) {
                sprintf(circleName, "selectlevel/circleBG%d.png",k+1);
                Sprite* water=Sprite::create("selectlevel/water.png");
                water->setScale(visibleSize.width*0.1/water->getContentSize().width);
                water->setPosition(Vec2(visibleSize.width/2,visibleSize.height*0.82));
                layer->addChild(water,3);
            }else{
                sprintf(circleName, "selectlevel/circleBG%d.png",1);
            }
            auto quanBG = Sprite::create(circleName);
            quanBG->setPosition(ccpAdd(Vec2(visibleSize.width/2,visibleSize.height/2),Vec2(visibleSize.width*k,0)));
            quanBG->setScale(visibleSize.width*0.9/quanBG->getContentSize().width);
            layer->addChild(quanBG, 0);
            
            for (int i=0; i<3; i++) {
                for (int j=0; j<3; j++) {
                    char getUserSql[100];
                    sprintf(getUserSql, "select * from User where level=%d",k*9+i*3+j+1);
                    
                    //从数据库中取出用户信息
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
                    
                    MenuItemImage* levelButton;Sprite* suo;Sprite* hengTiao;Sprite* shuTiao;
                    
                    
                    if (isSuo) {
                    
                        levelButton = MenuItemImage::create("selectlevel/levelNumberBG.png","selectlevel/levelNumberBG.png",CC_CALLBACK_1(SelectLevel::menuLevelButtonCallback, this,k*9+i*3+j+1,isSuo));
                        //关卡数字
//                        LabelAtlas* levelNum=LabelAtlas::create("1", "selectlevel/weiJiesuoNum.png", 40.0f, 54.0f, '1');//加:是为了显示字母，0是开始字符
//                        char levelNumber[10];
//                        if (i==1) {
//                            levelNum->setPosition(ccpAdd(Vec2(visibleSize.width/4*3-visibleSize.width/4*j-25,visibleSize.height*0.64-(visibleSize.height*0.09+visibleSize.height*0.038)*i-30),Vec2(visibleSize.width*k,0)));
//                        }else{
//                            levelNum->setPosition(ccpAdd(Vec2(visibleSize.width/4*(j+1)-25,visibleSize.height*0.64-(visibleSize.height*0.09+visibleSize.height*0.038)*i-30),Vec2(visibleSize.width*k,0)));
//                        }
//                        
//                        levelNum->setString(levelNumber);
//                        levelNum->setScale(visibleSize.width/640.0);
                        
                        //layer->addChild(levelNum, 2);
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
                        //锁
                        suo=Sprite::create("selectlevel/suo.png");
                        suo->setPosition(ccpAdd(Vec2(visibleSize.width/4*(j+1),visibleSize.height*0.64-(visibleSize.height*0.09+visibleSize.height*0.038)*i),Vec2(visibleSize.width*k,0)) );
                        layer->addChild(suo,4);
                    }else{
                        if (starNum==0)
                            levelButton = MenuItemImage::create("selectlevel/weiJiesuo.png","selectlevel/weiJiesuo.png",CC_CALLBACK_1(SelectLevel::menuLevelButtonCallback, this,k*9+i*3+j+1,isSuo));
                        else
                            levelButton = MenuItemImage::create("selectlevel/levelNumberBG.png","selectlevel/levelNumberBG.png",CC_CALLBACK_1(SelectLevel::menuLevelButtonCallback, this,k*9+i*3+j+1,isSuo));

                        
                        //关卡数字
                        LabelAtlas* levelNum=LabelAtlas::create("1", "selectlevel/levelNumber.png", 40.0f, 54.0f, '1');//加:是为了显示字母，0是开始字符
                        
                        char levelNumber[10];
                        sprintf(levelNumber, "%d",i*3+(j+1));
                        levelNum->setString(levelNumber);
                        levelNum->setScale(visibleSize.width/640.0);
                        if (i==1) {
                            levelNum->setPosition(ccpAdd(Vec2(visibleSize.width*0.72-visibleSize.width/4*j,visibleSize.height*0.605-visibleSize.height*0.13*i),Vec2(visibleSize.width*k,0)));
                        }else{
                            levelNum->setPosition(ccpAdd(Vec2(visibleSize.width*0.22+visibleSize.width/4*j,visibleSize.height*0.605-visibleSize.height*0.13*i),Vec2(visibleSize.width*k,0)));
                        }
                        
                        layer->addChild(levelNum, 3);
                        //横条和竖条
                        if (j<2) {
                            hengTiao=Sprite::create("selectlevel/hengtiao1.png");
                            hengTiao->setPosition(ccpAdd(Vec2(visibleSize.width*0.375+visibleSize.width*0.25*j,visibleSize.height*0.64-(visibleSize.height*0.09+visibleSize.height*0.038)*i),Vec2(visibleSize.width*k,0)) );
                            hengTiao->setScale(visibleSize.width*0.12/hengTiao->getContentSize().width);
                            layer->addChild(hengTiao,2);
                            shuTiao=Sprite::create("selectlevel/shutiao1.png");
                            shuTiao->setScale(visibleSize.height*smartRes_shuTiaoScale/shuTiao->getContentSize().height);
                            shuTiao->setPosition(ccpAdd(Vec2(visibleSize.width/4*3-visibleSize.width/2*j,visibleSize.height*0.576-visibleSize.height*0.13*j),Vec2(visibleSize.width*k,0)) );
                            layer->addChild(shuTiao,2);
                        }
                        
                    }
                    
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
                    
                    //星星
                    for (int n=0; n<3; n++) {
                        Sprite* star;
                        if (n<starNum)
                            star=Sprite::create("selectlevel/starLight.png");
                        else
                            star=Sprite::create("selectlevel/starNoLight.png");
                        if (starNum==0)
                            star->setVisible(false);
                        else
                            star->setVisible(true);
                            star->setPosition(levelButton->getPositionX()+visibleSize.width*0.03*(n-1), levelButton->getPositionY()-visibleSize.height*smartRes_starHigh);
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
    
        //当前显示的是第几页
        this->m_nCurPage =0;
    //adjustScrollView(1);
    
//        int pageNumber=UserDefault::getInstance()->getIntegerForKey("comeInLevel");
//        this->m_nCurPage= pageNumber/9;
//        log("%d",m_nCurPage);
    
    // 添加 声音  的开关按钮
    MenuItemImage *_turnOn,*_turnOff;
    _turnOn = MenuItemImage::create("selectlevel/musicOpen.png","selectlevel/musicOpen.png");
    _turnOff = MenuItemImage::create("selectlevel/musicClose.png","selectlevel/musicClose.png");
    MenuItemToggle *toggleItem = MenuItemToggle::createWithCallback(CC_CALLBACK_1(SelectLevel::menuMusicCallback, this), _turnOn,_turnOff, NULL);
    toggleItem->setScale(visibleSize.width*0.15/toggleItem->getContentSize().width);
    toggleItem->setPosition(Point(origin.x +visibleSize.width*0.05+_turnOn->getContentSize().width,origin.y +visibleSize.height*0.05+_turnOn->getContentSize().height));
    this->addChild(toggleItem,1);
    //成就按钮
    auto chengjiuButton = MenuItemImage::create("selectlevel/chengjiu.png","selectlevel/chengjiu.png",
                                           CC_CALLBACK_1(SelectLevel::menuChengjiuCallback, this));
    chengjiuButton->setScale(visibleSize.width*0.15/chengjiuButton->getContentSize().width);
    chengjiuButton->setPosition(Vec2(origin.x +visibleSize.width*0.95- chengjiuButton->getContentSize().width ,origin.y +visibleSize.height*0.95- chengjiuButton->getContentSize().height));
    //分享按钮
    auto shareButton = MenuItemImage::create("selectlevel/fenxiang.png","selectlevel/fenxiang.png",
                                                CC_CALLBACK_1(SelectLevel::menuShareCallback, this));
    shareButton->setScale(visibleSize.width*0.15/shareButton->getContentSize().width);
    shareButton->setPosition(Vec2(origin.x + visibleSize.width*0.95 - shareButton->getContentSize().width ,origin.y+visibleSize.height*0.05 +shareButton->getContentSize().height));
    //存档按钮
    auto cundangButton = MenuItemImage::create("selectlevel/cundang.png","selectlevel/cundang.png",
                                                CC_CALLBACK_1(SelectLevel::menuCundangCallback, this));
    cundangButton->setScale(visibleSize.width*0.15/cundangButton->getContentSize().width);
    cundangButton->setPosition(Vec2(origin.x+visibleSize.width*0.05 +cundangButton->getContentSize().width ,origin.y +visibleSize.height*0.95- cundangButton->getContentSize().height));
    
    //左滑按钮
    auto leftButton = MenuItemImage::create("selectlevel/leftButton.png","selectlevel/leftButton.png",
                                               CC_CALLBACK_1(SelectLevel::leftAndRightAdjustScrollView, this));
    leftButton->setTag(1111);
    leftButton->setPosition(Vec2(origin.x+visibleSize.width*0.05 +leftButton->getContentSize().width/2 ,origin.y +visibleSize.height/2));
    leftButton->setScale(visibleSize.width*0.08/leftButton->getContentSize().width);
    //右滑按钮
    auto rightButton = MenuItemImage::create("selectlevel/rightButton.png","selectlevel/rightButton.png",
                                            CC_CALLBACK_1(SelectLevel::leftAndRightAdjustScrollView, this));
    rightButton->setTag(2222);
    rightButton->setPosition(Vec2(origin.x+visibleSize.width*0.95-rightButton->getContentSize().width/2 ,origin.y +visibleSize.height/2));
    rightButton->setScale(visibleSize.width*0.08/rightButton->getContentSize().width);

    // create menu, it's an autorelease object
    auto menu = Menu::create(chengjiuButton,shareButton,cundangButton,leftButton,rightButton, NULL);
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
    Point point = touch->getLocation();
    Point direction = ccpSub(point,this->m_touchPoint);
    
    //CCPoint spriteDirection = ccpAdd(this->m_offsetPoint,direction);
    //只在x方向偏移
    Point spriteDirection = Point(direction.x+this->m_offsetPoint.x,0);
    this->m_scrollView->setContentOffset(spriteDirection);
    log("========Move=====%f",spriteDirection.x);
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
    //最后别忘了关闭数据库哦
    DataUtil::closeDB();

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
