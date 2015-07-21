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

	auto goItem = MenuItemImage::create(
		"go-down.png",
		"go-up.png",
		CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));

	goItem->setPosition(Vec2(origin.x + visibleSize.width - goItem->getContentSize().width/2 ,
		origin.y + goItem->getContentSize().height/2));

	auto menu = Menu::create(goItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	this->list  = __Array::createWithCapacity(MAX_COUNT);
	this->list->retain();

	for(int i = 0;i < MAX_COUNT; ++i){
		Sprite* sprite = Sprite::create("Ball.png");
		this->list->addObject(sprite);
	}

	return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
	Ref* obj = nullptr;
	log("list->count() = %d",this->list->count());
	Size visibleSize = Director::getInstance()->getVisibleSize();

	CCARRAY_FOREACH(this->list, obj) {
		
		Sprite* sprite = (Sprite*)obj;

		int x = CCRANDOM_0_1() * visibleSize.width;
		int y = CCRANDOM_0_1() * visibleSize.height;

		sprite->setPosition( Vec2(x, y) );
		this->removeChild(sprite);
		this->addChild(sprite);
	}

}

HelloWorld::~HelloWorld()
{
	this->list->removeAllObjects();
	CC_SAFE_RELEASE_NULL(this->list);
}