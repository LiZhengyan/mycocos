
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
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	/////////////////////////////
	// 2. add a menu item with "X" image, which is clicked to quit the program
	//    you may modify it.

	// add a "close" icon to exit the progress. it's an autorelease object
	auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));

	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
		origin.y + closeItem->getContentSize().height/2));

	// create menu, it's an autorelease object
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	_labelLoading = Label::createWithTTF("loading...", "fonts/Marker Felt.ttf", 35);
	_labelPercent = Label::createWithTTF("0%%", "fonts/Marker Felt.ttf", 35);

	_labelLoading->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - 20));
	_labelPercent->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + 20));

	this->addChild(_labelLoading);
	this->addChild(_labelPercent);

	_numberOfLoadedSprites = 0;
	_imageOffset = 0;

	auto sharedFileUtils = FileUtils::getInstance();
	std::string fullPathForFilename = sharedFileUtils->fullPathForFilename("ImageMetaData.plist");

	ValueVector vec = sharedFileUtils->getValueVectorFromFile(fullPathForFilename);  
	_numberOfSprites = vec.size();
	// load textrues
	for( auto& e : vec)  
	{ 
		auto row = e.asValueMap();
		auto filename = "icons/" + row.at("filename").asString();		
		Director::getInstance()->getTextureCache()->addImageAsync(filename,
				CC_CALLBACK_1(HelloWorld::loadingCallBack, this));
	}
	return true;
}


void HelloWorld::loadingCallBack(Texture2D *texture)
{
	++_numberOfLoadedSprites;
	__String* str = __String::createWithFormat("%d%%",
                (int)(((float)_numberOfLoadedSprites / _numberOfSprites) * 100));
	_labelPercent->setString(str->getCString());
    
	Size visibleSize = Director::getInstance()->getVisibleSize();
	int i = ++_imageOffset * 60;

	auto sprite = Sprite::createWithTexture(texture);
	sprite->setAnchorPoint(Vec2(0,0));
	addChild(sprite, -1);
	sprite->setPosition(Vec2( i % (int)visibleSize.width, (i / (int)visibleSize.width) * 60));

	if (_numberOfLoadedSprites == _numberOfSprites)
	{
		_numberOfLoadedSprites = 0;
	}
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
