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

	SpriteBatchNode* batchNode = SpriteBatchNode::create("Ball.png", 100);
	this->addChild(batchNode);

	for(int i = 0;i < 100;++i){
		int x = CCRANDOM_0_1() * 960;
		int y = CCRANDOM_0_1() * 640;
		Sprite* sprite = Sprite::createWithTexture(batchNode->getTexture());
		sprite->setPosition( Vec2(x, y) );
		batchNode->addChild(sprite);
	}

	return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}
