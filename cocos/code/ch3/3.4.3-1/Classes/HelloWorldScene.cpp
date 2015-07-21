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

	// create menu, it's an autorelease object
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	/////////////////////////////
	// 3. add your codes below...
	auto bg = Sprite::create("bg.png");
	bg->setPosition(Vec2(origin.x + visibleSize.width/2,
		origin.y + visibleSize.height/2));

	this->addChild(bg, 0);

	auto node1 = Sprite::create("node1.png");
	node1->setPosition(Vec2(400,500));
	node1->setAnchorPoint(Vec2(1.0, 1.0));

	this->addChild(node1, 0);

	auto node2 = Sprite::create("node2.png");
	node2->setPosition(Vec2(200,300));	
	node2->setAnchorPoint(Vec2(0.5, 0.5));

	this->addChild(node2, 0);

	Vec2 point1 = node1->convertToNodeSpace(node2->getPosition());

	Vec2 point3 = node1->convertToNodeSpaceAR(node2->getPosition());

	log("Node2 NodeSpace = (%f,%f)",point1.x,point1.y);

	log("Node2 NodeSpaceAR = (%f,%f)",point3.x,point3.y);

	return true;
}

void HelloWorld::update(float dt)
{   

	auto label = this->getChildByTag(123);  

	label->setPosition(label->getPosition() + Vec2(2,-2));  
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