#include "HelloWorldScene.h"
USING_NS_CC;


int timeNum1=100;
int timeNum2=99;

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

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();
   

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Point(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu, 1);


    
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
    
    ScrollView* m_scrollView = scrollView;
    
    //当前显示的是第几页
    //this->m_nCurPage =0;
    int pageNumber=UserDefault::getInstance()->getIntegerForKey("comeInLevel");
//    this->m_nCurPage= pageNumber/9;
//    this->m_scrollView->setContentOffset(Vec2(-visibleSize.width * m_nCurPage,0));//设置滑动视图的当前页
    //this->m_scrollView->setContentOffsetInDuration(Vec2(-visibleSize.width * 1,0), 0.1f);//设置滑动视图的当前页在0.1秒内移动多少像素
    
    
    
    
    return true;
}


void HelloWorld::updateTime(float dt)
{
    timeNum1--;timeNum2--;
    char Number1[10];
    char Number2[10];
    sprintf(Number1, "%d:",timeNum1);
    sprintf(Number2, "%d:",timeNum2);
    
    labelTime1->setString(Number2);
    auto diao = Spawn::create(MoveBy::create(0.6, Vec2(0,-80)),FadeTo::create(0.6, 0), NULL);
    auto labelTime4=LabelAtlas::create("99:", "shuzi.png", 41.0f, 60.0f,'0');
    labelTime4->setString(Number1);
    labelTime4->setPosition(visibleSize/2);
    addChild(labelTime4,2);
    
    labelTime4->runAction(Sequence::create(diao, DelayTime::create(1), CallFunc::create([=]{this->removeChild(labelTime4);}), NULL));

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





