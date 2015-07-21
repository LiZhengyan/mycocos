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
	
	auto bg = Sprite::create("zippo.png");

    bg->setPosition(Vec2(visibleSize.width/2, visibleSize.height /2));
	this->addChild(bg);

	ParticleSystem* particleSystem = ParticleFire::create();

	particleSystem->setPosition(Director::getInstance()->convertToGL(Vec2(270, 380)));

	this->addChild(particleSystem);
	

	return true;
}
