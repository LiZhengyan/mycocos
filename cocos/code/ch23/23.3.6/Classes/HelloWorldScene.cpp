#include "HelloWorldScene.h"

USING_NS_CC;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

#define bg_music_1   "sound/Jazz.aifc"
#define bg_music_2  "sound/Synth.aifc"
#define sound_1   "sound/Blip.caf"

#else

#define bg_music_1   "sound/Jazz.mp3"
#define bg_music_2  "sound/Synth.mp3"
#define sound_1   "sound/Blip.wav"

#endif

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

	log("HelloWorld init");

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Texture/Texture_PVR_zlib.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Texture/Texture_bg_PVR_zlib.plist");
    
#else
    
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Texture/Texture.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Texture/Texture_bg.plist");
    
#endif
    
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	Sprite *bg = Sprite::createWithSpriteFrameName("background.png");

	// position the label on the center of the screen
	bg->setPosition(Vec2(origin.x + visibleSize.width/2,
		origin.y + visibleSize.height /2));
	this->addChild(bg);

	//开始精灵
	Sprite *startSpriteNormal = Sprite::createWithSpriteFrameName("start-up.png");
	Sprite *startSpriteSelected = Sprite::createWithSpriteFrameName("start-down.png");

	MenuItemSprite *startMenuItem = MenuItemSprite::create(
		startSpriteNormal, 
		startSpriteSelected,
		CC_CALLBACK_1(HelloWorld::menuItemStartCallback, this));
	startMenuItem->setPosition(Director::getInstance()->convertToGL(Vec2(700, 170)));

	// 设置精灵菜单
	Sprite *settingSpriteNormal = Sprite::createWithSpriteFrameName("setting-up.png");
	Sprite *settingSpriteSelected = Sprite::createWithSpriteFrameName("setting-down.png");

	MenuItemSprite *settingMenuItem = MenuItemSprite::create(
		settingSpriteNormal,
		settingSpriteSelected,
		CC_CALLBACK_1(HelloWorld::menuItemSettingCallback, this)); 
	settingMenuItem->setPosition(Director::getInstance()->convertToGL(Vec2(480, 400)));

	// 帮助精灵菜单	
	Sprite *helpSpriteNormal = Sprite::createWithSpriteFrameName("help-up.png");
	Sprite *helpSpriteSelected = Sprite::createWithSpriteFrameName("help-down.png");

	MenuItemSprite *helpMenuItem = MenuItemSprite::create(
		helpSpriteNormal,
		helpSpriteSelected,
		CC_CALLBACK_1(HelloWorld::menuItemHelpCallback, this));	
	helpMenuItem->setPosition(Director::getInstance()->convertToGL(Vec2(860, 480)));

	Menu* mu = Menu::create(startMenuItem, settingMenuItem, helpMenuItem, NULL);	
	mu->setPosition(Vec2::ZERO);
	this->addChild(mu);

	return true;
}

void HelloWorld::menuItemSettingCallback(Ref* pSender)
{	
	auto sc = Setting::createScene();
	auto reScene = TransitionJumpZoom::create(1.0f, sc);
	Director::getInstance()->pushScene(reScene);
	SimpleAudioEngine::getInstance()->playEffect(sound_1);
}

void HelloWorld::menuItemHelpCallback(Ref* pSender)
{
	MenuItem* item = (MenuItem*)pSender;
	log("Touch Help %p", item);
	SimpleAudioEngine::getInstance()->playEffect(sound_1);
}

void HelloWorld::menuItemStartCallback(Ref* pSender)
{
	MenuItem* item = (MenuItem*)pSender;
	log("Touch Start %p", item);
	SimpleAudioEngine::getInstance()->playEffect(sound_1);
}

void HelloWorld::onEnter()
{
	Layer::onEnter();
	log("HelloWorld onEnter");		
}

void HelloWorld::onEnterTransitionDidFinish()
{
	Layer::onEnterTransitionDidFinish();
	log("HelloWorld onEnterTransitionDidFinish");
	//播放
	SimpleAudioEngine::getInstance()->playBackgroundMusic(bg_music_1, true);
}

void HelloWorld::onExit()
{
	Layer::onExit();
	log("HelloWorld onExit");
}

void HelloWorld::onExitTransitionDidStart()
{
	Layer::onExitTransitionDidStart();
	log("HelloWorld onExitTransitionDidStart");
}

void HelloWorld::cleanup()
{
	Layer::cleanup();
	log("HelloWorld cleanup");	
	//停止
	SimpleAudioEngine::getInstance()->stopBackgroundMusic(bg_music_1);
}