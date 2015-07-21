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
bool HelloWorld::init()
{
	if ( !Layer::init() )
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));

	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
		origin.y + closeItem->getContentSize().height/2));


	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	auto label1 = Label::createWithSystemFont("Hello World1", "Arial", 36);
	label1->setPosition(Vec2(origin.x + visibleSize.width/2,
		origin.y + visibleSize.height - 100));
	this->addChild(label1, 1);

	auto label2 = Label::createWithTTF("Hello World2", "fonts/Marker Felt.ttf", 36);
	label2->setPosition(Vec2(origin.x + visibleSize.width/2,
		origin.y + visibleSize.height - 200));
	this->addChild(label2, 1);

	auto label3 = Label::createWithBMFont("fonts/BMFont.fnt", "Hello World3");
	label3->setPosition(Vec2(origin.x + visibleSize.width/2,
		origin.y + visibleSize.height - 300));
	this->addChild(label3, 1);

	TTFConfig ttfConfig("fonts/Marker Felt.ttf",
		36,
		GlyphCollection::DYNAMIC);

	auto label4 = Label::createWithTTF(ttfConfig, "Hello World4");
	label4->setPosition(Vec2(origin.x + visibleSize.width/2,
		origin.y + visibleSize.height - 400));
	this->addChild(label4 , 1);

	ttfConfig.outlineSize = 4;
	auto label5 = Label::createWithTTF(ttfConfig, "Hello World5");
	label5->setPosition(Vec2(origin.x + visibleSize.width/2,
		origin.y + visibleSize.height - 500));
	label5->enableShadow(Color4B(255,255,255,128), Size(4, -4));
	label5->setColor(Color3B::RED);
	
	this->addChild(label5, 1);

	return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
	return;
#endif

	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}
