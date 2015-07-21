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

	auto label1 = LabelTTF::create("中国", "Arial", 30);
	label1->setPosition(Vec2(origin.x + visibleSize.width/2,
		origin.y + visibleSize.height - 150));
	this->addChild(label1, 1);

	auto label2 = LabelBMFont::create("中国", "fonts/bitmapFontChinese.fnt");
	label2->setPosition(Vec2(origin.x + visibleSize.width/2,
		origin.y + visibleSize.height - 250));
	this->addChild(label2, 1);

	auto label3 = Label::createWithBMFont("fonts/bitmapFontChinese.fnt", "中国3");
	label3->setPosition(Vec2(origin.x + visibleSize.width/2,
		origin.y + visibleSize.height - 350));
	this->addChild(label3, 1);

	TTFConfig ttfConfig("fonts/STLITI.ttf", 36, GlyphCollection::DYNAMIC);
	auto labe4 = Label::createWithTTF(ttfConfig,"您好，美好的一天啊",
                                      TextHAlignment::CENTER,
                                      visibleSize.width);
	labe4->setPosition(Vec2(origin.x + visibleSize.width/2,
		origin.y + visibleSize.height - 450));
	this->addChild(labe4, 1);

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
