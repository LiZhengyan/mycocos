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

	this->dict1  = __Dictionary::create();
	this->dict1->retain();
	this->dict2  = __Dictionary::create();
	this->dict2->retain();

	for(int i = 0;i < MAX_COUNT; ++i){

		auto sprite1 = Sprite::create("Ball.png");
		this->dict1->setObject(sprite1, i);

		auto sprite2 = Sprite::create("icon.png");
		__String *key = __String::createWithFormat("key%d",i);
		this->dict2->setObject(sprite2, key->getCString());
	}

	return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{

	Size visibleSize = Director::getInstance()->getVisibleSize();

	DictElement* pElement; 

	log("Dict1 key-value count = %d",this->dict1->count());
	CCDICT_FOREACH(dict1, pElement)  
	{	
		int key = pElement->getIntKey();  
		log("Add Sprite %d", key);

		Sprite* sprite = (Sprite*)pElement->getObject();

		int x = CCRANDOM_0_1() * visibleSize.width;
		int y = CCRANDOM_0_1() * visibleSize.height;

		sprite->setPosition( Vec2(x, y) );
		this->removeChild(sprite);
		this->addChild(sprite);
	}


	log("Dict2 key-value count = %d",this->dict2->count());
	CCDICT_FOREACH(dict2, pElement)  
	{	
		const char *key = pElement->getStrKey();  
		log("Add Sprite %s", key);

		Sprite* sprite = (Sprite*)pElement->getObject();

		int x = CCRANDOM_0_1() * visibleSize.width;
		int y = CCRANDOM_0_1() * visibleSize.height;

		sprite->setPosition( Vec2(x, y) );
		this->removeChild(sprite);
		this->addChild(sprite);
	}

}

HelloWorld::~HelloWorld()
{
	this->dict1->removeAllObjects();
	CC_SAFE_RELEASE_NULL(this->dict1);

	this->dict2->removeAllObjects();
	CC_SAFE_RELEASE_NULL(this->dict2);
}