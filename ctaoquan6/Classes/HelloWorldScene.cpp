#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

using namespace cocostudio::timeline;

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
    
    
    auto rootNode = CSLoader::createNode("Action1.csb");
    auto size= Director::getInstance()->getVisibleSize();
    rootNode->setContentSize(size);
    ui::Helper::doLayout(rootNode);
    addChild(rootNode);

    
    
    auto _eventDispatcher=Director::getInstance()->getEventDispatcher();
    auto listener=EventListenerTouchOneByOne::create();
    
    listener->setSwallowTouches(true);
    listener->onTouchMoved=CC_CALLBACK_2(HelloWorld::onTouchMoved, this);
    listener->onTouchBegan=CC_CALLBACK_2(HelloWorld::onTouchBegan,this);
    listener->onTouchEnded=CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    return true;
    
    
}




void HelloWorld::onTouchMoved(Touch *touch, Event *event)
{
    log("-----Move-------");
}


bool HelloWorld::onTouchBegan(Touch *touch, Event *event)
{
    
    log("Began this !!!!");
    return true;
}


void HelloWorld::onTouchEnded(Touch *touch, Event *event)
{
    
    log("Ended this !!!!");
    
}

