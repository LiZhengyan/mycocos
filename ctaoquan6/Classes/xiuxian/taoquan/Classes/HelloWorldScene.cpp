#include "HelloWorldScene.h"

USING_NS_CC;

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
static int timeNumber=60;static char Nmuber[10]="60";
// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();

    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    
    
    
    //倒计时
    label = LabelTTF::create(Nmuber, "fonts/Marker Felt.ttf", 24);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));
    this->addChild(label, 1);

    auto sprite = Sprite::create("HelloWorld.png");

    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(sprite, 0);
    
    this->schedule(schedule_selector(HelloWorld::updateTime), 1.0);
    
    
    spriteTiao=Sprite::create("tiao1.png");
    spriteTiao->setRotation(45);
    spriteTiao->setTag(1);
    spriteTiao->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    spriteTiao->setAnchorPoint(Vec2(0.5,0));
    // add the sprite as a child to this layer
    this->addChild(spriteTiao, 0);
    
    //旋转
    auto rotate1= RotateTo::create(1.0f,-45.0);
    auto rotate2= RotateTo::create(1.0f,45.0);
    auto sequenceBG=Sequence::create(rotate1, rotate2,rotate2,rotate1, NULL);
    auto repeatBG=RepeatForever::create(sequenceBG);
    
    spriteTiao->runAction(repeatBG);
    
    //添加进度条
    powerProgress=ProgressTimer::create(Sprite::create("tiao2.png"));
    powerProgress->setTag(2);
    powerProgress->setAnchorPoint(Vec2(0.5,0));
    powerProgress->setBarChangeRate(Point(0,1));
    powerProgress->setType(ProgressTimer::Type::BAR);
    powerProgress->setMidpoint(Point(0,0));
    powerProgress->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    powerProgress->setPercentage(0.0f);
    this->addChild(powerProgress,0);
    //powerProgress->setPercentage(100);
    
    
    auto rotate3= RotateTo::create(1.0f,60.0);
    auto rotate4= RotateTo::create(1.0f,-60.0);
    auto sequencePG=Sequence::create(rotate3, rotate4,rotate4,rotate3, NULL);
    auto repeatPG=RepeatForever::create(sequencePG);
    
    powerProgress->runAction(repeatPG);
//
//
//    powerProgress->setVisible(false);
    
    auto _eventDispatcher=Director::getInstance()->getEventDispatcher();
    auto listener=EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchMoved=CC_CALLBACK_2(HelloWorld::onTouchMoved, this);
    listener->onTouchBegan=CC_CALLBACK_2(HelloWorld::onTouchBegan,this);
    listener->onTouchEnded=CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    return true;
}

void HelloWorld::updateTime(float dt)
{
    if (timeNumber>0) {
        timeNumber--;
        
        sprintf(Nmuber, "%d s",timeNumber);
        log("%s",Nmuber);
        label->setString(Nmuber);
    }

}

bool HelloWorld::onTouchBegan(Touch *touch, Event *event)
{
   Director* director=Director::sharedDirector();
    director->getActionManager()->pauseTarget(HelloWorld::spriteTiao);
    
    
    ProgressFromTo* ptUp=ProgressFromTo::create(2, 0.0f, 100.0f);
    ProgressFromTo* ptDown=ProgressFromTo::create(2, 100.0f, 0.0f);
    auto sequencePG=Sequence::create(ptUp, ptDown, NULL);
    
    
    //auto spawn=Spawn::create(sequencePG,sequenceBG, NULL);
     auto repeatPG=RepeatForever::create(sequencePG);
    powerProgress->runAction(repeatPG);
    //powerProgress->setVisible(true);
    log("-----Began-------");
    return true;
}

void HelloWorld::onTouchMoved(Touch *touch, Event *event)
{
    log("-----Move-------");
}

void HelloWorld::onTouchEnded(Touch *touch, Event *event)
{
    Director* director=Director::sharedDirector();
    director->getActionManager()->resumeTarget(HelloWorld::spriteTiao);
    //powerProgress->setVisible(false);
    //移除进度条
    //this->removeChildByTag(2);
    log("-----End-------");
}

void HelloWorld::onTouchCancelled(Touch *touch, Event *event)
{}

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
