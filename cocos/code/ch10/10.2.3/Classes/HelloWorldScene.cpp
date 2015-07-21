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

	auto particleSystem = ParticleFire::create();

	//设置粒子的重力
	particleSystem->setGravity(Vec2(45, 300));
	//设置径向加速度
	particleSystem->setRadialAccel(58);
	//设置粒子初始化大小
	particleSystem->setStartSize(84);
	//设置粒子初始化大小偏差
	particleSystem->setStartSizeVar(73);
	//设置粒子最后大小偏差
	particleSystem->setEndSize(123);
	//设置粒子最后大小偏差
	particleSystem->setEndSizeVar(17);
	//设置粒子切向加速度
	particleSystem->setTangentialAccel(70);
	//设置粒子切向加速度偏差
	particleSystem->setTangentialAccelVar(47);
	//设置粒子生命期
	particleSystem->setLife(0.79f);
	//设置粒子生命期偏差
	particleSystem->setLifeVar(0.45f);
	
	particleSystem->setPosition(Director::getInstance()->convertToGL(Vec2(270, 380)));

	this->addChild(particleSystem);
	

	return true;
}
