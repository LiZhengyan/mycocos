#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
	// 'scene' is an autorelease Ref
	auto scene = Scene::create();

	// 'layer' is an autorelease Ref
	auto layer = HelloWorld::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

bool HelloWorld::init()
{
	if ( !Layer::init() )
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto background = Sprite::create("background.png");
	background->setAnchorPoint(Vec2::ZERO);
    this->addChild(background,0);
	
	SpriteFrameCache *frameCache = SpriteFrameCache::getInstance();
	frameCache->addSpriteFramesWithFile("SpirteSheet.plist");

    auto mountain1 = Sprite::createWithSpriteFrameName("mountain1.png");
	mountain1->setAnchorPoint(Vec2::ZERO);
    mountain1->setPosition(Vec2(-200,80));
    this->addChild(mountain1,0);

	SpriteFrame *heroSpriteFrame = frameCache->getSpriteFrameByName("hero1.png");
	Sprite *hero1 = Sprite::createWithSpriteFrame(heroSpriteFrame);
    hero1->setPosition(Vec2(800,200));
    this->addChild(hero1,0);

	return true;
}
