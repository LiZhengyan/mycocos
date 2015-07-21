#include "SceneA.h"

USING_NS_CC;

Scene* ALayer::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = ALayer::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool ALayer::init()
{
	//////////////////////////////
	// 1. super init first
	if ( !Layer::init() )
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto staticLabel = Label::createWithBMFont("fonts/fnt9.fnt", "Scene A");	
	staticLabel->setPosition(Vec2(visibleSize.width/2,
		visibleSize.height - 50));
	this->addChild(staticLabel, 1);

	auto label = Label::createWithTTF("", "fonts/Marker Felt.ttf", 24); 
	label->setPosition(Vec2(visibleSize.width/2,
		visibleSize.height - 200));
	this->addChild(label, 1, 100);

	auto pItmLabel = Label::createWithBMFont("fonts/fnt9.fnt", "Next");
	auto pItmMenu = MenuItemLabel::create(pItmLabel, CC_CALLBACK_1(ALayer::menEnterNextScene, this));

	Menu* mn = Menu::create(pItmMenu, NULL);
	mn->alignItemsVertically();
	this->addChild(mn);

	return true;
}

// 进入下一个场景
void ALayer::menEnterNextScene(Ref* pSender)
{
	auto  sc = Scene::create();
	auto  layer = BLayer::create();
	layer->setDelegator(this);
	sc->addChild(layer);

	auto reScene = TransitionSlideInR::create(1.0f, sc);
	Director::getInstance()->pushScene(reScene);
}


void ALayer::callBack(void *ctx, const char *str)
{
	log("ALayer callBack");
	Label* label =  (Label*)this->getChildByTag(100);
	if (label) 
		label->setString(str);
}