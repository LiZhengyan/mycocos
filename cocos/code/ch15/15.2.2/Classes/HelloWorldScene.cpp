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

	auto pItmLabel1 = Label::createWithBMFont("fonts/fnt8.fnt", "Parsing Data");
	auto pItmMenu1 = MenuItemLabel::create(pItmLabel1, CC_CALLBACK_1(HelloWorld::OnClickMenu, this));

	Menu* mn = Menu::create(pItmMenu1, NULL);
	mn->alignItemsVertically();
	this->addChild(mn);

	return true;
}

void HelloWorld::OnClickMenu(Ref* pSender)
{
	auto parser = XmlParser::createWithFile("Notes.xml");

	auto list = parser->getList();
	int index = 0;
	for (auto& v: list)
	{
		log("---------------- [%d] -------------------", ++index);
		ValueMap row = v.asValueMap();
		for (auto& pair: row)
		{
			log("===> %s = %s", pair.first.c_str(), pair.second.asString().c_str());
		}
	}
}
