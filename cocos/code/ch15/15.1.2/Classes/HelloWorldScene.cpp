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

	auto pItmLabel1 = Label::createWithBMFont("fonts/fnt8.fnt", "Decoding Data");
	auto pItmMenu1 = MenuItemLabel::create(pItmLabel1, CC_CALLBACK_1(HelloWorld::OnClickMenu, this));
	

	Menu* mn = Menu::create(pItmMenu1, NULL);
	mn->alignItemsVertically();
	this->addChild(mn);

	return true;
}

void HelloWorld::OnClickMenu(Ref* pSender)
{
	__Array* data = CSVParser::parse("Note.csv");

	for( int i = 0; i < data->count(); i++ )
	{	
		log("--------------Record(%d)-------------------",(i+1));
		__Array* row = static_cast<__Array*>(data->getObjectAtIndex(i));
		for(int j = 0; j < row->count(); j++ )
		{
			__String* str = static_cast<__String*>(row->getObjectAtIndex(j));
			log("%s", str->getCString());
		}
	}
}
