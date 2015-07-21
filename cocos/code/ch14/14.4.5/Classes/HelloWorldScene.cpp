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
	
	auto pItmLabel = Label::createWithBMFont("fonts/fnt8.fnt", "Read Data");
	auto pItmMenu = MenuItemLabel::create(pItmLabel, CC_CALLBACK_1(HelloWorld::OnClickMenu, this));

	Menu* mn = Menu::create(pItmMenu,  NULL);
	mn->alignItemsVertically();
	this->addChild(mn);

	return true;
}

void HelloWorld::OnClickMenu(Ref* pSender)
{
	auto sharedFileUtils = FileUtils::getInstance();
	std::string fullPath = sharedFileUtils->fullPathForFilename("NotesList.plist");
	log("fullPathForFilename path = %s", fullPath.c_str());

	ValueVector arry  = sharedFileUtils->getValueVectorFromFile(fullPath);

	for (auto& v: arry)
	{
		log("-----------------");
		ValueMap row = v.asValueMap();
		string date = row["date"].asString();
		string content = row["content"].asString();

		log("===>date: : %s", date.c_str());
		log("===>content: : %s", content.c_str());
	}

}
