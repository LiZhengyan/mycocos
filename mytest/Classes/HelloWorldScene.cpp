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

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...
    

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label0 = Label::createWithTTF("ABCD", "fonts/Marker Felt.ttf", 24);
//    auto label1 = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 34);
//    auto label2 = Label::createWithTTF("DDDDDDD", "fonts/Marker Felt.ttf", 44);
    
    // position the label on the center of the screen
    label0->setPosition(Vec2(origin.x + visibleSize.width/2,origin.y + visibleSize.height - label0->getContentSize().height));
    log("%f,%f",origin.x,origin.y);


    // add the label as a child to this layer
    this->addChild(label0, 1);


    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(sprite,-1);
    
    
    auto mySprite = Sprite::create("CloseNormal.png");
    mySprite->setPosition(Vec2(500,500)); //这里是摆放位置
    mySprite->setRotation(90);  //这里做旋转
    mySprite->setScale(4, 4); //这里是缩放
    mySprite->setAnchorPoint(Vec2(1,1));

    this->addChild(mySprite);
    
    
    auto mySprite1 = Sprite::create("CloseNormal.png");
    this->addChild(mySprite1);
    mySprite1->setPosition(Vec2(500,500)); //这里是摆放位置
    mySprite1->setRotation(90);  //这里做旋转
    mySprite1->setScale(4, 4); //这里是缩放
//    mySprite1->setAnchorPoint(Vec2(0,0)); //mao dian
    

    

    auto moveBy=MoveBy::create(2,Vec2(100,100)); //上下各自移动100p
    auto moveTo=MoveTo::create(2,Vec2(100,100)); //移动100p,100p这个坐标
    
    auto delay =DelayTime::create(2);
    mySprite1->runAction(Sequence::create(moveTo,delay,moveBy,delay->clone(),nullptr));
    
    auto mySprite2 =Sprite::create("tupian/1.png");
    auto mySprite3 =Sprite::create("tupian/2.png",Rect(0,0,20,200));
    mySprite2->setPosition(Vec2(400,400));
    mySprite3->setPosition(Vec2(300,300));
    
    this->addChild(mySprite2);
    this->addChild(mySprite3);

    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
