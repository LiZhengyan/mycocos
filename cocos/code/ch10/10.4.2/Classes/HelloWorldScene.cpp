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

	auto bg = Sprite::create("background-1.png");
	bg->setPosition(Point(visibleSize.width/2, visibleSize.height /2));
	this->addChild(bg);

	auto particleSystem = ParticleSystemQuad::create("snow.plist");
	particleSystem->setPosition(Point(visibleSize.width/2, visibleSize.height - 50));
	this->addChild(particleSystem);

	return true;
}
