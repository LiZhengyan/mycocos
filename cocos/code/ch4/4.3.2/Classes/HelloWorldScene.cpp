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

    Sprite *bg = Sprite::create("menu/background.png");

    bg->setPosition(Vec2(origin.x + visibleSize.width/2,

                             origin.y + visibleSize.height /2));

    this->addChild(bg);

	//开始精灵

    Sprite *startSpriteNormal = Sprite::create("menu/start-up.png");
    Sprite *startSpriteSelected = Sprite::create("menu/start-down.png");

	MenuItemSprite *startMenuItem = MenuItemSprite::create(startSpriteNormal, 
													startSpriteSelected,
												   CC_CALLBACK_1(HelloWorld::menuItemStartCallback, this));

	startMenuItem->setPosition(Director::getInstance()->convertToGL(Vec2(700, 170)));    

	// 设置图片菜单
    MenuItemImage *settingMenuItem = MenuItemImage::create(
                             "menu/setting-up.png",
                             "menu/setting-down.png",
							 CC_CALLBACK_1(HelloWorld::menuItemSettingCallback, this)); 

	settingMenuItem->setPosition(Director::getInstance()->convertToGL(Vec2(480, 400)));	

	// 帮助图片菜单
    MenuItemImage *helpMenuItem = MenuItemImage::create(
                             "menu/help-up.png",
                             "menu/help-down.png",
							 CC_CALLBACK_1(HelloWorld::menuItemHelpCallback, this));	

	helpMenuItem->setPosition(Director::getInstance()->convertToGL(Vec2(860, 480)));

	Menu* mu = Menu::create(startMenuItem, settingMenuItem, helpMenuItem, NULL);	
	mu->setPosition(Vec2::ZERO);
	this->addChild(mu);

    return true;
}

void HelloWorld::menuItemHelpCallback(Ref* pSender)
{
    MenuItem* item = (MenuItem*)pSender;
	log("Touch Help %p", item);
}

void HelloWorld::menuItemStartCallback(Ref* pSender)
{
    MenuItem* item = (MenuItem*)pSender;
	log("Touch Start %p", item);
}

void HelloWorld::menuItemSettingCallback(Ref* pSender)
{
    MenuItem* item = (MenuItem*)pSender;
	log("Touch Setting %p", item);
}
