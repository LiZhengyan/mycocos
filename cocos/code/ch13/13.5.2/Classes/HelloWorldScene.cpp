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

	for(int i = 0;i < MAX_COUNT; ++i){

		std::ostringstream stringStream1;
		stringStream1 << "key_ball_" << i;
		std::string keyBall = stringStream1.str();

		std::pair<std::string,Value> pair1(keyBall,Value("Ball.png"));
		map1.insert(pair1);

		std::ostringstream stringStream2;
		stringStream2 << "key_icon_" << i;
		std::string keyIcon = stringStream2.str();

		std::pair<std::string,Value> pair2(keyIcon,Value("icon.png"));
		map2.insert(pair2);
	}

	return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	log("Map1 key-value count = %d",this->map1.size());
	int tagIndex = 0;
	for (auto& pair: map1)
	{
		log("Map1 key-value = %s - %s", pair.first.c_str(),pair.second.asString().c_str());

		int x = CCRANDOM_0_1() * visibleSize.width;
		int y = CCRANDOM_0_1() * visibleSize.height;

		this->removeChildByTag(tagIndex);

		auto sprite = Sprite::create(pair.second.asString());
		sprite->setPosition(Vec2(x, y));
		this->addChild(sprite, 0, tagIndex++);
	}

	log("Map2 key-value count = %d",this->map2.size());

	for (auto& pair: map2)
	{
		log("Map2 key-value = %s - %s", pair.first.c_str(),pair.second.asString().c_str());

		int x = CCRANDOM_0_1() * visibleSize.width;
		int y = CCRANDOM_0_1() * visibleSize.height;

		this->removeChildByTag(tagIndex);

		auto sprite = Sprite::create(pair.second.asString());
		sprite->setPosition(Vec2(x, y));
		this->addChild(sprite, 0, tagIndex++);
	}
}