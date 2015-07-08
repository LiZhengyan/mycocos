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
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));
    log("%f,%f",origin.x,origin.y);
    log("%f,%f\n",closeItem->getContentSize().width,closeItem->getContentSize().height);

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("HelloWorld.png");
    auto moveBy = MoveBy::create(5,Vec2(500,0));
    sprite->runAction(moveBy);
    
    
    

    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
//    sprite->setRotation(40);
//    sprite->setScale(2.0, 3.0);

    // add the sprite as a child to this layer    
    this->addChild(sprite, 0);
    
    log("%f,%f",sprite->getContentSize().height,sprite->getContentSize().width);
    
    auto layer3 = LayerColor::create(Color4B(0, 128, 128, 255));
    layer3->setContentSize(CCSizeMake(120, 80));
    layer3->setPosition(Point(50, 50));
    this->addChild(layer3, 10);
    
    auto layer1 = LayerColor::create(Color4B(128, 0, 128, 255));
    layer1->setContentSize(CCSizeMake(120, 80));
    layer1->setPosition(Point(100, 80));
    this->addChild(layer1, 20);
    
    auto layer2 = LayerColor::create(Color4B(128, 128, 0, 255));
    layer2->setContentSize(CCSizeMake(120, 80));
    layer2->setPosition(Point(150, 110));
    this->addChild(layer2, 30);
    
    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
