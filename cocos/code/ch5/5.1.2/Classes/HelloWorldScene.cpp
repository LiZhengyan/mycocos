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

	auto tree1 = Sprite::create("tree1.png",Rect(604, 38, 302, 295));
	tree1->setPosition(Vec2(200,230));
	this->addChild(tree1,0);
	

	//Texture2D* cache = TextureCache::getInstance()->addImage("tree1.png");
	Texture2D* cache = Director::getInstance()->getTextureCache()->addImage("tree1.png");
	auto tree2 = Sprite::create();
	tree2->setTexture(cache);
	tree2->setTextureRect(Rect(73, 72,182,270));
	tree2->setPosition(Vec2(500,200));
	this->addChild(tree2,0);


	return true;
}


void HelloWorld::menuSoundToggleCallback(Ref* pSender)
{

}


void HelloWorld::menuMusicToggleCallback(Ref* pSender)
{

}