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

	///////////////动画开始//////////////////////
	Animation* animation = Animation::create();
	for( int i=1; i< 18; i++)
	{
		auto frameName = String::createWithFormat("fire/campFire%02d.png",i);
		log("frameName = %s",frameName->getCString());
		animation->addSpriteFrameWithFile(frameName->getCString());        
	}
	animation->setDelayPerUnit(0.11f);           //设置动画两帧之间时间间隔
	animation->setRestoreOriginalFrame(true);    //动画执行后还原初始状态

	Animate* action = Animate::create(animation);

	auto sp01 = Sprite::create("fire/campFire01.png");
	sp01->setPosition(Vec2(visibleSize.width/2,
		visibleSize.height /2));
	this->addChild(sp01);
	sp01->runAction(RepeatForever::create(action));

	//////////////////动画结束///////////////////


	return true;
}
