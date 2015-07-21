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
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("texture.pvr.ccz.plist");
    
#else
    
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("texture.plist");
    
#endif
    
    
    Sprite *bg = Sprite::createWithSpriteFrameName("home_bg.png");
    
    // position the label on the center of the screen
    bg->setPosition(Vec2(origin.x + visibleSize.width/2,
                          origin.y + visibleSize.height /2));
    this->addChild(bg);
    
    
    auto startSprite = Sprite::createWithSpriteFrameName("start.png");
    auto settingSprite = Sprite::createWithSpriteFrameName("setting.png");
    auto helpSprite = Sprite::createWithSpriteFrameName("help.png");
    
    auto item1 = MenuItemSprite::create(startSprite,
                                       startSprite,
                                       CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
    auto item2 = MenuItemSprite::create(settingSprite,
                                       settingSprite,
                                       CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
    auto item3 = MenuItemSprite::create(helpSprite,
                                       helpSprite,
                                       CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
    
    Menu* mn = Menu::create(item1,item2,item3, NULL);
    mn->alignItemsVerticallyWithPadding(10.0f);
    
    mn->setPosition(Vec2(origin.x + visibleSize.width/2,
                          origin.y + visibleSize.height /2 - 10));
    
    this->addChild(mn);
    
    return true;
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
